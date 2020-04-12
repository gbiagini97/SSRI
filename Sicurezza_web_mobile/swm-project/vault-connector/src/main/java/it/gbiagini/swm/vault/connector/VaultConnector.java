package it.gbiagini.swm.vault.connector;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.annotation.Configuration;
import org.springframework.vault.authentication.AppRoleAuthentication;
import org.springframework.vault.authentication.AppRoleAuthenticationOptions;
import org.springframework.vault.authentication.ClientAuthentication;
import org.springframework.vault.authentication.TokenAuthentication;
import org.springframework.vault.client.VaultClients;
import org.springframework.vault.client.VaultEndpoint;
import org.springframework.vault.config.AbstractVaultConfiguration;
import org.springframework.vault.support.VaultToken;
import org.springframework.web.client.RestTemplate;

import static org.springframework.vault.authentication.AppRoleAuthenticationOptions.*;

@Configuration
@EnableConfigurationProperties(VaultProperties.class)
public class VaultConnector extends AbstractVaultConfiguration {

    @Autowired
    private VaultProperties properties;

    @Override
    public VaultEndpoint vaultEndpoint() {
        VaultEndpoint vaultEndpoint = VaultEndpoint.create(properties.getHost(), properties.getPort());
        vaultEndpoint.setScheme(properties.getScheme());
        return vaultEndpoint;
    }

    @Override
    public ClientAuthentication clientAuthentication() {
        AppRoleAuthenticationOptionsBuilder builder = AppRoleAuthenticationOptions.builder()
                .roleId(RoleId.provided(properties.getRoleId()))
                .secretId(SecretId.provided(properties.getSecretId()))
                .path("approle");


        RestTemplate restTemplate = new RestTemplate();
        restTemplate.setUriTemplateHandler(new VaultClients.PrefixAwareUriBuilderFactory(this::vaultEndpoint));

        VaultToken vaultToken = new AppRoleAuthentication(builder.build(), restTemplate).login();

        return new TokenAuthentication(vaultToken);
    }

}
