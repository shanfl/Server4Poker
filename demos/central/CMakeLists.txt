project(centralserver)
include_directories(../../)
set(src centralserver.h centralserver.cpp central.toml)

add_executable(centralserver ${src})

target_link_libraries(centralserver BaseServer uv::uv-static protobuf::libprotobuf-lite)
