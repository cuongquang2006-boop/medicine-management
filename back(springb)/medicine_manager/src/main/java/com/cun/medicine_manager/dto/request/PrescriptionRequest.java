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
public class PrescriptionRequest {

    @JsonProperty("patient_id")
    @NotNull
    private Long patientId;

    @JsonProperty("disease_id")
    @NotNull
    private Long diseaseId;

    @JsonProperty("created_by")
    @NotNull
    private Long createdBy;

    @NotBlank
    private String diagnosis;
}