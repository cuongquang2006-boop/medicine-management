package com.cun.medicine_manager.dto.request;

import com.fasterxml.jackson.annotation.JsonProperty;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class DiseaseRequest {

    @NotBlank
    private String name;

    private String symptoms;

    private String description;

    @JsonProperty("clinic_id")
    @NotNull
    private Long clinicId;
}