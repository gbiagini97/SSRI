package it.gbiagini.swm.vault.test;

import it.gbiagini.swm.vault.VaultConnectorApplication;
import it.gbiagini.swm.vault.operation.VaultOperation;
import org.json.JSONException;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import static org.assertj.core.api.Assertions.assertThat;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = VaultConnectorApplication.class)
public class VaultOperationTest {

    @Autowired
    private VaultOperation vaultOperation;

    @Test
    public void vaultTemplateCorrectlyInitialized() throws JSONException {
        assertThat(!vaultOperation.getSecret("credentials-database").getString("url").isBlank());
    }
}
