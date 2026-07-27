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

set(CYTEXLAB_PROJECT CytexLab.Platform)
project(${CYTEXLAB_PROJECT} LANGUAGES ASM C CXX)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(CYTEXLAB_BUILD "Debug")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
set(CYTEXLAB_BUILD "Release")
else()
message(FATAL_ERROR "Invalid build type")
endif()

if (WIN32)
set(CYTEXLAB_PLATFORM "Windows")
elseif(UNIX AND NOT APPLE)
set(CYTEXLAB_PLATFORM "Linux")
else()
message(FATAL_ERROR "Unsupported platform")
endif()

set(CYTEXLAB_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CYTEXLAB_EXEC ${CYTEXLAB_ROOT}/Dist/${CYTEXLAB_PLATFORM}.${CYTEXLAB_BUILD})
set(CYTEXLAB_LIB ${CYTEXLAB_ROOT}/Lib/${CYTEXLAB_PLATFORM}.${CYTEXLAB_BUILD})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CYTEXLAB_EXEC})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CYTEXLAB_LIB})

set(CXX_BASE_FLAGS
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
)

if (WIN32)
    set(LINK_BASE_FLAGS
        -nostdlib
        -Wl,/ENTRY:startup
        -Wl,/NODEFAULTLIB
        -Wl,/SUBSYSTEM:CONSOLE
    )
else()
    set(LINK_BASE_FLAGS
        -nostdlib
        -Wl,--gc-sections
        -Wl,--entry=startup
        -Wl,--build-id=none
        -Wl,--no-undefined
    )
endif()

if (${CYTEXLAB_BUILD} STREQUAL "Debug")
	set(CXX_EXTRA_FLAGS
		-O0
		-g
		-fno-omit-frame-pointer
		-fno-inline
		-fno-elide-constructors
		-fno-optimize-sibling-calls
		-ggdb3
		-UNDEBUG
	)
	set(CYTEXLAB_DEFINE "CYTEXLAB_DEBUG")
elseif (${CYTEXLAB_BUILD} STREQUAL "Release")
	set(CXX_EXTRA_FLAGS
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
		-DNDEBUG
	)
	set(CYTEXLAB_DEFINE "CYTEXLAB_RELEASE")
endif()

if (${CYTEXLAB_PLATFORM} STREQUAL "Windows")
    set(CXX_BASE_FLAGS ${CXX_BASE_FLAGS} -target x86_64-pc-windows-msvc -fuse-ld=lld)
	set(CYTEXLAB_PLATFORM_LIBS kernel32 user32 gdi32 opengl32)
elseif (${CYTEXLAB_PLATFORM} STREQUAL "Linux")
	set(CYTEXLAB_PLATFORM_LIBS "")
endif()

function (platform_add_module name files includes deps)
	message("Module ${name}: ")
	message("- Files: ${files}")
	message("- Includes: ${includes}")
	message("- Deps: ${deps}")
	
	add_library(${name} STATIC ${files})
	target_include_directories(${name} PUBLIC ${includes})
	target_compile_options(${name} PRIVATE ${CXX_BASE_FLAGS} ${CXX_EXTRA_FLAGS})
	target_link_libraries(${name} PUBLIC ${deps} ${CYTEXLAB_PLATFORM_LIBS})
	target_compile_definitions(${name} PRIVATE ${CYTEXLAB_DEFINE})
	set_target_properties(${name} PROPERTIES prefix "")
	set_target_properties(${name} PROPERTIES suffix ".a")
endfunction()

function (platform_add_executable name files includes deps)
	message("Executable ${name}: ")
	message("- Files: ${files}")
	message("- Includes: ${includes}")
	message("- Deps: ${deps}")
	
	add_executable(${name} ${files})
	target_include_directories(${name} PRIVATE ${includes})
	target_compile_options(${name} PRIVATE ${CXX_BASE_FLAGS} ${CXX_EXTRA_FLAGS})
	target_compile_definitions(${name} PRIVATE ${CYTEXLAB_DEFINE})
	target_link_libraries(${name} PRIVATE ${deps} ${CYTEXLAB_PLATFORM_LIBS})
	target_link_options(${name} PRIVATE ${LINK_BASE_FLAGS})
	set_target_properties(${name} PROPERTIES prefix "")
	
	if (${CYTEXLAB_PLATFORM} STREQUAL "Windows")
		set_target_properties(${name} PROPERTIES suffix ".exe")
	elseif(${CYTEXLAB_PLATFORM} STREQUAL "Linux")
		set_target_properties(${name} PROPERTIES suffix ".exec")
	endif()
endfunction()
