cmake_minimum_required(VERSION 3.14)

project(BlockBop
    VERSION 0.1.0
    DESCRIPTION "An accessible 3D voxel game"
    LANGUAGES CXX
    )

# User-writable options
option(BB_USE_ESPEAK_NG "Compile support for the espeak-ng tts provider" ON)
#if (win32)
option(BB_USE_TOLK "Compile support for the Tolk tts provider" ON)
#endif()

# Global project options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# Dependencies
include(FetchContent)
find_package(PkgConfig)

pkg_check_modules(enet libenet)
if(NOT enet_FOUND)
FetchContent_Declare(
  enet
  URL https://github.com/lsalzman/enet/archive/refs/tags/v1.3.17.tar.gz
  URL_HASH MD5=1c3270f1e03ccb2a8544a88d91d2a368
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()

if (BB_USE_ESPEAK_NG)
pkg_check_modules(espeak_ng espeak-ng IMPORTED_TARGET)
if(espeak_ng_FOUND)
    add_library(espeak-ng ALIAS PkgConfig::espeak_ng)
else()
FetchContent_Declare(
  espeak-ng
  # This has to be master right now, as the latest release doesn't include the CMake buildsystem
  URL https://github.com/espeak-ng/espeak-ng/archive/master/espeak-ng-master.tar.gz
  # Subject to change
  #URL_HASH MD5=345228581040d3ae7be4fb1d94e9d279
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()
endif()

FetchContent_Declare(
  flatbuffers
  URL https://github.com/google/flatbuffers/archive/refs/tags/v23.5.26.tar.gz
  URL_HASH MD5=2ef00eaaa86ab5e9ad5eafe09c2e7b60
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES FlatBuffers
)

FetchContent_Declare(
  fmt
  URL https://github.com/fmtlib/fmt/archive/refs/tags/10.2.0.tar.gz
  URL_HASH MD5=683182450c06031d2611d29e1773f3ba
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES fmt
)

FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  URL_HASH MD5=69895110052f0d711c9c54fbf385f6f5
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES glm
)

set(ALSOFT_UTILS OFF CACHE INTERNAL "ALSOFT_UTILS")
set(ALSOFT_NO_CONFIG_UTIL ON CACHE INTERNAL "ALSOFT_NO_CONFIG_UTIL")
set(ALSOFT_EXAMPLES OFF CACHE INTERNAL "ALSOFT_EXAMPLES")
FetchContent_Declare(
    OpenAL
	URL https://github.com/kcat/openal-soft/archive/refs/tags/1.23.1.tar.gz
        URL_HASH MD5=190a60118236644b78488ccab26ebfdf
	TLS_VERIFY ON
	DOWNLOAD_EXTRACT_TIMESTAMP true
        FIND_PACKAGE_ARGS
        )

FetchContent_Declare(
  SDL2
  URL https://libsdl.org/release/SDL2-2.28.5.tar.gz
  URL_HASH MD5=a344eb827a03045c9b399e99af4af13d
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES SDL2 COMPONENTS SDL2main
)

set(SDL2PP_WITH_IMAGE OFF)
set(SDL2PP_WITH_MIXER OFF)
set(SDL2PP_WITH_TTF OFF)
set(SDL2PP_WITH_EXAMPLES OFF)
FetchContent_Declare(
  SDL2pp
  URL https://github.com/libSDL2pp/libSDL2pp/archive/refs/tags/0.18.1.tar.gz
  URL_HASH MD5=fdda5cc37fa831458b16a69edb7c833f
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES SDL2pp
)

pkg_check_modules(SndFile sndfile)
if(NOT SndFile_FOUND)
FetchContent_Declare(
  sndfile
  URL https://github.com/libsndfile/libsndfile/releases/download/1.2.2/libsndfile-1.2.2.tar.xz
  URL_HASH MD5=04e2e6f726da7c5dc87f8cf72f250d04
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()

FetchContent_Declare(
  sol2
  URL https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.tar.gz
  URL_HASH MD5=05021725f7a3e0b91e19250d001deb8e
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
  FIND_PACKAGE_ARGS NAMES sol2
)

FetchContent_MakeAvailable(flatbuffers fmt glm OpenAL SDL2 SDL2pp sol2)
if (NOT enet_FOUND)
    FetchContent_MakeAvailable(enet)
endif()
if (BB_USE_ESPEAK_NG AND NOT espeak_ng_FOUND)
    FetchContent_MakeAvailable(espeak-ng)
endif()
if (NOT SndFile_FOUND)
    FetchContent_MakeAvailable(sndfile)
endif()

# Build the client, server, and their internal support libraries
add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)
