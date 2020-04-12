Launch Vault as docker container:

```shell script
docker run --cap-add=IPC_LOCK -p 8200:8200 -e 'VAULT_DEV_ROOT_TOKEN_ID=root' -e 'VAULT_ADDR=http://0.0.0.0:8200' -d --name=vault vault
``` 

Get outputted VAULT_ADDR from logs:
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

Export VAULT_ADDR env variable (TODO at every login in the shell in order to make api calls / CLI commands):
```shell script
export VAULT_ADDR='http://0.0.0.0:8200'
```

Save Unseal Key and Root Token somewhere:
```shell script
echo vsCm1BHIkG3AssAmrySQzqReq6nink/k7w3ywfajdLs= > unseal.key
echo root > root.token

```

Try to login with the root token:
```shell script
vault login 
```

Initialize database:
```sql
CREATE DATABASE credentials;
CREATE USER 'iam'@'%' IDENTIFIED BY 'iam';
GRANT ALL PRIVILEGES ON credentials.* TO 'iam'@'%' WITH GRANT OPTION;
GRANT CREATE USER ON *.* to 'iam'@'%';
```

iam_policy.hcl
```hql
path "auth/approle/login" {
  capabilities = ["create", "read"]
}

path "secret/data/credentials-database"
{
  capabilities = ["read"]
}
```

```shell script
vault policy write iam_policy iam_policy.hcl
```

Create approle for iam:
```shell script
vault auth enable approle
vault write auth/approle/role/iam policies=iam_policy role_id=iam

vault write auth/approle/role/iam/custom-secret-id secret_id=iamsecret1

```
Important!!!
role_id = iam
secret_id = iamsecret1


Store secret in k/v format:
```shell script
vault kv put secret/credentials-database url=127.0.0.1:3306 username=iam password=iam schema=credentials
```
