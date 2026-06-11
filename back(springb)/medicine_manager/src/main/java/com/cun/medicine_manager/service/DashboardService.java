package com.cun.medicine_manager.service;

import com.cun.medicine_manager.dto.response.DashboardStatsResponse;
import com.cun.medicine_manager.dto.response.LowStockMedicineResponse;
import com.cun.medicine_manager.dto.response.RecentPrescriptionResponse;

import com.cun.medicine_manager.entity.Medicine;
import com.cun.medicine_manager.entity.Prescription;

import com.cun.medicine_manager.repository.ClinicRepository;
import com.cun.medicine_manager.repository.MedicineRepository;
import com.cun.medicine_manager.repository.PatientRepository;
import com.cun.medicine_manager.repository.PrescriptionRepository;

import org.springframework.stereotype.Service;

import java.util.Comparator;
import java.util.List;

@Service
public class DashboardService {

    private final PatientRepository patientRepository;

    private final MedicineRepository medicineRepository;

    private final ClinicRepository clinicRepository;

    private final PrescriptionRepository prescriptionRepository;

    public DashboardService(
            PatientRepository patientRepository,
            MedicineRepository medicineRepository,
            ClinicRepository clinicRepository,
            PrescriptionRepository prescriptionRepository
    ) {
        this.patientRepository = patientRepository;
        this.medicineRepository = medicineRepository;
        this.clinicRepository = clinicRepository;
        this.prescriptionRepository = prescriptionRepository;
    }

    public DashboardStatsResponse getStats()
    {
        return new DashboardStatsResponse(
                patientRepository.count(),
                medicineRepository.count(),
                clinicRepository.count(),
                prescriptionRepository.count()
        );
    }

    public List<RecentPrescriptionResponse>
    getRecentPrescriptions()
    {
        return prescriptionRepository.findAll()
                .stream()
                .sorted(
                        Comparator.comparing(
                                Prescription::getCreatedAt
                        ).reversed()
                )
                .limit(5)
                .map(p ->
                        new RecentPrescriptionResponse(
                                p.getPatient().getFullName(),
                                p.getDisease().getName(),
                                0,
                                p.getCreatedAt() != null
                                        ? p.getCreatedAt().toString()
                                        : ""
                        )
                )
                .toList();
    }

    public List<LowStockMedicineResponse>
    getLowStockMedicines()
    {
        return medicineRepository.findAll()
                .stream()
                .filter(m ->
                        m.getStock() <= 5
                )
                .map(m ->
                        new LowStockMedicineResponse(
                                m.getName(),
                                m.getStock()
                        )
                )
                .toList();
    }
}