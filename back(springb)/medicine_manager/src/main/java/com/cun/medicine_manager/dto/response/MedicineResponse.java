package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.math.BigDecimal;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class MedicineResponse {

    private Long id;

    private String name;

    private Integer stock;

    private BigDecimal price;

    private String created_at;

}