package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class PrescriptionResponse {

    private Long id;

    private Long patient_id;

    private Long disease_id;

    private Long created_by;

    private String patient_name;

    private String disease_name;

    private String doctor_name;

    private String diagnosis;

    private String created_at;
}