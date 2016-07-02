## Building ZeroMQ

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build with CMake:

1. `git clone git://github.com/zeromq/libzmq.git`
2. `cd libzmq`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
    or
   `cmake -G "Visual Studio 14 2015 Win64" ..`
6. `cmake --build . --config Release`
    or
   `cmake --build . --config Debug`
7. 빌드된 파일 위치
  * dll: libzmq\build\bin\Debug(or Release)
  * lib: libzmq\build\lib\Debug(or Release)

## Building ZeroMQ v4.1.5

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build with CMake:

* 주의: zeromq.org에서 배포하는 버전은 빌드 설정이 완벽하지 않아서 빌드 시 오류가 발생

1. `git clone https://github.com/zeromq/zeromq4-1.git` 
2. `cd zeromq4-1`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
    or
   `cmake -G "Visual Studio 14 2015 Win64" ..`
6. `cmake --build . --config Release`
    or
   `cmake --build . --config Debug`
7. 빌드된 파일 위치
  * dll: zeromq4-1\build\bin\Debug(or Release)
  * lib: zeromq4-1\build\lib\Debug(or Release)

## Building CZMQ v3.0.2

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build with CMake:

1. `git clone git://github.com/zeromq/czmq.git`
2. `cd czmq`
3. `git checkout v3.0.2`
4. `mkdir build`
5. `cd build`
6. `cmake ../ -DCMAKE_CXX_FLAGS=-DZMQ_STATIC -DZEROMQ_INCLUDE_DIRS=libzmq\include -DZEROMQ_LIBRARIES=libzmq\build\lib\Debug\libzmq-static-v140-mt-sgd-4_2_0.lib`
    or
   `cmake ../ -DZEROMQ_INCLUDE_DIRS=libzmq\include -DZEROMQ_LIBRARIES=libzmq\build\lib\Debug\libzmq-v140-mt-gd-4_2_0.lib`
7. `cmake --build . --config Release`
    or
   `cmake --build . --config Debug`
8. 빌드된 파일 위치
  * dll: czmq\build\bin\Debug(or Release)
  * lib: czmq\build\lib\Debug(or Release)
