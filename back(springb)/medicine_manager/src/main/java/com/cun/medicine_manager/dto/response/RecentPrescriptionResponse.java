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
public class RecentPrescriptionResponse {

    private String patient;

    private String disease;

    private Integer medicines;

    @JsonProperty("created_at")
    private String createdAt;
}