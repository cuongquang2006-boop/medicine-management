package com.cun.medicine_manager.repository;

import com.cun.medicine_manager.entity.Patient;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PatientRepository extends JpaRepository <Patient,Long>{

}