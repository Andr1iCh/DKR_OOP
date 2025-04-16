cmake_minimum_required(VERSION 3.16)

project(DKR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-msse4.2 -maes -mpclmul -mavx -mavx2 -msha)
endif()
option(CRYPTOPP_BUILD_TESTING OFF)
option(CRYPTOPP_DISABLE_ASM OFF)
option(CRYPTOPP_DISABLE_SSE3 OFF)
option(CRYPTOPP_DISABLE_SSSE3 OFF)
option(CRYPTOPP_DISABLE_SSE4 OFF)
option(CRYPTOPP_DISABLE_CLMUL OFF)
option(CRYPTOPP_DISABLE_AESNI OFF)
option(CRYPTOPP_DISABLE_AVX OFF)
option(CRYPTOPP_DISABLE_AVX2 OFF)
option(CRYPTOPP_DISABLE_SHANI OFF)
set(CRYPTOPP_BUILD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/lib/cryptopp-cmake/cryptopp")
set(CRYPTOPP_DISABLE_ASM ON  CACHE BOOL "No ASM for MinGW‑64" FORCE)
add_subdirectory(lib/cryptopp-cmake/cryptopp)                            #


include_directories(${CMAKE_SOURCE_DIR}/cryptopp)  #

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES DKR_en_150.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    lib/cryptopp-cmake/cryptopp/cpu.cpp
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DKR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        customer.h customer.cpp
        logger.h logger.cpp
        customers.h customers.cpp
        sorter.h sorter.cpp
        searcher.h searcher.cpp
    )

    target_link_libraries(DKR PRIVATE Qt6::Widgets cryptopp::cryptopp)   #

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(DKR SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DKR
            ${PROJECT_SOURCES}
        )
    endif()

    # ⬅️ додано лінкування з cryptopp у гілці Qt5
    target_link_libraries(DKR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cryptopp::cryptopp)   # ⬅️ додано

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# ❌ Замість цього виклику, ми тепер додаємо target_link_libraries в обох гілках умов
# target_link_libraries(DKR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DKR)
endif()
set_target_properties(DKR PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DKR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DKR)
endif()
