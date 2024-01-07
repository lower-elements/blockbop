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
    )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC sndfile OpenAL::OpenAL SDL2 SDL2pp)
