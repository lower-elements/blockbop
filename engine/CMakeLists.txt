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
    state/text_input.cpp
    streaming_source.cpp
    tts/chooser.cpp
    tts/window_title.cpp
    util.cpp
    )
target_precompile_headers(engine PUBLIC pch.hpp)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# Configure-time configuration
if (TARGET espeak-ng)
    target_sources(engine PRIVATE tts/espeak_ng.cpp)
    target_link_libraries(engine PRIVATE espeak-ng)
    set(HAVE_ESPEAK_NG 1)
endif()

configure_file(config.hpp.in config.hpp)

target_link_libraries(engine PUBLIC  fmt glm::glm OpenAL::OpenAL SDL2main SDL2 SDL2pp sndfile)
