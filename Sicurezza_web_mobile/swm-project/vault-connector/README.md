# Vault-Connector

The library provides a simple interface to retrieve secrets from a Vault instance by setting connection options in the externalized [configuration file](src/main/resources/application.yaml).

## Pre-requisites


### Setting up Vault

Vault must be instanced via [local installation](https://www.vaultproject.io/docs/install) or [Docker container](https://hub.docker.com/_/vault), consult the reference guide to determine which instance is most suitable.

A simple guide to run through steps for the Docker container instance is provided [here](../vault).


### Vault APP-Role authentication mechanism
Vault-Connector uses the APP-Role authentication mechanism provided by Vault which is meant to be used for service-to-Vault interactions.

Let's enable the dedicated authorization mechanism via:
```sh
vault auth enable approle
```

The APP-Role is a powerful mechanism that makes services connect to Vault by submitting their `role_id` and their `secret_id`. Vault will then evaulate the credentials and reply to the service with a temporary token that will be used for subsequent calls.

### Vault policies
In order to make a role-authenticated service retrieve secrets from Vault we need to explicitly declare a policy which describes what secrets _paths_ the service is allowed to access.

More info about policies can be found in the [official documentation](https://www.vaultproject.io/docs/concepts/policies).

Let's create the `iam_policy.hcl` file (HCL is the HashiCorp Configuration Language) for our `iam` role that we will create consequently:
```hcl
path "auth/approle/login" {
  capabilities = ["create", "read"]
}

path "kv-v2/data/credentials-database"
{
  capabilities = ["read"]
}
```

* The first entry of the policy allows a service to:
  * Login via the `create` capability;
  * Retrieve useful information about the token acquired via the APP-Role authentication. The `read` capability is necessary to make the service aware about the token expiration time so that it can perform a leasing renewal by logging in again.
* The second entry of the policy is the actual secret location, that the service needs to read.

Then submit the policy to the Vault server via:
```sh
vault policy write iam_policy iam_policy.hcl
```
### Role registration
The APP-Role authentication mechanism is enabled and we've defined the policy for our service; we only need to create an `Entity` and assign it the policy:
```shell script
vault write auth/approle/role/iam policies=iam_policy role_id=iam
vault write auth/approle/role/iam/custom-secret-id secret_id=iamsecret1
```

The `role_id` and the `secret_id` will be used for the login.

### Inserting the secret
We will be using the Vault-Connector for many secret retrievals, so let's begin by enabling the key/value version 2 secret engine and inserting our first secret representing the connection parameters of a MySQL database:
```sh
vault secrets enable kv-v2
vault kv put kv-v2/credentials-database url=127.0.0.1:3306 username=iam password=iam schema=iam
```

## Using the Vault-Connector
The library is not intended to be used as a standalone application but to be part of a service that needs to interact with Vault in order to retrieve secrets.

For instance the `iam` service will need MySQL connection parameters to successfully startup.

We need to initialize the database and create a user for the `iam` service with the credentials written on Vault:
```sql
CREATE DATABASE iam;
CREATE USER 'iam'@'%' IDENTIFIED BY 'iam';
GRANT ALL PRIVILEGES ON iam.* TO 'iam'@'%' WITH GRANT OPTION;
GRANT CREATE USER ON *.* to 'iam'@'%';
```

### Perform the service authentication
The `iam` service needs the APP-Role credentials in order to perform the authentication with Vault, otherwise an exception will be thrown.

The library is flexible so the credentials can be inserted in the externalized [configuration file](src/main/resources/application.yaml), or more securely injected via environment variables.

### Retrieving secrets

By _autowiring_ the @Repository [VaultOperation](src/main/java/it/gbiagini/swm/vault/operation/VaultOperation.java) a service can access to secrets stored in Vault simply by using the method `getSecret(String path)` that will return a non-null JSONObject if the secret is present in the requested path.



