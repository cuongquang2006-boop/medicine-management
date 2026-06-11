package com.cun.medicine_manager.dto.request;

import com.fasterxml.jackson.annotation.JsonProperty;

import jakarta.validation.Valid;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Size;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.Pattern;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class PatientRequest {

    @JsonProperty("full_name")
    @NotBlank
    private String fullName;

    @NotNull
    @Min(1)
    @Max(150)
    private Integer age;

    private String gender;

    @NotBlank
    private String phone;

    @NotBlank
    private String address;

    @JsonProperty("clinic_id")
    @NotNull
    private Long clinicId;

}