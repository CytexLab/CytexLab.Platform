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

# ===========================================
# Подготовка корневого проекта
# ===========================================

set(CYTEXLAB_PROJECT CytexLab.Platform)
project(${CYTEXLAB_PROJECT} LANGUAGES ASM C CXX)

# ===========================================
# Проверка типа проекта
# ===========================================

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CYTEXLAB_BUILD_TYPE "Debug")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CYTEXLAB_BUILD_TYPE "Release")
else()
  message(FATAL_ERROR "Не установлен тип сборки")
endif()

# ===========================================
# Проверка компилятора
# ===========================================

if ((NOT ${CMAKE_C_COMPILER_ID} STREQUAL "Clang") OR
	(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") OR
	(NOT ${CMAKE_ASM_COMPILER_ID} STREQUAL "Clang"))
  message(FATAL_ERROR "Используйте компилятор clang для компиляции платформы")
endif()

# ===========================================
# Проверка платформы
# ===========================================

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(CYTEXLAB_PLATFORM "Windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(CYTEXLAB_PLATFORM "Linux")
else()
  message(FATAL_ERROR "Текущая платформа не поддерживается для сборки")
endif()

# ===========================================
# Установка путей для сборки
# ===========================================

set(CYTEXLAB_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CYTEXLAB_DIST_SUFFIX ${CYTEXLAB_PLATFORM}.${CYTEXLAB_BUILD_TYPE})
set(CYTEXLAB_DIST_SHARED ${CYTEXLAB_ROOT}/Dist/${CYTEXLAB_DIST_SUFFIX})
set(CYTEXLAB_DIST_EXEC ${CYTEXLAB_ROOT}/Dist/${CYTEXLAB_DIST_SUFFIX})
set(CYTEXLAB_DIST_LIB ${CYTEXLAB_ROOT}/Lib/${CYTEXLAB_DIST_SUFFIX})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_EXEC})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_SHARED})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CYTEXLAB_DIST_LIB})

# ===========================================
# Подготовка флагов для компиляции
# ===========================================

# Добавляем интерфейс цели
add_library(CompileFlagsLibrary INTERFACE)
add_library(CompileFlagsExecutable INTERFACE)
add_library(CompileDefine INTERFACE)
add_library(LinkFlagsLibrary INTERFACE)
add_library(LinkFlagsExecutable INTERFACE)
add_library(LinkLibs INTERFACE)

# Базовые флаги
set (CYTEXLAB_BASE_C_CXX_FLAGS
  -nostdlib
  -nostdinc
  -ffreestanding
  -fno-rtti
  -fno-exceptions
  -fno-stack-protector
  -fno-builtin
  -fno-ident
  -fno-asynchronous-unwind-tables
  -fno-unwind-tables
  -fno-use-cxa-atexit
  -fno-threadsafe-statics
  -fno-common
  -fvisibility=hidden
  -masm=intel
  -std=c11
  -std=c++11
)
set (CYTEXLAB_BASE_ASM_FLAGS
  -masm=intel
)

# Базовые дефайны
set(CYTEXLAB_DEFINE_BASE 
  "CYTEXLAB_PLATFORM"
  ${CYTEXLAB_PLATFORM}
  ${CYTEXLAB_BUILD_TYPE}
)

# Флаги которые зависят от типа сборки
if (${CYTEXLAB_BUILD_TYPE} STREQUAL "Debug")
  set(CYTEXLAB_ADV1_C_CXX_FLAGS
    -O0
	-g3
	-ggdb
	-fno-omit-frame-pointer
    -fno-inline
    -fno-optimize-sibling-calls
  )
else()
  set(CYTEXLAB_ADV1_C_CXX_FLAGS
    -O3
	-g0
	-fomit-frame-pointer
    -fdata-sections
    -ffunction-sections
    -fmerge-constants
  )
endif()

# Флаги линковщика
set(CYTEXLAB_LINKER_BASE_FLAGS )
set(CYTEXLAB_LINKER_LIB_FLAGS )
set(CYTEXLAB_LINKER_EXEC_FLAGS )

# Флаги которые зависят от платформы
if (${CYTEXLAB_PLATFORM} STREQUAL "Windows")
  set(CYTEXLAB_PLATFORM_LIBS "kernel32" "user32" "shell32" "gdi32")
  set(CYTEXLAB_ADV2_C_CXX_FLAGS 
    -target x86_64-pc-windows-msvc
  )
  set(CYTEXLAB_LINKER_BASE_FLAGS 
    ${CYTEXLAB_LINKER_BASE_FLAGS} 
	-nostdlib 
	-Wl,/NODEFAULTLIB
	-target x86_64-pc-windows-msvc
	-fuse-ld=lld
  )
  set(CYTEXLAB_LINKER_LIB_FLAGS 
    ${CYTEXLAB_LINKER_LIB_FLAGS} 
	-Wl,/NOENTRY
  )
  set(CYTEXLAB_LINKER_EXEC_FLAGS 
    ${CYTEXLAB_LINKER_EXEC_FLAGS} 
	-Wl,/ENTRY:clSysStartup
	-Wl,/SUBSYSTEM:CONSOLE
  )
elseif (${CYTEXLAB_PLATFORM} STREQUAL "Linux")
  set(CYTEXLAB_PLATFORM_LIBS )
  set(CYTEXLAB_ADV2_C_CXX_FLAGS )
  set(CYTEXLAB_LINKER_BASE_FLAGS 
    ${CYTEXLAB_LINKER_BASE_FLAGS} 
    -nostdlib
	-Wl,--gc-sections
	-Wl,--build-id=none
  )
  set(CYTEXLAB_LINKER_EXEC_FLAGS
    ${CYTEXLAB_LINKER_EXEC_FLAGS}
	-Wl,--entry=clSysStartup
	-Wl,--no-undefined
  )
endif()

# Собираем все это вместе
set(CYTEXLAB_C_FLAGS ${CYTEXLAB_BASE_C_CXX_FLAGS} ${CYTEXLAB_ADV1_C_CXX_FLAGS} ${CYTEXLAB_ADV2_C_CXX_FLAGS})
set(CYTEXLAB_CXX_FLAGS ${CYTEXLAB_BASE_C_CXX_FLAGS} ${CYTEXLAB_ADV1_C_CXX_FLAGS} ${CYTEXLAB_ADV2_C_CXX_FLAGS})
set(CYTEXLAB_ASM_FLAGS ${CYTEXLAB_BASE_ASM_FLAGS})

# Собираем все флаги в цели
target_compile_options(CompileFlagsLibrary INTERFACE
  $<$<COMPILE_LANGUAGE:C>:${CYTEXLAB_C_FLAGS}>
  $<$<COMPILE_LANGUAGE:CXX>:${CYTEXLAB_CXX_FLAGS}>
  $<$<COMPILE_LANGUAGE:ASM>:${CYTEXLAB_ASM_FLAGS}>
)

target_compile_options(CompileFlagsExecutable INTERFACE
  $<$<COMPILE_LANGUAGE:C>:${CYTEXLAB_C_FLAGS}>
  $<$<COMPILE_LANGUAGE:CXX>:${CYTEXLAB_CXX_FLAGS}>
  $<$<COMPILE_LANGUAGE:ASM>:${CYTEXLAB_ASM_FLAGS}>
)

target_compile_definitions(CompileDefine INTERFACE
  $<$<COMPILE_LANGUAGE:C>:${CYTEXLAB_DEFINE_BASE}>
  $<$<COMPILE_LANGUAGE:CXX>:${CYTEXLAB_DEFINE_BASE}>
)

target_link_options(LinkFlagsLibrary INTERFACE
  ${CYTEXLAB_LINKER_BASE_FLAGS}
  ${CYTEXLAB_LINKER_LIB_FLAGS}
)

target_link_options(LinkFlagsExecutable INTERFACE
  ${CYTEXLAB_LINKER_BASE_FLAGS}
  ${CYTEXLAB_LINKER_EXEC_FLAGS}
)

target_link_libraries(LinkLibs INTERFACE
  ${CYTEXLAB_PLATFORM_LIBS}
)

# ===========================================
# Добавляем все папки
# ===========================================

add_subdirectory(${CYTEXLAB_ROOT}/Core)
#add_subdirectory(${CYTEXLAB_ROOT}/SystemPlatform)
#add_subdirectory(${CYTEXLAB_ROOT}/Test)

# ===========================================
# Добавляем цель для форматирования
# ===========================================

find_program(CLANG_FORMAT_EXECUTABLE clang-format)

if(CLANG_FORMAT_EXECUTABLE)
    file(GLOB_RECURSE FORMAT_SOURCES
        ${CYTEXLAB_ROOT}/*.cpp
        ${CYTEXLAB_ROOT}/*.cxx
        ${CYTEXLAB_ROOT}/*.c
        ${CYTEXLAB_ROOT}/*.hpp
        ${CYTEXLAB_ROOT}/*.h
    )

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

# ===========================================
# Выводим информацию о сборке
# ===========================================

message(STATUS "===========================================")
message(STATUS "")
message(STATUS "C компилятор: ${CMAKE_C_COMPILER_ID}")
message(STATUS "C++ компилятор: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "ASM компилятор: ${CMAKE_ASM_COMPILER_ID}")
message(STATUS "Тип сборки: ${CYTEXLAB_BUILD_TYPE}")
message(STATUS "Платформа сборки: ${CYTEXLAB_PLATFORM}")
message(STATUS "")
message(STATUS "Путь сборки исполняемых файлов: ${CYTEXLAB_DIST_EXEC}")
message(STATUS "Путь сборки разделяемых библиотек: ${CYTEXLAB_DIST_SHARED}")
message(STATUS "Путь сборки архивных библиотек: ${CYTEXLAB_DIST_LIB}")
message(STATUS "")
message(STATUS "===========================================")
