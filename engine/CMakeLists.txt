add_library(engine STATIC
    application.cpp
    application.hpp
    )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC SDL2 SDL2pp)
