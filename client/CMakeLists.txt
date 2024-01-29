add_executable(blockbop WIN32 blockbop.cpp main.cpp)
target_link_libraries(blockbop PRIVATE SDL2main engine)
install(TARGETS blockbop DESTINATION bin)
