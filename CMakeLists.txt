cmake_minimum_required(VERSION 3.0)

project(pi_drone_client)

add_executable(pi_drone_client main.cpp)

install(TARGETS pi_drone_client RUNTIME DESTINATION bin)


find_library(PTHREAD pthread)
add_library(client_pi STATIC client_sock.cpp client_sock.hpp)
target_link_libraries(pi_drone_client PUBLIC client_pi ${PTHREAD})
