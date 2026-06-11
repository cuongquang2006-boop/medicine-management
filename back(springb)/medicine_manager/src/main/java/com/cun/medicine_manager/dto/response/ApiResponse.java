package com.cun.medicine_manager.dto.response;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor

// tao lop ApiRes voi du lieu thuc the dua ra chua xac dinh
public class ApiResponse<T> {

    // {success : true/false}
    private boolean success;
    // {total : 5}
    private Integer total;
    // cac du lieu can tra ve frontend cua thuc the
    private T data;
}