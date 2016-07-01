## Building ZeroMQ v4.1.5

### Windows

Prerequisites:

* Visual Studio 2015 Update 3

To Build:

* 아래 경로의 솔루션 파일 열기
  * zeromq-4.1.5\builds\msvc\vs2013\libzmq.sln

* Build History
  * 프로젝트-속성-Local Dependencies-libsodium을 Not linked로 변경
  * 프로젝트-속성-ZMQ Options-Sodium-Enable Sodium을 Yes에서 No로 변경
  * Sodium은 암복호화 관련된 옵션인 것으로 보이는데 사용하지 않도록 변경, 이 옵션을 사용하려면 사전에 libsodium 설치필요

* 빌드 후 아래 경로에 빌드 옵션 별로 라이브러리 생성됨
  * zeromq-4.1.5\bin\
