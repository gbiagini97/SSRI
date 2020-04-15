package it.gbiagini.swm.iam.service;

import io.grpc.stub.StreamObserver;
import it.gbiagini.swm.crypto.CryptoLib;
import it.gbiagini.swm.iam.domain.User;
import it.gbiagini.swm.iam.domain.UserRepository;
import it.gbiagini.swm.iam.grpc.UserGrpc;
import net.devh.boot.grpc.server.service.GrpcService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Map;

import static it.gbiagini.swm.iam.grpc.UserOuterClass.*;

@GrpcService
public class UserService extends UserGrpc.UserImplBase {

    @Autowired
    private UserRepository userRepository;

    @Override
    public void registerUser(Credentials request, StreamObserver<Response> responseObserver) {

        Response.Builder response = Response.newBuilder();

        Map<String, String> encryption;

        try {
            encryption = CryptoLib.hash(request.getPassword());

            User user = new User();
            user.setUsername(request.getUsername());
            user.setPassword(encryption.get("hash"));
            user.setSalt(encryption.get("salt"));

            if (userRepository.save(user).getId() != null)
                response.setResponseCode(201).setResponseMessage("User registered successfully");
            else
                response.setResponseCode(400).setResponseMessage("Bad username or password");

        } catch (Exception e) {
            response.setResponseCode(500).setResponseMessage("An error occurred during user registration: " + e.getMessage());
        }

        responseObserver.onNext(response.build());
        responseObserver.onCompleted();

    }

    @Override
    public void updateUserClaims(UpdateClaimsRequest request, StreamObserver<Response> responseObserver) {

        Response.Builder response = Response.newBuilder();

        try {

            userRepository.save(
                    userRepository
                            .findByUsername(request.getUsername())
                            .setClaims(request.getClaims()));

            response.setResponseCode(200).setResponseMessage("User claims updated successfully");

        } catch (Exception e) {
            response.setResponseCode(500).setResponseMessage("An error occurred during updating user claims: " + e.getMessage());
        }

        responseObserver.onNext(response.build());
        responseObserver.onCompleted();

    }

    @Override
    public void preAuthenticateUser(Credentials request, StreamObserver<Response> responseObserver) {
        Response.Builder response = Response.newBuilder();


        try {
            User user = userRepository.findByUsername(request.getUsername());

            if (CryptoLib.verify(request.getPassword(), user.getSalt(), user.getPassword()))
                response.setResponseCode(200).setResponseMessage("User credentials are correct");
            else
                response.setResponseCode(401).setResponseMessage("User credentials are incorrect");

        } catch (Exception e) {
            response.setResponseCode(500).setResponseMessage("An error occurred during user pre-authentication: " + e.getMessage());
        }

        responseObserver.onNext(response.build());
        responseObserver.onCompleted();
    }

   /* public void registerUser(String username, String password) throws InvalidKeySpecException, NoSuchAlgorithmException {
        Map<String, String> encryption = CryptoLib.hash(password);

        User user = new User();
        user.setUsername(username);
        user.setPassword(encryption.get("hash"));
        user.setSalt(encryption.get("salt"));

        userRepository.save(user);

    }

    public void updateUserClaims(String username, String claims) {
        userRepository.save(
                userRepository.findByUsername(username)
                        .setClaims(claims));
    }

    public boolean preAuthenticateUser(String username, String password) throws InvalidKeySpecException, NoSuchAlgorithmException {
        Map<String, String> encryption = CryptoLib.hash(password);

        return userRepository.findByUsername(username).getPassword().equals(encryption.get("hash"));
    }*/
}
