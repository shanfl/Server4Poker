project(login)
include_directories(../../)
set(src login.h login.cpp login.toml)

add_executable(login ${src})

target_link_libraries(login BaseServer uv::uv-static protobuf::libprotobuf-lite)
