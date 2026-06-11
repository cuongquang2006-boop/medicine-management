package com.cun.medicine_manager.controller;

import com.cun.medicine_manager.dto.response.ApiResponse;
import com.cun.medicine_manager.dto.response.DashboardStatsResponse;
import com.cun.medicine_manager.dto.response.LowStockMedicineResponse;
import com.cun.medicine_manager.dto.response.RecentPrescriptionResponse;

import com.cun.medicine_manager.service.DashboardService;

import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/dashboard")
public class DashboardController {

    private final DashboardService dashboardService;

    public DashboardController(
            DashboardService dashboardService
    ) {
        this.dashboardService = dashboardService;
    }

    @GetMapping("/stats")
    public ApiResponse<DashboardStatsResponse>
    getStats()
    {
        DashboardStatsResponse stats =
                dashboardService.getStats();

        return new ApiResponse<>(
                true,
                1,
                stats
        );
    }

    @GetMapping("/recent-prescriptions")
    public ApiResponse<List<RecentPrescriptionResponse>>
    getRecentPrescriptions()
    {
        List<RecentPrescriptionResponse> data =
                dashboardService
                        .getRecentPrescriptions();

        return new ApiResponse<>(
                true,
                data.size(),
                data
        );
    }

    @GetMapping("/low-stock")
    public ApiResponse<List<LowStockMedicineResponse>>
    getLowStockMedicines()
    {
        List<LowStockMedicineResponse> data =
                dashboardService
                        .getLowStockMedicines();

        return new ApiResponse<>(
                true,
                data.size(),
                data
        );
    }
}