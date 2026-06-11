package com.cun.medicine_manager.controller;

import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;

import com.cun.medicine_manager.entity.Patient;
import com.cun.medicine_manager.service.PatientService;
import com.cun.medicine_manager.dto.request.PatientRequest;
import com.cun.medicine_manager.dto.response.PatientResponse;

import com.cun.medicine_manager.exception.ResourceNotFoundException;
import com.cun.medicine_manager.dto.response.ApiResponse;

import java.util.List;

@RestController
@RequestMapping("/api/patients")
public class PatientController {

    private final PatientService patientService;

    public PatientController(PatientService patientService){
        this.patientService = patientService;
    }

    @GetMapping
    public ApiResponse<List<PatientResponse>> getAllPatients(){

        List<PatientResponse> patients = patientService.getAllPatients();
        return new ApiResponse<> (true, patients.size(), patients);
    }

    @GetMapping("/{id}")
    public ApiResponse<PatientResponse> getPatientById(@PathVariable Long id)
    {
        PatientResponse patient =
                patientService.getPatientById(id);

        return new ApiResponse<>(
                true,
                1,
                patient
        );
    }

    @PostMapping
    public ApiResponse<PatientResponse> createPatient( @RequestBody PatientRequest req){
        PatientResponse patient = patientService.createPatient(req);

        return new ApiResponse<>(
                true,
                1,
                patient
        );
    }

    @PutMapping("/{id}")
    public ApiResponse<PatientResponse> updatePatient(@PathVariable Long id,  @RequestBody PatientRequest req){
        PatientResponse patient = patientService.updatePatient(id, req);
        return new ApiResponse<>(
                true,
                1,
                patient
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String> deletePatient( @PathVariable Long id)
    {
        patientService.deletePatient(id);

        return new ApiResponse<>(
                true,
                0,
                "Patient deleted successfully"
        );
    }
}