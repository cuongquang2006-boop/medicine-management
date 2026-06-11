package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class DashboardStatsResponse {

    private Long patients;

    private Long medicines;

    private Long clinics;

    private Long prescriptions;
}