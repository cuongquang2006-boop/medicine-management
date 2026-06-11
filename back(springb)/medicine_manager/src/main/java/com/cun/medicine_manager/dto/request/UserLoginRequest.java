package com.cun.medicine_manager.dto.request;

import lombok.Data;

@Data
public class UserLoginRequest {

    private String username;

    private String password;
}