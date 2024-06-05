project(login)
include_directories(../../)
set(src user.h user.cpp user.toml)

add_executable(user ${src})

target_link_libraries(user BaseServer uv::uv-static protobuf::libprotobuf-lite)
if(WIN32)
set_property(TARGET user PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF(WIN32)
