package com.cun.medicine_manager.controller;

import com.cun.medicine_manager.dto.request.PrescriptionRequest;
import com.cun.medicine_manager.dto.response.ApiResponse;
import com.cun.medicine_manager.dto.response.PrescriptionResponse;
import com.cun.medicine_manager.service.PrescriptionService;

import jakarta.validation.Valid;

import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/prescriptions")
public class PrescriptionController {

    private final PrescriptionService prescriptionService;

    public PrescriptionController(
            PrescriptionService prescriptionService
    ) {
        this.prescriptionService = prescriptionService;
    }

    @GetMapping
    public ApiResponse<List<PrescriptionResponse>>
    getAllPrescriptions()
    {
        List<PrescriptionResponse> prescriptions =
                prescriptionService.getAllPrescriptions();

        return new ApiResponse<>(
                true,
                prescriptions.size(),
                prescriptions
        );
    }

    @GetMapping("/{id}")
    public ApiResponse<PrescriptionResponse>
    getPrescriptionById(
            @PathVariable Long id
    )
    {
        PrescriptionResponse prescription =
                prescriptionService.getPrescriptionById(id);

        return new ApiResponse<>(
                true,
                1,
                prescription
        );
    }

    @PostMapping
    public ApiResponse<PrescriptionResponse>
    createPrescription(
            @Valid
            @RequestBody
            PrescriptionRequest request
    )
    {
        PrescriptionResponse prescription =
                prescriptionService.createPrescription(
                        request
                );

        return new ApiResponse<>(
                true,
                1,
                prescription
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String>
    deletePrescription(
            @PathVariable Long id
    )
    {
        prescriptionService.deletePrescription(id);

        return new ApiResponse<>(
                true,
                0,
                "Prescription deleted successfully"
        );
    }
}