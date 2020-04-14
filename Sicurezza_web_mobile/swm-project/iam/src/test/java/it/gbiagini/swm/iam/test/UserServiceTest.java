package it.gbiagini.swm.iam.test;

import it.gbiagini.swm.iam.IamApplication;
import it.gbiagini.swm.iam.domain.User;
import it.gbiagini.swm.iam.domain.UserRepository;
import it.gbiagini.swm.iam.service.UserService;
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
public class UserServiceTest {

    @Autowired
    private UserService userService;

    @Autowired
    private UserRepository userRepository;

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
        userService.registerUser(USERNAME, PASSWORD);

        User user = userRepository.findByUsername(USERNAME);
        assertThat(!user.getPassword().equals(PASSWORD));

        deleteCredentials(user);
    }

    @Test
    public void preAuthenticateUser() throws InvalidKeySpecException, NoSuchAlgorithmException {
        userService.registerUser(USERNAME, PASSWORD);

        boolean isPreAuthenticated = userService.preAuthenticateUser(USERNAME, PASSWORD);

        assertThat(isPreAuthenticated);

        deleteCredentials(userRepository.findByUsername(USERNAME));

    }

    @Test
    public void insertAndVerifyClaimsForUser() throws InvalidKeySpecException, NoSuchAlgorithmException {

        userService.registerUser(USERNAME, PASSWORD);

        assertThat(Optional.ofNullable(userRepository.getClaimsByUsername(USERNAME)).isEmpty());

        userService.updateUserClaims(USERNAME, CLAIMS);

        assertThat(Optional.ofNullable(userRepository.getClaimsByUsername(USERNAME)).isPresent());

        JSONObject userClaims = new JSONObject(userRepository.getClaimsByUsername(USERNAME).get());

        assertThat(!userClaims.getJSONObject("claim1").getBoolean("verified"));
        assertThat(userClaims.getJSONObject("claim2").getBoolean("verified"));

        userRepository.findAll().forEach(c -> System.out.println(c.getId()));
        deleteCredentials(userRepository.findByUsername(USERNAME));
    }


    private void deleteCredentials(User user) {
        userRepository.delete(user);
        assertThat(!userRepository.existsById(user.getId()));
    }

}
