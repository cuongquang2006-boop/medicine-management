package com.cun.medicine_manager.controller;

import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;

import com.cun.medicine_manager.service.MedicineService;

import com.cun.medicine_manager.dto.request.MedicineRequest;
import com.cun.medicine_manager.dto.response.MedicineResponse;
import com.cun.medicine_manager.dto.response.ApiResponse;

import java.util.List;

@RestController
@RequestMapping("/api/medicines")
public class MedicineController {

    private final MedicineService medicineService;

    public MedicineController(
            MedicineService medicineService)
    {
        this.medicineService = medicineService;
    }

    @GetMapping
    public ApiResponse<List<MedicineResponse>> getAllMedicines()
    {
        List<MedicineResponse> medicines =
                medicineService.getAllMedicines();

        return new ApiResponse<>(
                true,
                medicines.size(),
                medicines
        );
    }

    @GetMapping("/{id}")
    public ApiResponse<MedicineResponse> getMedicineById(
            @PathVariable Long id)
    {
        MedicineResponse medicine =
                medicineService.getMedicineById(id);

        return new ApiResponse<>(
                true,
                1,
                medicine
        );
    }

    @PostMapping
    public ApiResponse<MedicineResponse> createMedicine(
            @Valid @RequestBody MedicineRequest request)
    {
        MedicineResponse medicine =
                medicineService.createMedicine(request);

        return new ApiResponse<>(
                true,
                1,
                medicine
        );
    }

    @PutMapping("/{id}")
    public ApiResponse<MedicineResponse> updateMedicine(
            @PathVariable Long id,
            @Valid @RequestBody MedicineRequest request)
    {
        MedicineResponse medicine =
                medicineService.updateMedicine(
                        id,
                        request);

        return new ApiResponse<>(
                true,
                1,
                medicine
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String> deleteMedicine(
            @PathVariable Long id)
    {
        medicineService.deleteMedicine(id);

        return new ApiResponse<>(
                true,
                0,
                "Medicine deleted successfully"
        );
    }
}