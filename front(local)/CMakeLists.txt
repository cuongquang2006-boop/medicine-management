cmake_minimum_required(VERSION 3.19)
project(front_end LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    Network
)

qt_standard_project_setup()

qt_add_executable(front_end
    WIN32 MACOSX_BUNDLE

    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    DashboardWidget.h
    DashboardWidget.cpp

    PatientWidget.h
    PatientWidget.cpp

    MedicineWidget.h
    MedicineWidget.cpp

    PrescriptionWidget.h
    PrescriptionWidget.cpp

    ClinicWidget.h
    ClinicWidget.cpp

    DiseaseWidget.h
    DiseaseWidget.cpp

    UserWidget.h
    UserWidget.cpp

    LoginWindow.h
    LoginWindow.cpp

    PatientService.h
    PatientService.cpp
    PatientModel.h
    ClinicModel.h
    ClinicService.h
    ClinicService.cpp
    DiseaseModel.h
    DiseaseService.h
    DiseaseService.cpp
    MedicineModel.h
    MedicineService.h
    MedicineService.cpp
    PrescriptionModel.h
    PrescriptionService.h
    PrescriptionService.cpp
    UserModel.h
    UserService.h
    UserService.cpp
    AuthService.h
    AuthService.cpp
    RegisterDialog.h
    RegisterDialog.cpp
    DashboardService.h
    DashboardService.cpp
)

target_link_libraries(front_end
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS front_end
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET front_end
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})