cmake_minimum_required(VERSION 2.8)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

file(COPY cfg/config.cfg DESTINATION src)
file(COPY cfg/config.cfg DESTINATION test)
