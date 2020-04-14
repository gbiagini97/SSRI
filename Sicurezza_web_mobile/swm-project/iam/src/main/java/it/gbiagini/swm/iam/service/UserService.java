package it.gbiagini.swm.iam.service;

import it.gbiagini.swm.crypto.CryptoLib;
import it.gbiagini.swm.iam.domain.User;
import it.gbiagini.swm.iam.domain.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.util.Map;

@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;

    public void registerUser(String username, String password) throws InvalidKeySpecException, NoSuchAlgorithmException {
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
    }
}
