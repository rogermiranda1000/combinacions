cmake_minimum_required(VERSION 3.5.1)
project(combinacions C)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(combinacions main.c main.h texto.c texto.h lista.h lista.c combinatoria.c combinatoria.h estructuras.h paraleling.c paraleling.h)
target_link_libraries(combinacions m Threads::Threads)