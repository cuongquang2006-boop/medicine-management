package com.cun.medicine_manager.entity;

import com.fasterxml.jackson.annotation.JsonProperty;

import jakarta.persistence.*;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDateTime;

@Entity
@Table(name = "users")
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String username;

    @JsonProperty("password_hash")
    @Column(name = "password_hash")
    private String passwordHash;

    @JsonProperty("full_name")
    @Column(name = "full_name")
    private String fullName;

    private String role;

    @JsonProperty("created_at")
    @Column(name = "created_at")
    private LocalDateTime createdAt;

    @JsonProperty("failed_attempts")
    @Column(name = "failed_attempts")
    private Integer failedAttempts;

    @JsonProperty("locked_until")
    @Column(name = "locked_until")
    private LocalDateTime lockedUntil;
}