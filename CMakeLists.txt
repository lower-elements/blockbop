cmake_minimum_required(VERSION 3.14)

project(BlockBop)

include(FetchContent)

FetchContent_Declare(
  enet
  URL https://github.com/lsalzman/enet/archive/refs/tags/v1.3.17.tar.gz
  URL_HASH MD5=1c3270f1e03ccb2a8544a88d91d2a368
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  flatbuffers
  URL https://github.com/google/flatbuffers/archive/refs/tags/v23.5.26.tar.gz
  URL_HASH MD5=2ef00eaaa86ab5e9ad5eafe09c2e7b60
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  fmt
  URL https://github.com/fmtlib/fmt/archive/refs/tags/10.2.0.tar.gz
  URL_HASH MD5=683182450c06031d2611d29e1773f3ba
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  SDL2
  URL https://libsdl.org/release/SDL2-2.28.5.tar.gz
  URL_HASH MD5=a344eb827a03045c9b399e99af4af13d
  TLS_VERIFY true
  DOWNLOAD_EXTRACT_TIMESTAMP true
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
)

    FetchContent_MakeAvailable(enet flatbuffers fmt SDL2 SDL2pp)

# Your main project
add_executable(tmp main.cpp)

# Link SDL2 library
target_link_libraries(tmp PRIVATE SDL2::SDL2 enet SDL2pp::SDL2pp fmt::fmt flatbuffers)

