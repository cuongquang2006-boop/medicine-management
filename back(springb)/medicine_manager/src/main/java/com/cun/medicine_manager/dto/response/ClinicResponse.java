package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import lombok.Getter;
import lombok.Setter;


@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class ClinicResponse {

    private Long id;

    private String name;

    private String location;

    private String description;

    private String created_at;

}


