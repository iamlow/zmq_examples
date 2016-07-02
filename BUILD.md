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

To Build with Visual Studio 2015:

* 아래 경로의 솔루션 파일 열기
  * zeromq-4.1.5\builds\msvc\vs2013\libzmq.sln

* Build History
  * 프로젝트-속성-Local Dependencies-libsodium을 Not linked로 변경
  * 프로젝트-속성-ZMQ Options-Sodium-Enable Sodium을 Yes에서 No로 변경
  * Sodium은 암복호화 관련된 옵션인 것으로 보이는데 사용하지 않도록 변경, 이 옵션을 사용하려면 사전에 libsodium 설치필요

* 빌드 후 아래 경로에 빌드 옵션 별로 라이브러리(libzmq.lib & libzmq.dll) 생성됨
  * zeromq-4.1.5\bin\

To Build with CMake:

*  빌드 설정이 완벽하지 않아서 빌드 시 오류가 발생하여 CMakeLists.txt 파일 수정 및 옵션을 추가하여 빌드해야함

1. zeromq-4.1.5\CMakeLists.txt 파일의 473 라인 주석처리
   `# set(rc-sources version.rc)`
2. `mkdir build`
3. `cd build`
4. `cmake -DZMQ_BUILD_TESTS=OFF ..`
    or
   `cmake -G "Visual Studio 14 2015 Win64" -DZMQ_BUILD_TESTS=OFF ..`
5. `cmake --build . --config Release`
    or
   `cmake --build . --config Debug`
6. 빌드된 파일 위치
  * dll: zeromq-4.1.5\build\bin\Debug(or Release)
  * lib: zeromq-4.1.5\build\lib\Debug(or Release)

## Building CZMQ v3.0.2

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build with CMake:

1. `git clone git://github.com/zeromq/czmq.git`
2. `git checkout v3.0.2`
3. `cd czmq`
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
