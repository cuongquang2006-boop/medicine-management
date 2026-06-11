package com.cun.medicine_manager.service;

import com.cun.medicine_manager.entity.Medicine;

import com.cun.medicine_manager.repository.MedicineRepository;

import com.cun.medicine_manager.dto.request.MedicineRequest;
import com.cun.medicine_manager.dto.response.MedicineResponse;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MedicineService {

    private final MedicineRepository medicineRepository;

    public MedicineService(
            MedicineRepository medicineRepository)
    {
        this.medicineRepository = medicineRepository;
    }

    public List<MedicineResponse> getAllMedicines()
    {
        return medicineRepository.findAll()
                .stream()
                .map(this::mapToResponse)
                .toList();
    }

    private MedicineResponse mapToResponse(
            Medicine medicine)
    {
        return new MedicineResponse(
                medicine.getId(),
                medicine.getName(),
                medicine.getStock(),
                medicine.getPrice(),
                medicine.getCreatedAt() != null
                        ? medicine.getCreatedAt().toString()
                        : ""
        );
    }

    private Medicine findMedicineById(Long id)
    {
        return medicineRepository.findById(id)
                .orElseThrow(() ->
                        new RuntimeException(
                                "Medicine " + id + " not found"));
    }

    public MedicineResponse getMedicineById(Long id)
    {
        return mapToResponse(
                findMedicineById(id)
        );
    }

    public MedicineResponse createMedicine(
            MedicineRequest request)
    {
        Medicine medicine = new Medicine();

        medicine.setName(
                request.getName());

        medicine.setStock(
                request.getStock());

        medicine.setPrice(
                request.getPrice());

        Medicine savedMedicine =
                medicineRepository.save(medicine);

        return mapToResponse(savedMedicine);
    }

    public MedicineResponse updateMedicine(
            Long id,
            MedicineRequest request)
    {
        Medicine ex =
                findMedicineById(id);

        ex.setName(
                request.getName());

        ex.setStock(
                request.getStock());

        ex.setPrice(
                request.getPrice());

        Medicine updatedMedicine =
                medicineRepository.save(ex);

        return mapToResponse(updatedMedicine);
    }

    public void deleteMedicine(Long id)
    {
        Medicine medicine =
                findMedicineById(id);

        medicineRepository.delete(medicine);
    }
}