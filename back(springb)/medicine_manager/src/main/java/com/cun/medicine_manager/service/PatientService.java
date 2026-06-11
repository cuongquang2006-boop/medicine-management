package com.cun.medicine_manager.service;

import com.cun.medicine_manager.entity.Patient;
import com.cun.medicine_manager.entity.Clinic;

import com.cun.medicine_manager.repository.PatientRepository;
import com.cun.medicine_manager.dto.request.PatientRequest;
import com.cun.medicine_manager.dto.response.PatientResponse;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PatientService {

    private final PatientRepository patientRepository;

    private final ClinicService clinicService;

    public PatientService(PatientRepository patientRepository, ClinicService clinicService){
        this.patientRepository = patientRepository;
        this.clinicService = clinicService;
    }

    public List<PatientResponse> getAllPatients(){
        return patientRepository.findAll().stream().map(
                patient-> new PatientResponse(
                        patient.getId(),
                        patient.getFullName(),
                        patient.getAge(),
                        patient.getGender(),
                        patient.getPhone(),
                        patient.getAddress(),
                        patient.getClinic().getId(),
                        patient.getCreatedAt() != null ? patient.getCreatedAt().toString() : "")
        ).toList();
    }

    private PatientResponse mapToResponse(Patient patient)
    {
        return new PatientResponse(
                patient.getId(),
                patient.getFullName(),
                patient.getAge(),
                patient.getGender(),
                patient.getPhone(),
                patient.getAddress(),
                patient.getClinic().getId(),
                patient.getCreatedAt() != null
                        ? patient.getCreatedAt().toString()
                        : ""
        );
    }

    public Patient findPatientById(Long id)
    {
        return patientRepository.findById(id)
                .orElseThrow(() ->
                        new RuntimeException(
                                "Patient " + id + " not found"));
    }

    public PatientResponse getPatientById(Long id)
    {
        return mapToResponse(findPatientById(id));
    }

    public PatientResponse createPatient(PatientRequest request){

        Patient patient = new Patient();

        patient.setFullName(request.getFullName());
        patient.setAge(request.getAge());
        patient.setGender(request.getGender());
        patient.setPhone(request.getPhone());
        patient.setAddress(request.getAddress());

        Clinic clinic =
                clinicService.findClinicById(request.getClinicId());

        patient.setClinic(clinic);

        Patient savePatient = patientRepository.save(patient);

        return mapToResponse(savePatient);
    }

    public PatientResponse updatePatient(Long id , PatientRequest request){

        Patient ex = findPatientById(id);

        ex.setFullName(request.getFullName());
        ex.setAge(request.getAge());
        ex.setGender(request.getGender());
        ex.setPhone(request.getPhone());
        ex.setAddress(request.getAddress());

        Clinic clinic =
                clinicService.findClinicById(request.getClinicId());

        ex.setClinic(clinic);

        Patient update = patientRepository.save(ex);

        return mapToResponse(update);
    }

    public void deletePatient(Long id){
        Patient patient = findPatientById(id);
        patientRepository.delete(patient);
    }
}