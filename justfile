
# Run with: just build

default:
    just build

build:
    mkdir -p build
    cd build && cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -DCMAKE_PREFIX_PATH=$CHECK_PREFIX
    cd build && ninja

test:
    just build
    cd build && ctest --output-on-failure
