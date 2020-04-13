package it.gbiagini.swm.iam.configuration;

import it.gbiagini.swm.vault.operation.VaultOperation;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.jdbc.DataSourceBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import javax.sql.DataSource;

@Configuration
public class DataSourceConfig {

    @Autowired
    private VaultOperation vaultOperation;

    @Bean
    public DataSource getDataSource() throws JSONException {

        JSONObject connectionData = vaultOperation.getSecret( "credentials-database");

        return DataSourceBuilder.create()
                .driverClassName("com.mysql.cj.jdbc.Driver")
                .url(String.format("jdbc:mysql://%s/%s",
                        connectionData.getString("url"),
                        connectionData.getString("schema")))
                .username(connectionData.getString("username"))
                .password(connectionData.getString("password"))
                .build();
    }



}
