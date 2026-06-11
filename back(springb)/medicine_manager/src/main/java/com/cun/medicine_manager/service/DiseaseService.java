package com.cun.medicine_manager.service;

import com.cun.medicine_manager.entity.Disease;
import com.cun.medicine_manager.entity.Clinic;

import com.cun.medicine_manager.repository.DiseaseRepository;

import com.cun.medicine_manager.dto.request.DiseaseRequest;
import com.cun.medicine_manager.dto.response.DiseaseResponse;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class DiseaseService {

    private final DiseaseRepository diseaseRepository;

    private final ClinicService clinicService;

    public DiseaseService(DiseaseRepository diseaseRepository, ClinicService clinicService)
    {
        this.diseaseRepository = diseaseRepository;
        this.clinicService = clinicService;
    }

    public List<DiseaseResponse> getAllDiseases()
    {
        return diseaseRepository.findAll()
                .stream()
                .map(this::mapToResponse)
                .toList();
    }

    private DiseaseResponse mapToResponse(
            Disease disease)
    {
        return new DiseaseResponse(
                disease.getId(),
                disease.getName(),
                disease.getClinic().getName(),
                disease.getSymptoms(),
                disease.getDescription(),
                disease.getCreatedAt() != null
                        ? disease.getCreatedAt().toString()
                        : ""
        );
    }

    public Disease findDiseaseById(Long id)
    {
        return diseaseRepository.findById(id)
                .orElseThrow(() ->
                        new RuntimeException(
                                "Disease " + id + " not found"));
    }

    public DiseaseResponse getDiseaseById(Long id)
    {
        return mapToResponse(findDiseaseById(id));
    }

    public DiseaseResponse createDisease(
            DiseaseRequest request)
    {
        Disease disease = new Disease();

        disease.setName(request.getName());

        disease.setSymptoms(request.getSymptoms());

        disease.setDescription(request.getDescription());

        Clinic clinic = clinicService.findClinicById(request.getClinicId());

        disease.setClinic(clinic);

        Disease savedDisease = diseaseRepository.save(disease);

        return mapToResponse(savedDisease);
    }

    public DiseaseResponse updateDisease(Long id, DiseaseRequest request)
    {
        Disease ex = findDiseaseById(id);

        ex.setName(request.getName());

        ex.setSymptoms(request.getSymptoms());

        ex.setDescription(request.getDescription());

        Clinic clinic = clinicService.findClinicById(request.getClinicId());

        ex.setClinic(clinic);

        Disease updatedDisease = diseaseRepository.save(ex);

        return mapToResponse(updatedDisease);
    }

    public void deleteDisease(Long id)
    {
        Disease disease = findDiseaseById(id);

        diseaseRepository.delete(disease);
    }
}