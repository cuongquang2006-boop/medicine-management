package com.cun.medicine_manager.service;

import com.cun.medicine_manager.dto.response.ClinicResponse;
import com.cun.medicine_manager.entity.Clinic;
import com.cun.medicine_manager.dto.request.ClinicRequest;
import com.cun.medicine_manager.dto.response.PatientResponse;

import com.cun.medicine_manager.repository.ClinicRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ClinicService {

    private final ClinicRepository clinicRepository;

    public ClinicService(ClinicRepository clinicRepository){
        this.clinicRepository = clinicRepository;
    }

    public List<ClinicResponse> getAllClinics(){
        return clinicRepository.findAll().stream().map(
                clinic -> new ClinicResponse(
                        clinic.getId(),
                        clinic.getName(),
                        clinic.getLocation(),
                        clinic.getDescription(),
                        clinic.getCreatedAt() != null ? clinic.getCreatedAt().toString() : ""
                )
        ).toList();
    }

    private ClinicResponse mapToResponse(Clinic clinic){

        return new ClinicResponse(
                clinic.getId(),
                clinic.getName(),
                clinic.getLocation(),
                clinic.getDescription(),
                clinic.getCreatedAt() != null ? clinic.getCreatedAt().toString() : ""
        );
    }

    public Clinic findClinicById(Long id){
        return clinicRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Clinic " + id + " not found"));
    }

    public ClinicResponse getClinicById(Long id) {
        return mapToResponse(findClinicById(id));
    }

    public ClinicResponse createClinic(ClinicRequest req){

        Clinic clinic = new Clinic();

        clinic.setName(req.getName());
        clinic.setLocation(req.getLocation());
        clinic.setDescription(req.getDescription());

        Clinic saveClinic = clinicRepository.save(clinic);

        return mapToResponse(saveClinic);
    }

    public ClinicResponse updateClinic(Long id, ClinicRequest req){

        Clinic clinic = findClinicById(id);

        clinic.setName(req.getName());
        clinic.setLocation(req.getLocation());
        clinic.setDescription(req.getDescription());

        Clinic saveClinic = clinicRepository.save(clinic);

        return mapToResponse(saveClinic);
    }

    public void deleteClinic(Long id){
        Clinic clinic = findClinicById(id);
        clinicRepository.delete(clinic);
    }
}
