package it.gbiagini.swm.iam.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import it.gbiagini.swm.iam.domain.json.JsonDeserializer;
import it.gbiagini.swm.iam.domain.json.JsonSerializer;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "credentials", uniqueConstraints = {
        @UniqueConstraint(columnNames = {"username"})
})
public class Credentials implements Serializable {

    private static final long serialVersionUID = 1L;
    
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String username;

    @JsonIgnore
    @Column(nullable = false)
    private String password;

    @Column(nullable = false)
    private String salt;

    @Column(nullable = true, length = 10240)
    @JsonDeserialize(using = JsonDeserializer.class)
    @JsonSerialize(using = JsonSerializer.class)
    private String claims;

    public Credentials() {}

    public Long getId() {
        return id;
    }

    public Credentials setId(Long id) {
        this.id = id;
        return this;
    }

    public String getUsername() {
        return username;
    }

    public Credentials setUsername(String username) {
        this.username = username;
        return this;
    }

    public String getPassword() {
        return password;
    }

    public Credentials setPassword(String password) {
        this.password = password;
        return this;
    }

    public String getSalt() {
        return salt;
    }

    public Credentials setSalt(String salt) {
        this.salt = salt;
        return this;
    }

    public String getClaims() {
        return claims;
    }

    public Credentials setClaims(String claims) {
        this.claims = claims;
        return this;
    }
}
