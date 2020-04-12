package it.gbiagini.swm.iam;

import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication(scanBasePackages = {"it.gbiagini.swm"})
public class IamApplication {

    public static void main(String[] args) {

        ConfigurableApplicationContext context =
                new SpringApplicationBuilder(IamApplication.class)
                        .registerShutdownHook(false)
                        .web(WebApplicationType.SERVLET)
                        .run(args);

        Runtime.getRuntime().addShutdownHook(new ShutdownHook(context));

    }

    private static class ShutdownHook extends Thread {

        private ConfigurableApplicationContext context;

        private ShutdownHook(ConfigurableApplicationContext context) {

            this.context = context;
        }

        @Override
        public void run() {
            context.close();
        }

    }
}


