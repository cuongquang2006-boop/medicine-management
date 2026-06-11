package com.cun.medicine_manager.entity;


import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.persistence.*;

import lombok.Setter;
import lombok.Getter;

import java.time.LocalDateTime;

import java.util.List;

@Entity
@Table(name = "clinics")
@Getter
@Setter
public class Clinic {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    private String location;

    private String description;

    @JsonProperty("created_at")
    @Column(name = "created_at")
    private LocalDateTime createdAt;

    // one to many
    @OneToMany(mappedBy = "clinic")
    private List<Patient> patients;
}
