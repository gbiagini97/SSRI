package it.gbiagini.swm.iam.domain;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface UserRepository extends CrudRepository<User, Long> {

    public User findByUsername(String username);

    @Query(value = "SELECT claims FROM users WHERE username = :username", nativeQuery = true)
    public Optional<String> getClaimsByUsername(@Param("username") String username);
}
