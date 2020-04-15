package it.gbiagini.swm.iam.test;

import io.grpc.internal.testing.StreamRecorder;
import it.gbiagini.swm.iam.IamApplication;
import it.gbiagini.swm.iam.domain.User;
import it.gbiagini.swm.iam.domain.UserRepository;
import it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials;
import it.gbiagini.swm.iam.service.UserService;
import org.json.JSONObject;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.junit.jupiter.api.extension.ExtendWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.TimeUnit;

import static it.gbiagini.swm.iam.grpc.UserOuterClass.Response;
import static it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest;
import static org.junit.jupiter.api.Assertions.*;


@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@ExtendWith(SpringExtension.class)
@ContextConfiguration(classes = IamApplication.class)
@SpringBootTest
public class UserServiceTest {

    private final static Logger LOG = LoggerFactory.getLogger(UserServiceTest.class);

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
    @Order(1)
    public void saveCredentialsWithEncryption() throws Exception {

        // Build input parameter
        Credentials credentials = Credentials.newBuilder()
                .setUsername(USERNAME)
                .setPassword(PASSWORD)
                .build();

        StreamRecorder<Response> responseObserver = StreamRecorder.create();

        // Make service call for user registration
        userService.registerUser(credentials, responseObserver);

        // Check await time, if exceeds timeout test is failed
        if (!responseObserver.awaitCompletion(5, TimeUnit.SECONDS)) {
            fail("The call did not terminate in time");
        }

        // Check errors in service call
        assertNull(responseObserver.getError());

        // Extract responses
        List<Response> responseList = responseObserver.getValues();
        assertEquals(1, responseList.size());

        // Validate response
        Response response = responseList.get(0);
        LOG.info(response.getResponseMessage());
        assertEquals(201, response.getResponseCode());

        // Verify password encryption
        User user = userRepository.findByUsername(USERNAME);
        assertNotEquals(user.getPassword(), PASSWORD);
    }



    @Test
    @Order(2)
    public void preAuthenticateUser() throws Exception {

        // Build input parameter
        Credentials credentials = Credentials.newBuilder()
                .setUsername(USERNAME)
                .setPassword(PASSWORD)
                .build();

        StreamRecorder<Response> responseObserver = StreamRecorder.create();

        // Make service call for user authentication
        userService.preAuthenticateUser(credentials, responseObserver);

        // Check await time, if exceeds timeout test is failed
        if (!responseObserver.awaitCompletion(5, TimeUnit.SECONDS)) {
            fail("The call did not terminate in time");
        }

        // Check errors in service call
        assertNull(responseObserver.getError());

        // Extract responses
        List<Response> responseList = responseObserver.getValues();
        assertEquals(1, responseList.size());

        // Validate response
        Response response = responseList.get(0);
        LOG.info(response.getResponseMessage());
        assertEquals(200, response.getResponseCode());
    }

    @Test
    @Order(3)
    public void insertAndVerifyClaimsForUser() throws Exception {

        UpdateClaimsRequest updateClaimsRequest = UpdateClaimsRequest.newBuilder()
                .setUsername(USERNAME)
                .setClaims(CLAIMS)
                .build();

        StreamRecorder<Response> responseObserver = StreamRecorder.create();

        // Make service call for user authentication
        userService.updateUserClaims(updateClaimsRequest, responseObserver);

        // Check await time, if exceeds timeout test is failed
        if (!responseObserver.awaitCompletion(5, TimeUnit.SECONDS)) {
            fail("The call did not terminate in time");
        }

        // Check errors in service call
        assertNull(responseObserver.getError());

        // Extract responses
        List<Response> responseList = responseObserver.getValues();
        assertEquals(1, responseList.size());

        // Validate response
        Response response = responseList.get(0);
        LOG.info(response.getResponseMessage());
        assertEquals(200, response.getResponseCode());

        // Verify claims persistance
        assertTrue(Optional.ofNullable(userRepository.getClaimsByUsername(USERNAME)).isPresent());

        JSONObject userClaims = new JSONObject(userRepository.getClaimsByUsername(USERNAME).get());

        // Verify claims
        assertFalse(userClaims.getJSONObject("claim1").getBoolean("verified"));
        assertTrue(userClaims.getJSONObject("claim2").getBoolean("verified"));

    }

    @Test
    @Order(4)
    public void deleteUser() {
        User user = userRepository.findByUsername(USERNAME);
        userRepository.delete(user);
        assertFalse(userRepository.existsById(user.getId()));
    }



/*

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

*/

    private void deleteUser(User user) {
        userRepository.delete(user);
    }

}
