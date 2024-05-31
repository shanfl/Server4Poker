project(gateserver)
include_directories(../../)
set(src gateserver.h gateserver.cpp)

add_executable(gateserver ${src})

target_link_libraries(gateserver BaseServer uv::uv-static protobuf::libprotobuf-lite)
if(WIN32)
set_property(TARGET gateserver PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF(WIN32)