package com.cun.medicine_manager.controller;

import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;

import com.cun.medicine_manager.service.DiseaseService;

import com.cun.medicine_manager.dto.request.DiseaseRequest;
import com.cun.medicine_manager.dto.response.DiseaseResponse;
import com.cun.medicine_manager.dto.response.ApiResponse;

import java.util.List;

@RestController
@RequestMapping("/api/diseases")
public class DiseaseController {

    private final DiseaseService diseaseService;

    public DiseaseController(
            DiseaseService diseaseService)
    {
        this.diseaseService = diseaseService;
    }

    @GetMapping
    public ApiResponse<List<DiseaseResponse>> getAllDiseases()
    {
        List<DiseaseResponse> diseases =
                diseaseService.getAllDiseases();

        return new ApiResponse<>(
                true,
                diseases.size(),
                diseases
        );
    }

    @GetMapping("/{id}")
    public ApiResponse<DiseaseResponse> getDiseaseById(
            @PathVariable Long id)
    {
        DiseaseResponse disease =
                diseaseService.getDiseaseById(id);

        return new ApiResponse<>(
                true,
                1,
                disease
        );
    }

    @PostMapping
    public ApiResponse<DiseaseResponse> createDisease(
            @Valid @RequestBody DiseaseRequest request)
    {
        DiseaseResponse disease =
                diseaseService.createDisease(request);

        return new ApiResponse<>(
                true,
                1,
                disease
        );
    }

    @PutMapping("/{id}")
    public ApiResponse<DiseaseResponse> updateDisease(
            @PathVariable Long id,
            @Valid @RequestBody DiseaseRequest request)
    {
        DiseaseResponse disease =
                diseaseService.updateDisease(
                        id,
                        request);

        return new ApiResponse<>(
                true,
                1,
                disease
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String> deleteDisease(
            @PathVariable Long id)
    {
        diseaseService.deleteDisease(id);

        return new ApiResponse<>(
                true,
                0,
                "Disease deleted successfully"
        );
    }
}