# ZEROMQ 관련 예제
## ZMQ_STREAM 응용

### 목적
* BSD Socket과 ZMQ(ZMQ_STREAM)와 연동 가능 여부 테스트

### 구성도
![ZMQ_STREAM PIPELINE](zmq_stream.png)

### 파일 설명
* sserver.cpp: ZMQ_STREAM SERVER
* sclient.cpp: ZMQ_STREAM CLIENT
* sproxy.cpp: ZMQ_STREAM PROXY
 * STREAM->PUSH->PULL->STREAM
* sworker.cpp: ZMQ_STREAM WORKER
* bclient.cpp: BSD SOCKET CLIENT
 * BSD Client Socket

### How To Build
* cmake 사용
* centos에서 빌드, 다른 OS 빌드 테스트 안함.
