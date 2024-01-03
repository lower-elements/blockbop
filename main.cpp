#include <fmt/core.h>
#include <flatbuffers/flatbuffers.h>
#include <enet/enet.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>

int main() {
    fmt::print("ENet version: {:x}\n", enet_linked_version());
    fmt::print("FlatBuffers version: {}\n", flatbuffers::flatbuffers_version_string());
    fmt::print("SDL revision: {}\n", SDL_GetRevision());
    fmt::print("SDL2pp version: {}\n", SDL2PP_VERSION);
    return 0;
}
