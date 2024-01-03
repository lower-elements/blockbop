add_executable(blockbop main.cpp)
target_link_libraries(blockbop PRIVATE engine)
install(TARGETS blockbop DESTINATION bin)
