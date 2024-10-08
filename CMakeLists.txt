cmake_minimum_required(VERSION 3.22)
project(Server4Poker)


if(WIN32)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
ENDIF()

#get_target_property(your_target_FILES your_target SOURCES)
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${your_target_FILES })

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS 0)

set(LIBUV_VERSION 1.47.0)
function(fetch_libuv)

    include(FetchContent)

    FetchContent_Declare(
        libuv
        GIT_REPOSITORY https://github.com/libuv/libuv.git
        GIT_TAG "v${LIBUV_VERSION}"
        GIT_SHALLOW 1
    )

    FetchContent_GetProperties(libuv)

    if(NOT libuv_POPULATED)
        FetchContent_Populate(libuv)
        message(STATUS "libuv_SOURCE_DIR:  " ${libuv_SOURCE_DIR})
        add_subdirectory(${libuv_SOURCE_DIR} ${libuv_BINARY_DIR} EXCLUDE_FROM_ALL)
        message(STATUS "after add_subdirectory libuv_SOURCE_DIR:  " ${libuv_SOURCE_DIR})
    endif()
    add_library(uv::uv-static ALIAS uv_a)

    set_target_properties(uv_a PROPERTIES POSITION_INDEPENDENT_CODE 1)
    if(WIN32)
        set_property(TARGET uv_a PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif(WIN32)

    #install(DIRECTORY ${libuv_SOURCE_DIR}/include/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/3rd/uvw-3.3.0_libuv_v1.47/uv/include)
endfunction()
fetch_libuv()

FetchContent_Declare(
    libfmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "10.2.1"
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(libfmt)

#
#set(protobuf_BUILD_TESTS 0)
#FetchContent_Declare(
#    protobuf
#    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
#    GIT_TAG "v3.26.0"
#    GIT_SHALLOW 1
#)
#FetchContent_MakeAvailable(protobuf)

IF(WIN32)
    set(absl_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/win64/debug/lib/cmake/absl)
    set(utf8_range_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/win64/debug/lib/cmake/utf8_range)
    SET(protobuf_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/win64/debug/cmake)
    find_package(protobuf PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/win64/debug/cmake
        NO_DEFAULT_PATH REQUIRED
        )
ELSE()
    set(absl_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/linux/lib/cmake/absl)
    set(utf8_range_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/linux/lib/cmake/utf8_range)
    SET(protobuf_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/linux/lib/cmake/protobuf)
    find_package(protobuf PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf3/linux/lib/cmake
        NO_DEFAULT_PATH REQUIRED
        )

MESSAGE(STATUS "INC:" ${protobuf_INCLUDE_DIR})
ENDIF()

IF(WIN32)
SET(MYSQL_BIN "C:/Program Files/MySQL/MySQL Server 8.0")
include_directories(${MYSQL_BIN}/include)
link_directories(${MYSQL_BIN}/lib)
ENDIF()



#FetchContent_Declare(
#    cjson
#    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
#    GIT_TAG "v1.7.18"
#    GIT_SHALLOW 1
#)
#FetchContent_MakeAvailable(cjson)
INCLUDE_DIRECTORIES(./3rd)
include_directories(./3rd/uvw-3.3.0_libuv_v1.47/src)
IF(WIN32)
include_directories(./3rd/protobuf3/win64/debug/include)
ELSE()
include_directories(./3rd/protobuf3/linux/include)
ENDIF()
include_directories(${libuv_SOURCE_DIR}/include/)
include_directories(${cjson_SOURCE_DIR})
INCLUDE_DIRECTORIES(./3rd/cJSON)
INCLUDE_DIRECTORIES(./3rd/OptionParser)
INCLUDE_DIRECTORIES(./3rd/spdlog-1.14.1/include)
include_directories(./)


FILE(GLOB PROTO_SRC gen_proto/*.cc gen_proto/*.h protos/*.proto)

FILE(GLOB SESSION_SRC Session/*.h Session/*.hpp Session/*.cpp)

FILE(GLOB DBPOOL_SRC dbpool/*.h dbpool/*.hpp)

set(BS_SRC 
    WrappedMessage.hpp
    #WrappedMessage.cpp
    MessagePool.h
    #MessagePool.cpp
    Msg.def.h
    Msg.def.cpp
    ServerBase.h
    ServerBase.cpp
    Thread.cpp
    Thread.hpp
    TimerListener.hpp
    TimerListener.cpp
    AsyncUvw.hpp
    AsyncUvw.cpp
    demo.toml
    TomlHelper.h
    snowflake.hpp
    nats_client/natsclient.hpp
    nats_client/natsclient.cpp
    CommonDef.h
    CommonDef.cpp
    3rd/cJSON/cJSON.h
    3rd/cJSON/cJSON.c
    3rd/OptionParser/OptionParser.h
    3rd/OptionParser/OptionParser.cpp
    3rd/miniz/miniz.c
    3rd/miniz/miniz.h
    ${PROTO_SRC}
    ${SESSION_SRC}
    ${DBPOOL_SRC}
)

source_group_by_dir(BS_SRC)

add_library(BaseServer STATIC ${BS_SRC})

if(WIN32)
set_property(TARGET BaseServer PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF(WIN32)

add_subdirectory(demos)
#add_subdirectory(tests)
