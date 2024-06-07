cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME fax-asteroids)
project(${PROJECT_NAME})
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(DEFAULT_SHELL "Use default html page" OFF)


include_directories(${CMAKE_SOURCE_DIR}/deps) 
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/core)
include_directories(${CMAKE_SOURCE_DIR}/src/scenes)
include_directories(${CMAKE_SOURCE_DIR}/src/components)

if(EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE "Emscripten")
    set(PLATFORM Web)
    set(GLFW_BUILD_X11 0)
endif()
# Specify the C++ standard
if (EMSCRIPTEN)
    if(DEFAULT_SHELL)
        set(USE_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH  --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/")
    else()
        set(USE_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/min_shell.html --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")

	set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
    set(CMAKE_CXX_STANDARD 20) 
    set(CMAKE_CXX_STANDARD_REQUIRED ON)


endif()
# Common include directories


# Add platform-specific settings
if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/platforms/windows/include)
    link_directories(${CMAKE_SOURCE_DIR}/platforms/windows/lib)
    add_definitions(-DPLATFORM_WINDOWS)
    # Add platform-specific source files
    file(GLOB PLATFORM_SOURCES ${CMAKE_SOURCE_DIR}/platforms/windows/src/*.cpp)


elseif(EMSCRIPTEN)
    include_directories(${CMAKE_SOURCE_DIR}/platforms/wasm/include)
    link_directories(${CMAKE_SOURCE_DIR}/platforms/wasm/lib)
    add_definitions(-DPLATFORM_WASM)
    
    
    # Add platform-specific source files
    file(GLOB PLATFORM_SOURCES ${CMAKE_SOURCE_DIR}/platforms/wasm/src/*.cpp)
elseif(UNIX AND NOT ANDROID)
    include_directories(${CMAKE_SOURCE_DIR}/platforms/linux/include)
    link_directories(${CMAKE_SOURCE_DIR}/platforms/linux/lib)
    add_definitions(-DPLATFORM_LINUX)
    # Add platform-specific source files
    file(GLOB PLATFORM_SOURCES ${CMAKE_SOURCE_DIR}/platforms/linux/src/*.cpp)
endif()

# Add common source files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    # ${CMAKE_SOURCE_DIR}/src/common_source.cpp
)

file(GLOB CORE_SOURCES ${CMAKE_SOURCE_DIR}/src/core/*.cpp)
# recursively, include everything in scenes
file(GLOB_RECURSE  SCENES_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/scenes/*.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${CORE_SOURCES} ${SCENES_SOURCES} ${PLATFORM_SOURCES})


if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} raylib)
elseif(BUILD_SHARED_LIBS)
    if(WIN32)
        target_link_libraries(${PROJECT_NAME}  ${CMAKE_SOURCE_DIR}/platforms/windows/lib/raylibdll.lib winmm)
    elseif(UNIX AND NOT ANDROID)
        target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/platforms/linux/lib/libraylib.so)
    endif()
else()
    if(WIN32)
        target_link_libraries(${PROJECT_NAME}  ${CMAKE_SOURCE_DIR}/platforms/windows/lib/raylib.lib winmm)
    elseif(UNIX AND NOT ANDROID)
        target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/platforms/linux/lib/libraylib.a)
    endif()
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
