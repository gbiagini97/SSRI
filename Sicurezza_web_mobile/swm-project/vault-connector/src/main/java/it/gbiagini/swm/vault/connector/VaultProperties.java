package it.gbiagini.swm.vault.connector;

import org.springframework.boot.context.properties.ConfigurationProperties;

@ConfigurationProperties(prefix = "vault")
public class VaultProperties {

    private String host;
    private Integer port;
    private String scheme;

    private String roleId;
    private String secretId;

    public String getHost() {
        return host;
    }

    public Integer getPort() {
        return port;
    }

    public String getScheme() {
        return scheme;
    }

    public String getRoleId() {
        return roleId;
    }

    public String getSecretId() {
        return secretId;
    }


    public VaultProperties setHost(String host) {
        this.host = host;
        return this;
    }

    public VaultProperties setPort(Integer port) {
        this.port = port;
        return this;
    }

    public VaultProperties setScheme(String scheme) {
        this.scheme = scheme;
        return this;
    }

    public VaultProperties setRoleId(String roleId) {
        this.roleId = roleId;
        return this;
    }

    public VaultProperties setSecretId(String secretId) {
        this.secretId = secretId;
        return this;
    }

}
