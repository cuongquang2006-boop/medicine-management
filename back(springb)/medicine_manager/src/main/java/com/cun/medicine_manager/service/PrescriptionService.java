package com.cun.medicine_manager.service;

import com.cun.medicine_manager.entity.Prescription;
import com.cun.medicine_manager.entity.Patient;
import com.cun.medicine_manager.entity.Disease;
import com.cun.medicine_manager.entity.User;

import com.cun.medicine_manager.repository.PrescriptionRepository;

import com.cun.medicine_manager.dto.request.PrescriptionRequest;
import com.cun.medicine_manager.dto.response.PrescriptionResponse;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PrescriptionService {

    private final PrescriptionRepository prescriptionRepository;

    private final PatientService patientService;

    private final DiseaseService diseaseService;

    private final UserService userService;

    public PrescriptionService(
            PrescriptionRepository prescriptionRepository,
            PatientService patientService,
            DiseaseService diseaseService,
            UserService userService)
    {
        this.prescriptionRepository = prescriptionRepository;
        this.patientService = patientService;
        this.diseaseService = diseaseService;
        this.userService = userService;
    }

    public List<PrescriptionResponse> getAllPrescriptions()
    {
        return prescriptionRepository.findAll()
                .stream()
                .map(this::mapToResponse)
                .toList();
    }

    private PrescriptionResponse mapToResponse(
            Prescription prescription)
    {
        return new PrescriptionResponse(
                prescription.getId(),

                prescription.getPatient().getId(),

                prescription.getDisease().getId(),

                prescription.getCreatedBy().getId(),

                prescription.getPatient().getFullName(),

                prescription.getDisease().getName(),

                prescription.getCreatedBy().getFullName(),

                prescription.getDiagnosis(),

                prescription.getCreatedAt() != null
                        ? prescription.getCreatedAt().toString()
                        : ""
        );
    }

    private Prescription findPrescriptionById(
            Long id)
    {
        return prescriptionRepository.findById(id)
                .orElseThrow(() ->
                        new RuntimeException(
                                "Prescription "
                                        + id
                                        + " not found"));
    }

    public PrescriptionResponse getPrescriptionById(
            Long id)
    {
        return mapToResponse(
                findPrescriptionById(id)
        );
    }

    public PrescriptionResponse createPrescription(
            PrescriptionRequest request)
    {
        Prescription prescription =
                new Prescription();

        Patient patient =
                patientService.findPatientById(
                        request.getPatientId());

        Disease disease =
                diseaseService.findDiseaseById(
                        request.getDiseaseId());

        User doctor =
                userService.findUserById(
                        request.getCreatedBy());

        prescription.setPatient(patient);

        prescription.setDisease(disease);

        prescription.setCreatedBy(doctor);

        prescription.setDiagnosis(
                request.getDiagnosis());

        Prescription saved =
                prescriptionRepository.save(
                        prescription);

        return mapToResponse(saved);
    }

    public void deletePrescription(Long id)
    {
        Prescription prescription =
                findPrescriptionById(id);

        prescriptionRepository.delete(
                prescription);
    }
}