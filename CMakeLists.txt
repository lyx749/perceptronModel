cmake_minimum_required(VERSION 3.0.0)
project(perceptron_model VERSION 0.1.0)
include_directories(src)
include(CTest)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(CMAKE_CXX_STANDARD 17)
set(operatingMode 0) #1 is or   0 is and
configure_file(config.h.in ${CMAKE_SOURCE_DIR}/src/config.h @ONLY)
add_executable(perceptron_model main.cpp)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
