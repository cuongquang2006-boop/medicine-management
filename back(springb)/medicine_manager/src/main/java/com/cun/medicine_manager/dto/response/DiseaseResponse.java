package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class DiseaseResponse {

    private Long id;

    private String name;

    private String clinic_name;

    private String symptoms;

    private String description;

    private String created_at;
}