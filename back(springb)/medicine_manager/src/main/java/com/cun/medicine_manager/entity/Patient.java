package com.cun.medicine_manager.entity;

import com.cun.medicine_manager.entity.Clinic;

import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.persistence.*;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.Getter;

import java.time.LocalDateTime;

@Entity
@Table (name = "patients")
@Setter
@Getter
@NoArgsConstructor
@AllArgsConstructor
public class Patient{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @JsonProperty("full_name")
    @Column(name = "full_name")
    private String fullName;

    private Integer age;
    private String gender;
    private String phone;
    private String address;

    // many to one n:1
    @ManyToOne
    @JoinColumn(name = "clinic_id")
    private Clinic clinic;

    @JsonProperty("created_at")
    @Column(name = "created_at")
    private LocalDateTime createdAt;
}