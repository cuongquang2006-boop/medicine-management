package com.cun.medicine_manager.dto.request;

import jakarta.validation.constraints.DecimalMin;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.math.BigDecimal;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class MedicineRequest {

    @NotBlank
    private String name;

    @NotNull
    @Min(0)
    private Integer stock;

    @NotNull
    @DecimalMin("0.0")
    private BigDecimal price;

}