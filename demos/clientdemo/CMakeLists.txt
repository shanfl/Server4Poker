project(client_demo)
include_directories(../../)
set(src main.cpp)

add_executable(client_demo ${src})

target_link_libraries(client_demo BaseServer uv::uv-static protobuf::libprotobuf-lite mysqlclient)
if(WIN32)
set_property(TARGET client_demo PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF(WIN32)
