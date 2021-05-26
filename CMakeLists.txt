cmake_minimum_required(VERSION 3.5.1)

project(barcode)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
     
#generate project binary
add_executable(
    ${PROJECT_NAME}
        ${INC_DIR}/LightDataReader.h
        ${INC_DIR}/Interpreter.h
        ${INC_DIR}/Decoder.h
        ${INC_DIR}/Validation.h
        ${INC_DIR}/ErrorChecks.h
        ${INC_DIR}/StringUtil.h
        
        
        ${SRC_DIR}/main.c
        ${SRC_DIR}/LightDataReader.c
        ${SRC_DIR}/Interpreter.c
        ${SRC_DIR}/Decoder.c
        ${SRC_DIR}/Validation.c
        ${SRC_DIR}/ErrorChecks.c
        ${SRC_DIR}/StringUtil.c
        )

target_include_directories(
    ${PROJECT_NAME} 
        PRIVATE 
            ${INC_DIR}
)  
