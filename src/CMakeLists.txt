add_executable(SpaceTraders WIN32 )

file(GLOB_RECURSE SOURCE_FILES *.hpp *.cpp */*.hpp */*.cpp)
target_sources(SpaceTraders PRIVATE ${SOURCE_FILES})

find_package(imgui CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries( SpaceTraders
    PUBLIC
        imgui::imgui
        SDL2::SDL2
        d3d11
        nlohmann_json::nlohmann_json
        OpenSSL::SSL OpenSSL::Crypto
)

target_include_directories( SpaceTraders
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CPP_HTTPLIB_INCLUDE_DIRS}
)

target_compile_definitions( SpaceTraders
    PUBLIC
        IMGUI_DEFINE_MATH_OPERATORS
)

if (WIN32)
    target_compile_definitions( SpaceTraders
        PRIVATE
            WIN32_LEAN_AND_MEAN
            NOMINMAX
    )
endif()