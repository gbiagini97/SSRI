# IAM

The IAM service is the platform registration service that is responsible of executing `commands` in the MySQL database.

## Connecting to MySQL
The connection with MySQL is performed at application startup via the Datasource definition in the @Configuration [DataSourceConfig](src/main/java/it/gbiagini/swm/iam/domain/DataSourceConfig.java), which is reliant on the [Vault-Connector](../vault-connector) library to retrieve connection parameters.

## Credentials storage
The service registers users with their credentials and their claims. In particular the password is hashed via the [Crypto](../crypto-lib) library and the salt is stored as well for authentication.