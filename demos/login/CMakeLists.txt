project(login)
include_directories(../../)
set(src login.h login.cpp login.toml)

add_executable(login ${src})

target_link_libraries(login BaseServer uv::uv-static protobuf::libprotobuf-lite mysqlclient)
if(WIN32)
set_property(TARGET login PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF(WIN32)
