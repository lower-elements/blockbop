add_library(engine STATIC
    al/buffer.cpp
    al/context.cpp
    al/device.cpp
    al/source.cpp
    al/util.cpp
    application.cpp
    application.hpp
    audio_file.cpp
    audio_file.hpp
    state/manager.cpp
    state/state.cpp
    state/menu.cpp
    tts/espeak_ng.cpp
    )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC espeak-ng fmt OpenAL::OpenAL SDL2 SDL2pp sndfile)
