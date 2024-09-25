project(gateserver)
include_directories(../../)
set(src gateserver.h gateserver.cpp gate.toml)
find_package(libmysql)
add_executable(gateserver ${src})


if(WIN32)
    target_link_libraries(gateserver BaseServer uv::uv-static protobuf::libprotobuf-lite libmysql)
set_property(TARGET gateserver PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    target_link_libraries(gateserver BaseServer uv::uv-static protobuf::libprotobuf-lite mysqlclient)
ENDIF(WIN32)
