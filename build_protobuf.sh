git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git ./protobuf 
mkdir -p 3rd/protobuf3
cmake -S ./protobuf -B ./protobuf/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./3rd/protobuf3

cmake --build ./protobuf/build --target install --config Release