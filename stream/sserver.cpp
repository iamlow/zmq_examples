#include <iostream>
#include <thread>
#include <unistd.h>

#include "zmq.hpp"

//  Receive 0MQ string from socket and convert into string
static std::string s_recv (zmq::socket_t & socket)
{
    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

//  Convert string to 0MQ string and send to socket
static bool s_send (zmq::socket_t & socket, const std::string & string)
{
    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message);
    return (rc);
}

//  Sends string as 0MQ string, as multipart non-terminal
static bool
s_sendmore (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}

static void run(zmq::socket_t &responder, std::string id)
{
    // Do some 'work'
    // sleep(1);
    usleep(1000 * 100);

    std::cout << __LINE__ << std::endl;
    //  Send reply back to client
    s_sendmore (responder, id);
    s_send (responder, "World");
    std::cout << __LINE__ << std::endl;
}

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

	zmq::socket_t responder(context, ZMQ_STREAM);
    responder.bind("tcp://*:5559");

    /* Data structure to hold the ZMQ_STREAM ID */
    uint8_t id [256];
    size_t id_size = 256;

	while (1) {
        /*  Get HTTP request; ID frame and then request */
        std::string id = s_recv(responder);

        std::cout << __LINE__ << " ID: " << id << std::endl;

		//  Wait for next request from client
		std::string string = s_recv(responder);

		std::cout << "Received request: " << string << std::endl;
#if 0
		// Do some 'work'
        // sleep (1);
        usleep(100 * 1000);
        //  Send reply back to client
        s_sendmore (responder, id);
		s_send (responder, "World");
#else
        std::thread t(std::bind(&run, std::ref(responder), id));
        t.detach();
#endif
	}
}
