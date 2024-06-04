cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME fax-asteroids)
project(${PROJECT_NAME})
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
if(EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE "Emscripten")
    set(PLATFORM Web)
    set(GLFW_BUILD_X11 0)
endif()
# Specify the C++ standard
if (EMSCRIPTEN)
    
    set(USE_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s ASYNCIFY --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/min_shell.html --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")

	set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
    set(CMAKE_CXX_STANDARD 20) 
    set(CMAKE_CXX_STANDARD_REQUIRED ON)


endif()
# Common include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add platform-specific settings
if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/platforms/windows/include)
    link_directories(${CMAKE_SOURCE_DIR}/platforms/windows/lib)
    add_definitions(-DPLATFORM_WINDOWS)
    # Add platform-specific source files
    file(GLOB PLATFORM_SOURCES ${CMAKE_SOURCE_DIR}/platforms/windows/src/*.cpp)

    
# elseif(ANDROID)
#     include_directories(${CMAKE_SOURCE_DIR}/platforms/android/include)
#     link_directories(${CMAKE_SOURCE_DIR}/platforms/android/lib)
#     add_definitions(-DPLATFORM_ANDROID)
#     # Add platform-specific source files
#     set(PLATFORM_SOURCES
#         ${CMAKE_SOURCE_DIR}/platforms/android/src/*.cpp
#     )
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

# Add executable
add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${PLATFORM_SOURCES})

# Link libraries
# if(WIN32)
# #I need to add it manually because it doesn't add it automatically. 
# #but it adds gdi32 and it doesn't make sense.
# target_link_libraries(${PROJECT_NAME} raylib winmm) 
# else()
# target_link_libraries(${PROJECT_NAME} raylib)

# endif()

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} raylib)
elseif(BUILD_SHARED_LIBS)
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} winmm ${CMAKE_SOURCE_DIR}/platforms/windows/lib/raylibdll.lib)
    elseif(UNIX AND NOT ANDROID)
        target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/platforms/linux/lib/libraylib.so)
    endif()
else()
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} winmm ${CMAKE_SOURCE_DIR}/platforms/windows/lib/raylib.lib)
    elseif(UNIX AND NOT ANDROID)
        target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/platforms/linux/lib/libraylib.a)
    endif()
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
