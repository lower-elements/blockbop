add_executable(blockbop application.cpp main.cpp)
target_link_libraries(blockbop enet espeak-ng flatbuffers fmt OpenAL::OpenAL SDL2::SDL2 SDL2pp sol2)
install(TARGETS blockbop DESTINATION bin)
