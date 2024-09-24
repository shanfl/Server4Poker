mkdir .\tmp\debug\protobuf
mkdir .\tmp\release\protobuf
mkdir .\3rd\protobuf3\win64\debug
mkdir .\3rd\protobuf3\win64\release
git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git .\tmp\debug\protobuf
git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git .\tmp\release\protobuf

cmake -S .\tmp\protobuf -B .\tmp\release\protobuf\build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\3rd\protobuf3\win64\release -DBUILD_SHARED_LIBS=OFF -Dprotobuf_BUILD_TESTS=OFF
cmake --build .\tmp\release\protobuf\build --target install --config Release

cmake -S .\tmp\protobuf -B .\tmp\debug\protobuf\build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\3rd\protobuf3\win64\debug -DBUILD_SHARED_LIBS=OFF -Dprotobuf_BUILD_TESTS=OFF
cmake --build .\tmp\debug\protobuf\build --target install --config Debug