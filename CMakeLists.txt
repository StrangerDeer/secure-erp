cmake_minimum_required(VERSION 3.26)
project(secure_erp_cpp)

set(CMAKE_CXX_STANDARD 17)
include_directories(model)
include_directories(controller)
include_directories(ui)
include_directories(util)

set(SOURCE_FILES main.cpp
        ui/TerminalView.cpp
        ui/TerminalView.h
        controller/MainController.cpp
        controller/MainController.h
        controller/CRMController.cpp
        controller/CRMController.h
        model/CRMModel.hpp
        DAO/CRMDAO.cpp
        DAO/CRMDAO.h
        util/Util.cpp
        util/Util.h)

add_executable(secure_erp_cpp ${SOURCE_FILES})
