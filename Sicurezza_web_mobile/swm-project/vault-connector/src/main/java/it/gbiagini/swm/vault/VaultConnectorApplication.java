package it.gbiagini.swm.vault;

import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;

@SpringBootApplication
public class VaultConnectorApplication {

    public static void main(String[] args) {
        new SpringApplicationBuilder(VaultConnectorApplication.class).run(args);
    }
}
