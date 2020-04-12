package it.gbiagini.swm.iam.test;

import it.gbiagini.swm.iam.IamApplication;
import it.gbiagini.swm.iam.domain.Credentials;
import it.gbiagini.swm.iam.domain.CredentialsRepository;
import it.gbiagini.swm.iam.service.CredentialsService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;

import static org.assertj.core.api.Assertions.assertThat;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = IamApplication.class)
public class CredentialsServiceTest {

    @Autowired
    private CredentialsService credentialsService;

    @Autowired
    private CredentialsRepository credentialsRepository;


    @Test
    public void saveCredentialsWithEncryption() throws InvalidKeySpecException, NoSuchAlgorithmException {
        credentialsService.registerUser("username", "password");

        Credentials credentials = credentialsRepository.findByUsername("username");
        assertThat(!credentials.getPassword().equals("password"));

        deleteCredentials(credentials);
    }

    @Test
    public void preAuthenticateUser() throws InvalidKeySpecException, NoSuchAlgorithmException {
        credentialsService.registerUser("username", "password");

        boolean isPreAuthenticated = credentialsService.preAuthenticateUser("username", "password");

        assertThat(isPreAuthenticated);

        deleteCredentials(credentialsRepository.findByUsername("username"));

    }


    private void deleteCredentials(Credentials credentials) {
        credentialsRepository.delete(credentials);
        assertThat(!credentialsRepository.existsById(credentials.getId()));
    }

}
