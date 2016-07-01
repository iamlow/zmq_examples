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
s_sendmore (zmq::socket_t & socket, const std::string & string)
{

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}

static void run(zmq::socket_t &zpush, std::string id, std::string string, int msleep = 1000)
{
    usleep(msleep * 1000);
    std::cout << __LINE__ << std::endl;
    //  Send reply back to client
    s_sendmore(zpush, id);
    if ("Hello" == string) {
        s_send(zpush, "World");
    } else if ("Foo" == string) {
        s_send(zpush, "Bar");
    } else {
        s_send(zpush, "Unknown");
    }

    std::cout << __LINE__ << std::endl;
}

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t zpull(context, ZMQ_PULL);
    zpull.connect("tcp://localhost:5557");

    zmq::socket_t zpush(context, ZMQ_PUSH);
    zpush.connect("tcp://localhost:5556");

    while (1) {
        /*  Get HTTP request; ID frame and then request */
        std::string id = s_recv(zpull);
        std::cout << __LINE__ << " ID: " << id << std::endl;

        //  Wait for next request from client
        std::string string = s_recv(zpull);
        std::cout << "Received request: " << string << std::endl;

        if (2 == argc) {
            run(zpush, id, string, atoi(argv[1]));
        } else {
            run(zpush, id, string);
        }
    }

    return 0;
}
