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

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    // backend
    zmq::socket_t be_push(context, ZMQ_PUSH);
	be_push.bind("tcp://*:5557");

    zmq::socket_t be_pull(context, ZMQ_PULL);
	be_pull.bind("tcp://*:5556");

    // frontend
	zmq::socket_t fe_stream(context, ZMQ_STREAM);
    fe_stream.bind("tcp://*:5558");

    zmq::pollitem_t items [] = {
        { (void *)be_pull, 0, ZMQ_POLLIN, 0 },
        { (void *)fe_stream, 0, ZMQ_POLLIN, 0 }
    };

	while (1) {
        zmq::poll(&items [0], 2, -1);

        if (items[0].revents & ZMQ_POLLIN) {   // be -> fe
            /*  Get HTTP request; ID frame and then request */
            std::string id = s_recv(be_pull);
            std::cout << __LINE__ << " ID: " << id << std::endl;

    		//  Wait for next request from client
    		std::string string = s_recv(be_pull);
    		std::cout << "BE->FE Received request: " << string << std::endl;

            s_sendmore(fe_stream, id);
            s_send(fe_stream, string);
        }

        if (items[1].revents & ZMQ_POLLIN) {   // fe -> be
            /*  Get HTTP request; ID frame and then request */
            std::string id = s_recv(fe_stream);
            std::cout << __LINE__ << " ID: " << id << std::endl;

    		//  Wait for next request from client
    		std::string string = s_recv(fe_stream);
    		std::cout << "FE->BE Received request: " << string << std::endl;

            s_sendmore(be_push, id);
            s_send(be_push, string);
        }
	}
}
