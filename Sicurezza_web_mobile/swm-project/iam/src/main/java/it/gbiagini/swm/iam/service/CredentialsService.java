package it.gbiagini.swm.iam.service;

import it.gbiagini.swm.crypto.CryptoLib;
import it.gbiagini.swm.iam.domain.Credentials;
import it.gbiagini.swm.iam.domain.CredentialsRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.util.Map;

@Service
public class CredentialsService {

    @Autowired
    private CredentialsRepository credentialsRepository;

    public void registerUser(String username, String password) throws InvalidKeySpecException, NoSuchAlgorithmException {
        Map<String, String> encryption = CryptoLib.hash(password);

        Credentials credentials = new Credentials();
        credentials.setUsername(username);
        credentials.setPassword(encryption.get("hash"));
        credentials.setSalt(encryption.get("salt"));

        credentialsRepository.save(credentials);

    }

    public boolean preAuthenticateUser(String username, String password) throws InvalidKeySpecException, NoSuchAlgorithmException {
        Map<String, String> encryption = CryptoLib.hash(password);

        return credentialsRepository.findByUsername(username).getPassword().equals(encryption.get("hash"));
    }
}
