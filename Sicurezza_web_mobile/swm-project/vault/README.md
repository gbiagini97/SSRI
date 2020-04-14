# Vault

The Vault secret manager can be instanced via Docker in two different configurations:
* Dev-mode
* Server-mode


## Dev-mode
This mode refers to a particular configuration that is very useful during development:
* In-memory storage: secrets engines, configurations and roles won't be persisted in a local volume;
* Unsealed: Vault will be already unsealed;
* Root Token initialization: the `Root Token` can be declared via commandline.

Start Vault in Dev-mode via the command:
```sh
docker run \
 --cap-add=IPC_LOCK \
 -p 8200:8200 \
 -e 'VAULT_DEV_ROOT_TOKEN_ID=root' \
 -e 'VAULT_ADDR=http://0.0.0.0:8200' \
 --name=vault \
 -d vault
``` 

* `VAULT_DEV_ROOT_TOKEN_ID=root` sets up the root token as `root`;
* `VAULT_ADDR=http://0.0.0.0:8200` sets an environment variable in the container specifying the protocol, endpoint and Vault port.

The container will log something like this:
```

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

In particular the `Unseal Key` and the `Root Token` must be kept in a secure place and not exposed to prevent malicious activities on the Vault instance.

We proceed by logging in via the CLI:
```sh
vault login
```
It will be asked to insert a Token as it is the main authentication mechanism on Vault. By inserting the previously acquired `Root Token` we will be authenticated as root.

## Server-mode
This mode is meant to be production-ready and requires several tasks to be fully functional and secure:
* Storage: can be fine-grained tuned to deployment requirements (making use of: file, database, external-services);
* Listener: it's possible to define the TCP address/port Vault will be listening to;
* Sealed:  Vault will be initialized as sealed so that none can interact with it (neither read nor write) until it will be unsealed;

Let's create the volume for the persistent storage:
```sh
docker volume create vault_volume
```
And start the server:
```sh
docker run \
 -v vault_volume:/vault \
 -e 'VAULT_LOCAL_CONFIG={"backend": {"file": {"path": "/vault/file"}}, "default_lease_ttl": "168h", "max_lease_ttl": "720h",  "listener": {"tcp": {"address": "0.0.0.0:8200", "tls_disable": "true"}}}' \
 -e 'VAULT_API_ADDR=http://0.0.0.0:8200' \
 -e 'VAULT_ADDR=http://0.0.0.0:8200' \
 -p 8200:8200 \
 --cap-add=IPC_LOCK \
 --name=vault \
 -d vault server   
```

Once the instance is started we need to connect to the container and initialize the Vault server:
```sh
vault operator init
```

The output will be something like this:
```
Unseal Key 1: ajsRAYx84/diD3+LsQ1chOjYLlULNjyCMGD1z5DA7MZU
Unseal Key 2: l7rSdskIa34AEDUD6vWQzrJZRwAFsMmULl4SeS+QD0z4
Unseal Key 3: k5r6IFmOxE75yctp8qDIfAVnLuyvLS0nX2oM5Yw0OMcG
Unseal Key 4: Rd62m7rs5o/xiAeue+iLCmgDc1BHiGUWkH6DuVBcT/yD
Unseal Key 5: 8w4pp19PhPO35ypYsmR68V11O35lfzjjfya1/4CSOAnr

Initial Root Token: s.irEonmCW3J5Xhh3qTtpysaLk

Vault initialized with 5 key shares and a key threshold of 3. Please securely
distribute the key shares printed above. When the Vault is re-sealed,
restarted, or stopped, you must supply at least 3 of these keys to unseal it
before it can start servicing requests.

Vault does not store the generated master key. Without at least 3 key to
reconstruct the master key, Vault will remain permanently sealed!

It is possible to generate new unseal keys, provided you have a quorum of
existing unseal keys shares. See "vault operator rekey" for more information.
```

The `root key ceremony` implies the distribution of unseal keys as per logged instructions. At first startup and every time the server is restarted it will automatically seal.

In order to unseal Vault we should use at least 3 keys via:
```sh
vault operator unseal <Unseal-Key-X>
```

After the unseal operation we can login in Vault by inserting the `Root Token` when prompted after the command:
```sh
vault login
```
