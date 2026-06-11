package com.cun.medicine_manager.dto.request;

import jakarta.validation.constraints.NotBlank;

import jakarta.validation.constraints.Size;


import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;


@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class ClinicRequest {

    @NotBlank
    private String name;

    @NotBlank
    private String location;

    @Size(max = 2000)
    private String description;

}
