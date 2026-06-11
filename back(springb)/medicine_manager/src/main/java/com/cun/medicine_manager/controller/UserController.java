package com.cun.medicine_manager.controller;

import com.cun.medicine_manager.dto.request.UserLoginRequest;
import com.cun.medicine_manager.dto.request.UserRequest;

import com.cun.medicine_manager.dto.response.ApiResponse;
import com.cun.medicine_manager.dto.response.UserResponse;

import com.cun.medicine_manager.service.UserService;

import jakarta.validation.Valid;

import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/users")
public class UserController {

    private final UserService userService;

    public UserController(
            UserService userService
    ) {
        this.userService = userService;
    }

    @GetMapping
    public ApiResponse<List<UserResponse>>
    getAllUsers()
    {
        List<UserResponse> users =
                userService.getAllUsers();

        return new ApiResponse<>(
                true,
                users.size(),
                users
        );
    }

    @GetMapping("/{id}")
    public ApiResponse<UserResponse>
    getUserById(
            @PathVariable Long id
    )
    {
        UserResponse user =
                userService.getUserById(id);

        return new ApiResponse<>(
                true,
                1,
                user
        );
    }

    @PostMapping
    public ApiResponse<UserResponse>
    createUser(
            @Valid
            @RequestBody
            UserRequest request
    )
    {
        UserResponse user =
                userService.createUser(request);

        return new ApiResponse<>(
                true,
                1,
                user
        );
    }

    @PutMapping("/{id}")
    public ApiResponse<UserResponse>
    updateUser(
            @PathVariable Long id,

            @Valid
            @RequestBody
            UserRequest request
    )
    {
        UserResponse user =
                userService.updateUser(
                        id,
                        request
                );

        return new ApiResponse<>(
                true,
                1,
                user
        );
    }

    @DeleteMapping("/{id}")
    public ApiResponse<String>
    deleteUser(
            @PathVariable Long id
    )
    {
        userService.deleteUser(id);

        return new ApiResponse<>(
                true,
                0,
                "User deleted successfully"
        );
    }

    @PostMapping("/login")
    public Map<String, Object>
    login(
            @RequestBody
            UserLoginRequest request
    )
    {
        return userService.login(request);
    }
}