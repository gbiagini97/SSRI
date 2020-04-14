package it.gbiagini.swm.iam.test;

import it.gbiagini.swm.iam.IamApplication;
import it.gbiagini.swm.iam.domain.Credentials;
import it.gbiagini.swm.iam.domain.CredentialsRepository;
import it.gbiagini.swm.iam.service.CredentialsService;
import org.json.JSONObject;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.annotation.DirtiesContext;
import org.springframework.test.context.junit4.SpringRunner;

import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;

@RunWith(SpringRunner.class)
@DirtiesContext(methodMode = DirtiesContext.MethodMode.BEFORE_METHOD)
@SpringBootTest(classes = IamApplication.class)
public class CredentialsServiceTest {

    @Autowired
    private CredentialsService credentialsService;

    @Autowired
    private CredentialsRepository credentialsRepository;

    public final static String USERNAME = "username";
    public final static String PASSWORD = "password";

    public static final String CLAIMS = new JSONObject()
                                .put("claim1", new JSONObject()
                                    .put("verified", false))
                                .put("claim2", new JSONObject()
                                    .put("verified", true))
                                .toString();


    @Test
    public void saveCredentialsWithEncryption() throws InvalidKeySpecException, NoSuchAlgorithmException {
        credentialsService.registerUser(USERNAME, PASSWORD);

        Credentials credentials = credentialsRepository.findByUsername(USERNAME);
        assertThat(!credentials.getPassword().equals(PASSWORD));

        deleteCredentials(credentials);
    }

    @Test
    public void preAuthenticateUser() throws InvalidKeySpecException, NoSuchAlgorithmException {
        credentialsService.registerUser(USERNAME, PASSWORD);

        boolean isPreAuthenticated = credentialsService.preAuthenticateUser(USERNAME, PASSWORD);

        assertThat(isPreAuthenticated);

        deleteCredentials(credentialsRepository.findByUsername(USERNAME));

    }

    @Test
    public void insertAndVerifyClaimsForUser() throws InvalidKeySpecException, NoSuchAlgorithmException {

        credentialsService.registerUser(USERNAME, PASSWORD);

        assertThat(Optional.ofNullable(credentialsRepository.getClaimsByUsername(USERNAME)).isEmpty());

        credentialsService.updateUserClaims(USERNAME, CLAIMS);

        assertThat(Optional.ofNullable(credentialsRepository.getClaimsByUsername(USERNAME)).isPresent());

        JSONObject userClaims = new JSONObject(credentialsRepository.getClaimsByUsername(USERNAME).get());

        assertThat(!userClaims.getJSONObject("claim1").getBoolean("verified"));
        assertThat(userClaims.getJSONObject("claim2").getBoolean("verified"));

        credentialsRepository.findAll().forEach(c -> System.out.println(c.getId()));
        deleteCredentials(credentialsRepository.findByUsername(USERNAME));
    }


    private void deleteCredentials(Credentials credentials) {
        credentialsRepository.delete(credentials);
        assertThat(!credentialsRepository.existsById(credentials.getId()));
    }

}
