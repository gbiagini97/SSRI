# Vault-Connector

The library provides a simple interface to retrieve secrets from a Vault instance by setting connection options in the externalized [configuration file](src/main/resources/application.yaml).

## Pre-requisites


### Setting up Vault
Launch a Docker instance via the command:
```shell script
docker run --cap-add=IPC_LOCK -p 8200:8200 -e 'VAULT_DEV_ROOT_TOKEN_ID=root' -e 'VAULT_ADDR=http://0.0.0.0:8200' -d --name=vault vault
``` 

* `VAULT_DEV_ROOT_TOKEN_ID=root` sets up the root token as `root`;
* `VAULT_ADDR=http://0.0.0.0:8200` sets an environment variable in the container specifying the protocol, endpoint and Vault port.

The container will log something like this:
```log

==> Vault server configuration:
             Api Address: http://0.0.0.0:8200
                    Cgo: disabled
         Cluster Address: https://0.0.0.0:8201
              Listener 1: tcp (addr: "0.0.0.0:8200", cluster address: "0.0.0.0:8201", max_request_duration: "1m30s", max_request_size: "33554432", tls: "disabled")
               Log Level: info
                   Mlock: supported: true, enabled: false
           Recovery Mode: false
                 Storage: inmem
                 Version: Vault v1.3.4

WARNING! dev mode is enabled! In this mode, Vault runs entirely in-memory
and starts unsealed with a single unseal key. The root token is already
authenticated to the CLI, so you can immediately begin using Vault.

You may need to set the following environment variable:

    $ export VAULT_ADDR='http://0.0.0.0:8200'

The unseal key and root token are displayed below in case you want to
seal/unseal the Vault or re-authenticate.

Unseal Key: vsCm1BHIkG3AssAmrySQzqReq6nink/k7w3ywfajdLs=
Root Token: root

Development mode should NOT be used in production installations!

==> Vault server started! Log data will stream in below:
```

In particolar the `Unseal Key` and the `Root Token` must be kept in a secure place and not exposed to prevent malicious activities on the Vault instance.

We proceed by logging in via the CLI:
```shell
vault login
```
It will be asked to insert a Token as it is the main authentication mechanism on Vault. By inserting the previously acquired `Root Token` we will be authenticated as root.

### Vault APP-Role authentication mechanism
Vault-Connector uses the APP-Role authentication mechanism provided by Vault which is meant to be used for service-to-Vault interactions.

Let's enable the dedicated authorization mechanism via:
```shell
vault auth enable approle
```

The APP-Role is a powerful mechanism that makes services connect to Vault by submitting their `role_id` and their `secret_id`. Vault will then evaulate the credentials and reply to the service with a temporary token that will be used for subsequent calls.

### Vault policies
In order to make a role-authenticated service retrieve secrets from Vault we need to explicitly declare a policy which describes what secrets _paths_ the service is allowed to access.

More info about policies can be found in the [official documentation](https://www.vaultproject.io/docs/concepts/policies)

Let's create the `iam_policy.hcl` file (HCL is the HashiCorp Configuration Language) for our `iam` role that we will create consequently:
```hcl
path "auth/approle/login" {
  capabilities = ["create", "read"]
}

path "secret/data/credentials-database"
{
  capabilities = ["read"]
}
```

* The first entry of the policy allows a service to:
  * Login via the `create` capability;
  * Retrieve useful information about the token acquired via the APP-Role authentication. The ability to access the endpoint is necessary to make the service aware about the token expiration time so that it can perform a leasing renewal by logging in again.
* The second entry of the policy is the actual secret location, that the service needs to read.

Then submit the policy to the Vault server via:
```shell
vault policy write iam_policy iam_policy.hcl
```
### Role registration
The APP-Role authentication mechanism is enabled and we've defined the policy for our service; we only need to create an `Entity` and assign it the policy:
```shell
vault write auth/approle/role/iam policies=iam_policy role_id=iam
vault write auth/approle/role/iam/custom-secret-id secret_id=iamsecret1
```

The `role_id` and the `secret_id` will be used for the login.

### Inserting the secret
We will be using the Vault-Connector for many secret retrievals, so let's begin by inserting our first secret representing the connection parameters of a MySQL database:
```shell script
vault kv put secret/credentials-database url=127.0.0.1:3306 username=iam password=iam schema=credentials
```

## Using the Vault-Connector
The library is not intended to be used as a standalone application but to be part of a service that needs to interact with Vault in order to retrieve secrets.

For instance let's the `iam` service will need MySQL connection parameters to successfully startup.

### Perform the service authentication
The `iam` service needs the APP-Role credentials in order to perform the authentication with Vault, otherwise an exception will be thrown.

The library is flexible so the credentials can be inserted in the externalized [configuration file](src/main/resources/application.yaml), or more securely injected via environment variables.

### Retrieving secrets

By _autowiring_ the @Repository [VaultOperation](src/main/java/it/gbiagini/swm/vault/operation/VaultOperation.java) a service can access to secrets stored in Vault simply by using the method `getSecret(String path)` that will return a non-null JSONObject if the secret is present in the requested path.



