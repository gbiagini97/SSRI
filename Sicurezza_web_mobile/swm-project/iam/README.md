# IAM

The `iam` service is the platform registration service that is responsible of executing `commands` in the MySQL database.

## Connecting to MySQL
The connection with MySQL is performed at application startup via the Datasource definition in the @Configuration [DataSourceConfig](src/main/java/it/gbiagini/swm/iam/domain/DataSourceConfig.java), which is reliant on the [Vault-Connector](../vault-connector) library to retrieve connection parameters.
