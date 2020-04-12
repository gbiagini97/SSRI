package it.gbiagini.swm.iam.domain;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CredentialsRepository extends CrudRepository<Credentials, Long> {

    public Credentials findByUsername(String username);
}
