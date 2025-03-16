cmake_minimum_required(VERSION 3.30)

# The toolchain file setup should ideally be in a CMakePresets.json file,
# but we'll keep it here for simplicity
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(MultiRPG VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add dependencies
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# No C++20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# Playground executable
add_executable(MMORPG)

# Playground sources and headers
file(GLOB_RECURSE MMORPG_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

target_sources(MMORPG PRIVATE ${MMORPG_SOURCES})

# Playground include dirs
target_include_directories(MMORPG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Preprocessor defines
target_compile_definitions(MMORPG PRIVATE
    MY_TEST_DEFINE
)

# Automatically links to these libs
target_link_libraries(MMORPG PRIVATE
    sfml-system 
    sfml-network 
    sfml-graphics 
    sfml-window 
    sfml-audio
    ImGui-SFML::ImGui-SFML
    imgui::imgui
)

# Add directories with any random loose .dlls or .libs here
target_link_directories(MMORPG PRIVATE
  
)

# Set configuration properties for Playground
if(MSVC)
    target_compile_options(MMORPG PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(MMORPG PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# Set Playground as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MMORPG)

# Filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${MMORPG_SOURCES})

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)