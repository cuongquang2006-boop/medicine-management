package com.cun.medicine_manager.repository;

import com.cun.medicine_manager.entity.Medicine;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface MedicineRepository
        extends JpaRepository<Medicine, Long> {

}