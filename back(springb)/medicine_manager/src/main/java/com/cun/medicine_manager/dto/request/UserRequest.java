package com.cun.medicine_manager.dto.request;

import com.fasterxml.jackson.annotation.JsonProperty;

import jakarta.validation.constraints.NotBlank;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class UserRequest {

    @NotBlank
    private String username;

    @JsonProperty("full_name")
    @NotBlank
    private String fullName;

    @JsonProperty("password")
    @NotBlank
    private String password;

    @NotBlank
    private String role;
}