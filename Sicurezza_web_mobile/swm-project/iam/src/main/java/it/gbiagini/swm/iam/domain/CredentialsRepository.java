package it.gbiagini.swm.iam.domain;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface CredentialsRepository extends CrudRepository<Credentials, Long> {

    public Credentials findByUsername(String username);

    @Query(value = "SELECT claims FROM credentials WHERE username = :username", nativeQuery = true)
    public Optional<String> getClaimsByUsername(@Param("username") String username);
}
