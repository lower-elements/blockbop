add_executable(blockbop blockbop.cpp main.cpp)
target_link_libraries(blockbop PRIVATE engine)
install(TARGETS blockbop DESTINATION bin)
