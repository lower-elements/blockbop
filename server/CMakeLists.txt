add_executable(bbsrv main.cpp)
target_link_libraries(bbsrv fmt)
install(TARGETS bbsrv DESTINATION bin)
