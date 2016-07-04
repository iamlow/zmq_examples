#include <iostream>
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
s_sendmore (zmq::socket_t & socket, const std::string & string)
{

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t requester(context, ZMQ_STREAM);
    requester.connect("tcp://localhost:5558");

    int rtimeo = 5 * 1000; /* sec */
    requester.setsockopt(ZMQ_RCVTIMEO, &rtimeo, sizeof rtimeo);

    size_t id_size = 256;
    char identity[id_size] = {};
    requester.getsockopt(ZMQ_IDENTITY, identity, &id_size);
    std::string id(identity, id_size);

    std::cout << __LINE__ << " ID: " << id << " " << id_size << std::endl;

    for( int request = 0 ; request < 10 ; request++) {
        s_sendmore(requester, id);
        // s_send(requester, "Hello");
        s_send(requester, argv[1]);
        std::string string = s_recv (requester);
        std::string string2 = s_recv (requester);

        std::cout << "Received reply " << request
                  << " [" << string << "]"
                  << " [" << string2 << "]" << std::endl;
    }

    return 0;
}
