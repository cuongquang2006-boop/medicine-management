package com.cun.medicine_manager.controller;

import com.cun.medicine_manager.dto.request.ClinicRequest;
import com.cun.medicine_manager.dto.response.ApiResponse;
import com.cun.medicine_manager.dto.response.ClinicResponse;
import com.cun.medicine_manager.service.ClinicService;

import jakarta.validation.Valid;

import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/clinics")
public class ClinicController {

    private final ClinicService clinicService;

    public ClinicController(ClinicService clinicService) {
        this.clinicService = clinicService;
    }

    @GetMapping
    public ApiResponse<List<ClinicResponse>> getAllClinics() {

        List<ClinicResponse> clinics = clinicService.getAllClinics();

        return new ApiResponse<>(
                true,
                clinics.size(),
                clinics
        );
    }

    @GetMapping("/{id}")
    public ApiResponse<ClinicResponse> getClinicById(
            @PathVariable Long id
    ) {

        ClinicResponse clinic = clinicService.getClinicById(id);

        return new ApiResponse<>(
                true,
                1,
                clinic
        );
    }

    @PostMapping
    public ApiResponse<ClinicResponse> createClinic(
            @Valid @RequestBody ClinicRequest req
    ) {

        ClinicResponse clinic = clinicService.createClinic(req);

        return new ApiResponse<>(
                true,
                1,
                clinic
        );
    }

    @PutMapping("/{id}")
    public ApiResponse<ClinicResponse> updateClinic(
            @PathVariable Long id,
            @Valid @RequestBody ClinicRequest req
    ) {

        ClinicResponse clinic = clinicService.updateClinic(id, req);

        return new ApiResponse<>(
                true,
                1,
                clinic
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String> deleteClinic(
            @PathVariable Long id
    ) {

        clinicService.deleteClinic(id);

        return new ApiResponse<>(
                true,
                0,
                "Clinic deleted successfully"
        );
    }
}