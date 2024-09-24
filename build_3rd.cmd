    mkdir  .\tmp\

echo    git clone -b v5.7.0-stable --recursive https://github.com/wolfSSL/wolfssl.git   .\tmp\wolfssl
    //git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git .\tmp\protobuf

echo     mkdir .\3rd\wolfssl\win64
 echo    cmake -S .\tmp\wolfssl  -B .\tmp\wolfssl\build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\3rd\wolfssl\win64 -DBUILD_SHARED_LIBS=OFF
 echo    cmake --build .\tmp\wolfssl\build --target install --config Release


    git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git .\tmp\protobuf
    mkdir .\3rd\protobuf3\win64
    cmake -S .\tmp\protobuf -B .\tmp\protobuf\build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\3rd\protobuf3\win64 -DBUILD_SHARED_LIBS=OFF -Dprotobuf_BUILD_TESTS=OFF
    cmake --build .\tmp\protobuf\build --target install --config Release
