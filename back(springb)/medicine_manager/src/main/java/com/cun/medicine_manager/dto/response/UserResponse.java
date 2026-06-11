package com.cun.medicine_manager.dto.response;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class UserResponse {

    private Long id;

    private String username;

    @JsonProperty("full_name")
    private String fullName;

    private String role;

    @JsonProperty("created_at")
    private String createdAt;
}