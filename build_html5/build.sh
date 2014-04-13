export EMSCRIPTEN_ROOT=/Users/jpd002/Projects/emscripten
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN_ROOT}/cmake/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
