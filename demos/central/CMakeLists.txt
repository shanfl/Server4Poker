project(centralserver)
include_directories(../../)
set(src centralserver.h centralserver.cpp)

add_executable(centralserver ${src})

target_link_libraries(centralserver BaseServer uv::uv-static protobuf::libprotobuf-lite)
