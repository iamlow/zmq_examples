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
2. Go to the project directory of the local source repository.
3. To perform an out-of-source build, run:
4. `mkdir build`
5. `cd build`
6. `cmake -DZMQ_BUILD_TESTS=OFF ..`
    or
   `cmake -G "Visual Studio 14 2015 Win64" -DZMQ_BUILD_TESTS=OFF ..`
7. `cmake --build . --config Release`
    or
   `cmake --build . --config Debug`
8. 빌드된 파일 위치
  * dll: zeromq-4.1.5\build\bin\Debug(or Release)
  * lib: zeromq-4.1.5\build\lib\Debug(or Release)

## Building CZMQ v3.0.2

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build:

* 아래 경로의 솔루션 파일 열기
  * czmq-3.0.2\builds\msvc\vs2013\czmq.sln

* Build History
  * 프로젝트-속성-Local Dependencies-libsodium을 Not linked로 변경
  * 프로젝트-속성-ZMQ Options-Sodium-Enable Sodium을 Yes에서 No로 변경
  * 빌드 시 libzmq.import.props 파일에서 오류 발생 시 아래 내용 삭제 후 빌드
  ``` xml
    <Target Name="Linkage-libzmq-dynamic" AfterTargets="AfterBuild" Condition="'$(Linkage-libzmq)' == 'dynamic'">
    <Copy Condition="$(Configuration.IndexOf('Debug')) != -1"
          SourceFiles="$(ProjectDir)..\..\..\..\..\libzmq\bin\$(PlatformName)\Debug\$(PlatformToolset)\dynamic\libzmq.dll"
          DestinationFiles="$(TargetDir)libzmq.dll"
          SkipUnchangedFiles="true" />
    <Copy Condition="$(Configuration.IndexOf('Debug')) != -1"
          SourceFiles="$(ProjectDir)..\..\..\..\..\libzmq\bin\$(PlatformName)\Debug\$(PlatformToolset)\dynamic\libzmq.pdb"
          DestinationFiles="$(TargetDir)libzmq.pdb"
          SkipUnchangedFiles="true" />
    <Copy Condition="$(Configuration.IndexOf('Release')) != -1"
          SourceFiles="$(ProjectDir)..\..\..\..\..\libzmq\bin\$(PlatformName)\Release\$(PlatformToolset)\dynamic\libzmq.dll"
          DestinationFiles="$(TargetDir)libzmq.dll"
          SkipUnchangedFiles="true" />
  </Target>
  ``` 
* 빌드 후 아래 경로에 빌드 옵션 별로 라이브러리(czmq.lib, czmq.dll) 생성됨
  * czmq-3.0.2\bin\
