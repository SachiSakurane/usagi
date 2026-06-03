include_guard(GLOBAL)

option(USAGI_ENABLE_SKIA_TESTS "Build Skia-dependent tests" OFF)
option(USAGI_FETCH_SKIA "Clone the pinned Skia checkout into the build directory" OFF)
option(USAGI_BUILD_SKIA "Build the pinned Skia checkout with GN/Ninja" OFF)
option(USAGI_SKIA_WRITE_IMAGES "Write Skia test result images" OFF)

set(USAGI_SKIA_GIT_REPOSITORY "https://skia.googlesource.com/skia.git"
    CACHE STRING "Skia Git repository URL")
set(USAGI_SKIA_GIT_REVISION "b988efa06f8aa3bfeaa18c5b8c716ff244ab43cf"
    CACHE STRING "Pinned Skia Git revision")
set(USAGI_SKIA_ROOT "${CMAKE_BINARY_DIR}/_deps/skia-src"
    CACHE PATH "Skia checkout path")
set(USAGI_SKIA_BUILD_DIR "${USAGI_SKIA_ROOT}/out/usagi-cpu"
    CACHE PATH "Skia build output directory")
set(USAGI_SKIA_LIBRARY "${USAGI_SKIA_BUILD_DIR}/libskia.a"
    CACHE FILEPATH "Skia static library path")
set(USAGI_SKIA_IMAGE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/skia-images"
    CACHE PATH "Directory for Skia test result images")
set(USAGI_SKIA_GN_ARGS
    "is_debug=false is_official_build=true skia_enable_gpu=false skia_enable_pdf=false skia_enable_fontmgr_empty=true skia_enable_fontmgr_fontconfig=false skia_enable_fontmgr_win=false skia_use_fonthost_mac=false skia_use_gl=false skia_use_metal=false skia_use_vulkan=false skia_use_dng_sdk=false skia_use_expat=false skia_use_fontconfig=false skia_use_freetype=false skia_use_icu=false skia_use_jpeg_gainmaps=false skia_use_libjpeg_turbo_decode=false skia_use_libjpeg_turbo_encode=false skia_use_no_jpeg_encode=true skia_use_libpng_decode=false skia_use_libpng_encode=false skia_use_no_png_encode=true skia_use_libwebp_decode=false skia_use_libwebp_encode=false skia_use_no_webp_encode=true"
    CACHE STRING "GN args used when USAGI_BUILD_SKIA is ON")

function(usagi_fetch_skia)
    get_filename_component(USAGI_SKIA_PARENT_DIR "${USAGI_SKIA_ROOT}" DIRECTORY)
    file(MAKE_DIRECTORY "${USAGI_SKIA_PARENT_DIR}")

    if (EXISTS "${USAGI_SKIA_ROOT}/.git")
        execute_process(
            COMMAND git fetch origin
            WORKING_DIRECTORY "${USAGI_SKIA_ROOT}"
            RESULT_VARIABLE USAGI_SKIA_FETCH_RESULT
        )
        if (NOT USAGI_SKIA_FETCH_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to fetch Skia from ${USAGI_SKIA_GIT_REPOSITORY}")
        endif ()
    elseif (EXISTS "${USAGI_SKIA_ROOT}")
        message(FATAL_ERROR
            "USAGI_SKIA_ROOT exists but is not a Git checkout: ${USAGI_SKIA_ROOT}")
    else ()
        execute_process(
            COMMAND git clone "${USAGI_SKIA_GIT_REPOSITORY}" "${USAGI_SKIA_ROOT}"
            RESULT_VARIABLE USAGI_SKIA_CLONE_RESULT
        )
        if (NOT USAGI_SKIA_CLONE_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to clone Skia from ${USAGI_SKIA_GIT_REPOSITORY}")
        endif ()
    endif ()

    execute_process(
        COMMAND git checkout "${USAGI_SKIA_GIT_REVISION}"
        WORKING_DIRECTORY "${USAGI_SKIA_ROOT}"
        RESULT_VARIABLE USAGI_SKIA_CHECKOUT_RESULT
    )
    if (NOT USAGI_SKIA_CHECKOUT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to checkout Skia revision ${USAGI_SKIA_GIT_REVISION}")
    endif ()
endfunction()

function(usagi_build_skia)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)

    if (NOT EXISTS "${USAGI_SKIA_ROOT}/tools/git-sync-deps")
        message(FATAL_ERROR
            "Skia checkout is missing tools/git-sync-deps. Enable USAGI_FETCH_SKIA or set USAGI_SKIA_ROOT.")
    endif ()

    execute_process(
        COMMAND "${Python3_EXECUTABLE}" tools/git-sync-deps
        WORKING_DIRECTORY "${USAGI_SKIA_ROOT}"
        RESULT_VARIABLE USAGI_SKIA_SYNC_DEPS_RESULT
    )
    if (NOT USAGI_SKIA_SYNC_DEPS_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to sync Skia dependencies")
    endif ()

    execute_process(
        COMMAND "${USAGI_SKIA_ROOT}/bin/gn" gen "${USAGI_SKIA_BUILD_DIR}" "--args=${USAGI_SKIA_GN_ARGS}"
        WORKING_DIRECTORY "${USAGI_SKIA_ROOT}"
        RESULT_VARIABLE USAGI_SKIA_GN_RESULT
    )
    if (NOT USAGI_SKIA_GN_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate Skia build files")
    endif ()

    execute_process(
        COMMAND ninja -C "${USAGI_SKIA_BUILD_DIR}" skia
        WORKING_DIRECTORY "${USAGI_SKIA_ROOT}"
        RESULT_VARIABLE USAGI_SKIA_NINJA_RESULT
    )
    if (NOT USAGI_SKIA_NINJA_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build Skia")
    endif ()
endfunction()

function(usagi_configure_skia_target TARGET_NAME)
    if (USAGI_FETCH_SKIA)
        usagi_fetch_skia()
    endif ()

    if (USAGI_BUILD_SKIA)
        usagi_build_skia()
    endif ()

    if (NOT EXISTS "${USAGI_SKIA_ROOT}/include/core/SkCanvas.h")
        message(FATAL_ERROR
            "Skia headers were not found at ${USAGI_SKIA_ROOT}. "
            "Enable USAGI_FETCH_SKIA or set USAGI_SKIA_ROOT.")
    endif ()

    if (NOT EXISTS "${USAGI_SKIA_LIBRARY}")
        message(FATAL_ERROR
            "Skia library was not found at ${USAGI_SKIA_LIBRARY}. "
            "Enable USAGI_BUILD_SKIA or set USAGI_SKIA_LIBRARY.")
    endif ()

    add_library(usagi_skia INTERFACE)
    target_include_directories(usagi_skia INTERFACE "${USAGI_SKIA_ROOT}")
    target_link_libraries(usagi_skia INTERFACE "${USAGI_SKIA_LIBRARY}")

    if (APPLE)
        target_link_libraries(usagi_skia INTERFACE
            "-framework CoreFoundation"
            "-framework CoreGraphics"
            "-framework CoreText"
            "-framework ImageIO"
        )
    endif ()

    if (USAGI_SKIA_WRITE_IMAGES)
        file(MAKE_DIRECTORY "${USAGI_SKIA_IMAGE_OUTPUT_DIR}")
        target_compile_definitions(${TARGET_NAME} PRIVATE
            USAGI_SKIA_WRITE_IMAGES=1
            USAGI_SKIA_IMAGE_OUTPUT_DIR="${USAGI_SKIA_IMAGE_OUTPUT_DIR}"
        )
    endif ()

    target_link_libraries(${TARGET_NAME} PRIVATE usagi_skia)
endfunction()
