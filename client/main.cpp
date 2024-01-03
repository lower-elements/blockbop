#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <alc.h>
#include <enet/enet.h>
#include <espeak-ng/speak_lib.h>
#include <flatbuffers/flatbuffers.h>
#include <fmt/core.h>
#include <sol/version.hpp>

int main() {
  int openal_major, openal_minor;
  alcGetIntegerv(nullptr, ALC_MAJOR_VERSION, 1, &openal_major);
  alcGetIntegerv(nullptr, ALC_MINOR_VERSION, 1, &openal_minor);
  fmt::print("ENet version: {:x}\n", enet_linked_version());
  fmt::print("espeak-ng version: {}\n", espeak_Info(nullptr));
  fmt::print("FlatBuffers version: {}\n",
             flatbuffers::flatbuffers_version_string());
  fmt::print("OpenAL version: {}.{}\n", openal_major, openal_minor);
  fmt::print("SDL revision: {}\n", SDL_GetRevision());
  fmt::print("SDL2pp version: {}\n", SDL2PP_VERSION);
  fmt::print("sol2 version: {}\n", SOL_VERSION_STRING);
  return 0;
}
