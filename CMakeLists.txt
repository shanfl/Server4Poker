project(BaseServer)

FILE(GLOB PROTO_SRC gen_proto/*.cc gen_proto/*.h)

set(BS_SRC 
    MessagePool.h
    Msg.def.h
    ServerBase.h
    ServerBase.cpp
    Thread.cpp
    Thread.hpp
    ${PROTO_SRC}
)

add_library(BaseServer STATIC ${BS_SRC})