add_library(engine STATIC
    al/buffer.cpp
    al/context.cpp
    al/device.cpp
    al/util.cpp
    application.cpp
    application.hpp
    )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC OpenAL::OpenAL SDL2 SDL2pp)
