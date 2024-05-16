project(gateserver)
include_directories(../)
set(src gateserver.h gateserver.cpp)

add_executable(gateserver ${src})

target_link_libraries(gateserver BaseServer uv::uv-static protobuf::libprotobuf-lite)
