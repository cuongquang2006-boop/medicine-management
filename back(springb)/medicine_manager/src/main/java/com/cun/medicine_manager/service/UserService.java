package com.cun.medicine_manager.service;

import com.cun.medicine_manager.dto.request.UserLoginRequest;
import com.cun.medicine_manager.dto.request.UserRequest;
import com.cun.medicine_manager.dto.response.UserResponse;

import com.cun.medicine_manager.entity.User;

import com.cun.medicine_manager.repository.UserRepository;

import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

@Service
public class UserService {

    private final UserRepository userRepository;

    public UserService(
            UserRepository userRepository
    ) {
        this.userRepository = userRepository;
    }

    private UserResponse mapToResponse(
            User user
    ) {
        return new UserResponse(
                user.getId(),
                user.getUsername(),
                user.getFullName(),
                user.getRole(),
                user.getCreatedAt() != null
                        ? user.getCreatedAt().toString()
                        : ""
        );
    }

    public User findUserById(
            Long id
    ) {
        return userRepository.findById(id)
                .orElseThrow(
                        () -> new RuntimeException(
                                "User " + id + " not found"
                        )
                );
    }

    public List<UserResponse> getAllUsers()
    {
        return userRepository.findAll()
                .stream()
                .map(this::mapToResponse)
                .toList();
    }

    public UserResponse getUserById(
            Long id
    ) {
        return mapToResponse(
                findUserById(id)
        );
    }

    public UserResponse createUser(
            UserRequest request
    ) {
        User user = new User();

        user.setUsername(
                request.getUsername()
        );

        user.setFullName(
                request.getFullName()
        );

        user.setPasswordHash(
                request.getPassword()
        );

        user.setRole(
                request.getRole()
        );

        user.setFailedAttempts(0);

        user.setLockedUntil(null);

        user.setCreatedAt(
                LocalDateTime.now()
        );

        User savedUser =
                userRepository.save(user);

        return mapToResponse(
                savedUser
        );
    }

    public UserResponse updateUser(
            Long id,
            UserRequest request
    ) {
        User user =
                findUserById(id);

        user.setUsername(
                request.getUsername()
        );

        user.setFullName(
                request.getFullName()
        );

        user.setPasswordHash(
                request.getPassword()
        );

        user.setRole(
                request.getRole()
        );

        User updatedUser =
                userRepository.save(user);

        return mapToResponse(
                updatedUser
        );
    }

    public void deleteUser(
            Long id
    ) {
        User user =
                findUserById(id);

        userRepository.delete(user);
    }

    public Map<String, Object> login(
            UserLoginRequest request
    ) {

        User user = userRepository
                .findByUsername(
                        request.getUsername()
                )
                .orElseThrow(
                        () -> new RuntimeException(
                                "Invalid username"
                        )
                );

        if (
                user.getLockedUntil() != null
                        &&
                        user.getLockedUntil()
                                .isAfter(LocalDateTime.now())
        ) {

            long remainingSeconds =
                    java.time.Duration
                            .between(
                                    LocalDateTime.now(),
                                    user.getLockedUntil()
                            )
                            .getSeconds();

            return Map.of(
                    "success", false,
                    "message", "Account locked",
                    "remaining_seconds",
                    remainingSeconds
            );
        }

        if (
                !user.getPasswordHash()
                        .equals(
                                request.getPassword()
                        )
        ) {

            int failedAttempts =
                    user.getFailedAttempts() + 1;

            LocalDateTime lockedUntil =
                    null;

            if(failedAttempts >= 5)
            {
                lockedUntil =
                        LocalDateTime.now()
                                .plusMinutes(25);

                failedAttempts = 0;
            }

            user.setFailedAttempts(
                    failedAttempts
            );

            user.setLockedUntil(
                    lockedUntil
            );

            userRepository.save(user);

            throw new RuntimeException(
                    "Invalid password"
            );
        }

        user.setFailedAttempts(0);

        user.setLockedUntil(null);

        userRepository.save(user);

        return Map.of(
                "success", true,
                "message", "Login successful",
                "user", Map.of(
                        "id", user.getId(),
                        "username",
                        user.getUsername(),
                        "full_name",
                        user.getFullName(),
                        "role",
                        user.getRole()
                )
        );
    }
}