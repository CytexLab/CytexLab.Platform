#
# CytexLab Platform
# Copyright (c) 2026 CytexLab
#
# Данный файл является частью платформы CytexLab и распространяется
# согласно условиям CytexLab Public Community License (CL2P) v1.0.
# Полный текст лицензии доступен в файле LICENSE.txt.
#
# Для получения коммерческой лицензии: programminyka@mail.ru
#

cmake_minimum_required(VERSION 3.20)

# ==========================================
# Project definition
# ==========================================

set(CYTEXLAB_PROJECT CytexLab.Platform)
project(${CYTEXLAB_PROJECT} LANGUAGES ASM C CXX)

# ==========================================
# Configuration
# ==========================================

# Build type
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug")
    message(STATUS "Unset build type. Using build type \"Debug\"")
endif()

if(NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "Release"))
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Supported: Debug, Release")
endif()

# Platform detection
if (WIN32)
    set(CYTEXLAB_PLATFORM "Windows")
elseif(LINUX)
    set(CYTEXLAB_PLATFORM "Linux")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# ==========================================
# Paths
# ==========================================

set(CYTEXLAB_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CYTEXLAB_DIST_EXECUTABLE ${CYTEXLAB_ROOT}/Dist/${CYTEXLAB_PLATFORM}.${CMAKE_BUILD_TYPE})
set(CYTEXLAB_DIST_LIB ${CYTEXLAB_ROOT}/Lib/${CYTEXLAB_PLATFORM}.${CMAKE_BUILD_TYPE})
set(CYTEXLAB_GENERIC_INCLUDE ${CYTEXLAB_ROOT}/Generic/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_EXECUTABLE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_LIB})

# ==========================================
# Compiler setup
# ==========================================

# Register .asm extension for ASM language
list(APPEND CMAKE_ASM_SOURCE_FILE_EXTENSIONS asm)

set(CMAKE_ASM_COMPILER clang)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# ==========================================
# Compiler flags
# ==========================================

# Base flags for C/C++, ASM
set(COMPILER_CXX_BASE_FLAGS
    -nostdlib
    -nostdinc
    -ffreestanding
    -fno-exceptions
    -fno-rtti
    -fno-stack-protector
    -fno-builtin
    -fno-ident
    -fno-asynchronous-unwind-tables
    -fno-unwind-tables
    -fno-use-cxa-atexit
    -fno-threadsafe-statics
    -fno-common
    -masm=intel
)
set(COMPILER_ASM_BASE_FLAGS -masm=intel)

# Build-specific flags
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(COMPILER_CXX_BUILD_FLAGS
        -O0
        -g
        -fno-omit-frame-pointer
        -fno-inline
        -fno-elide-constructors
        -fno-optimize-sibling-calls
        -ggdb3
    )
    set(CYTEXLAB_DEFINE "Debug")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(COMPILER_CXX_BUILD_FLAGS
        -O3
        -g0
        -flto=auto
        -fomit-frame-pointer
        -finline-functions
        -funroll-loops
        -fstrict-aliasing
        -ffast-math
        -fno-math-errno
        -fno-trapping-math
        -fno-rounding-math
    )
    set(CYTEXLAB_DEFINE "CYTEXLAB_RELEASE")
endif()

# Platform-specific flags
if (${CYTEXLAB_PLATFORM} STREQUAL "Windows")
    set(COMPILER_CXX_PLATFORM_FLAGS -target x86_64-pc-windows-msvc -fuse-ld=lld)
    set(PLATFORM_LINKER_FLAGS
        -nostdlib
        -Wl,/NODEFAULTLIB
    )
    set(PLATFORM_LINKER_LIB_FLAGS
        -Wl,/NOENTRY
    )
    set(PLATFORM_LINKER_EXE_FLAGS
        -Wl,/ENTRY:startup
        -Wl,/SUBSYSTEM:CONSOLE
    )
    set(PLATFORM_LIBS ${CYTEXLAB_ROOT}/Generic/WinLibs/ntdll.lib)
elseif(${CYTEXLAB_PLATFORM} STREQUAL "Linux")
    set(PLATFORM_LINKER_FLAGS
        -nostdlib
        -Wl,--gc-sections
        -Wl,--build-id=none
        -Wl,--no-undefined
    )
    set(PLATFORM_LINKER_EXE_FLAGS
        -Wl,--entry=startup
    )
    set(PLATFORM_LIBS "")
endif()

# Combine all C/C++ flags
set(COMPILER_CXX_FLAGS ${COMPILER_CXX_BASE_FLAGS} ${COMPILER_CXX_PLATFORM_FLAGS} ${COMPILER_CXX_BUILD_FLAGS})
set(COMPILER_C_FLAGS ${COMPILER_CXX_BASE_FLAGS} ${COMPILER_CXX_PLATFORM_FLAGS} ${COMPILER_CXX_BUILD_FLAGS})
set(COMPILER_ASM_FLAGS ${COMPILER_ASM_BASE_FLAGS})

# ==========================================
# Functions
# ==========================================

function(platform_add_module NAME FILES INCLUDES DEPS)
    message(STATUS "Module ${NAME}:")
    message(STATUS "  Files: ${FILES}")
    message(STATUS "  Includes: ${INCLUDES}")
    message(STATUS "  Dependencies: ${DEPS}")

    add_library(${NAME} SHARED ${FILES})

    target_include_directories(${NAME} PUBLIC ${INCLUDES} ${CYTEXLAB_GENERIC_INCLUDE})

    target_compile_options(${NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${COMPILER_CXX_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:${COMPILER_C_FLAGS}>
        $<$<COMPILE_LANGUAGE:ASM>:${COMPILER_ASM_FLAGS}>
    )

    target_compile_definitions(${NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${CYTEXLAB_DEFINE}>
        $<$<COMPILE_LANGUAGE:C>:${CYTEXLAB_DEFINE}>
    )

    target_link_libraries(${NAME} PUBLIC ${DEPS} ${PLATFORM_LIBS})

    target_link_options(${NAME} PRIVATE
        ${PLATFORM_LINKER_FLAGS}
        ${PLATFORM_LINKER_LIB_FLAGS}
    )

    set_target_properties(${NAME} PROPERTIES
        PREFIX ""
        SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}"
    )
endfunction()

function(platform_add_executable NAME FILES INCLUDES DEPS)
    message(STATUS "Executable ${NAME}:")
    message(STATUS "  Files: ${FILES}")
    message(STATUS "  Includes: ${INCLUDES}")
    message(STATUS "  Dependencies: ${DEPS}")

    add_executable(${NAME} ${FILES})

    target_include_directories(${NAME} PRIVATE ${INCLUDES} ${CYTEXLAB_GENERIC_INCLUDE})

    target_compile_options(${NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${COMPILER_CXX_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:${COMPILER_C_FLAGS}>
        $<$<COMPILE_LANGUAGE:ASM>:${COMPILER_ASM_FLAGS}>
    )

    target_compile_definitions(${NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${CYTEXLAB_DEFINE}>
        $<$<COMPILE_LANGUAGE:C>:${CYTEXLAB_DEFINE}>
    )

    target_link_libraries(${NAME} PRIVATE ${DEPS} ${PLATFORM_LIBS})

    target_link_options(${NAME} PRIVATE
        ${PLATFORM_LINKER_FLAGS}
        ${PLATFORM_LINKER_EXE_FLAGS}
    )

    # Set executable extension
    if(CYTEXLAB_PLATFORM STREQUAL "Windows")
        set(EXE_SUFFIX ".exe")
    elseif(CYTEXLAB_PLATFORM STREQUAL "Linux")
        set(EXE_SUFFIX ".exec")
    endif()

    set_target_properties(${NAME} PROPERTIES
        PREFIX ""
        SUFFIX "${EXE_SUFFIX}"
    )
endfunction()

# ==========================================
# Functions
# ==========================================

add_subdirectory(${CYTEXLAB_ROOT}/Core)
add_subdirectory(${CYTEXLAB_ROOT}/SystemPlatform)
add_subdirectory(${CYTEXLAB_ROOT}/Test/Dev)

# ==========================================
# Formatting target
# ==========================================

find_program(CLANG_FORMAT_EXECUTABLE clang-format)

if(CLANG_FORMAT_EXECUTABLE)
    file(GLOB_RECURSE FORMAT_SOURCES
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.cxx
        ${CMAKE_SOURCE_DIR}/*.c
        ${CMAKE_SOURCE_DIR}/*.hpp
        ${CMAKE_SOURCE_DIR}/*.h
    )

    # Exclude build directories
    list(FILTER FORMAT_SOURCES EXCLUDE REGEX "/(Build|Dist|Lib|Temp|Doc)/")

    if(FORMAT_SOURCES)
        list(LENGTH FORMAT_SOURCES SRC_COUNT)
        message(STATUS "Found ${SRC_COUNT} source files for formatting")

        add_custom_target(format
            COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${FORMAT_SOURCES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Formatting source files with clang-format"
            VERBATIM
        )
    else()
        message(WARNING "No source files found for formatting")
    endif()
else()
    message(STATUS "clang-format not found (formatting target disabled)")
endif()

# ==========================================
# Printing result
# ==========================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS " CytexLab Platform Configuration")
message(STATUS "========================================")
message(STATUS "  Project:        ${CYTEXLAB_PROJECT}")
message(STATUS "  Build Type:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform:       ${CYTEXLAB_PLATFORM}")
message(STATUS "  Output Dir:     ${CYTEXLAB_DIST_EXECUTABLE}")
message(STATUS "  Library Dir:    ${CYTEXLAB_DIST_LIB}")
message(STATUS "  C++ Compiler:   ${CMAKE_CXX_COMPILER}")
message(STATUS "  C Compiler:     ${CMAKE_C_COMPILER}")
message(STATUS "  ASM Compiler:   ${CMAKE_ASM_COMPILER}")
message(STATUS "========================================")
message(STATUS "")