package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Setter;
import lombok.Getter;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class PatientResponse {

    private Long id;

    private String full_name;

    private Integer age;

    private String gender;

    private String phone;

    private String address;

    private Long clinic_id;

    private String created_at;

}