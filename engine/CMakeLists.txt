add_library(engine STATIC
    al/buffer.cpp
    al/context.cpp
    al/device.cpp
    al/extensions/extension.cpp
    al/extensions/direct_channels.cpp
    al/extensions/events.cpp
    al/extensions/pause_device.cpp
    al/source.cpp
    al/util.cpp
    application.cpp
    application.hpp
    audio_file.cpp
    audio_manager.cpp
    state/manager.cpp
    state/state.cpp
    state/menu.cpp
    streaming_source.cpp
    tts/espeak_ng.cpp
    util.cpp
    )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC espeak-ng fmt glm::glm OpenAL::OpenAL SDL2 SDL2pp sndfile)
target_precompile_headers(engine PUBLIC pch.hpp)
