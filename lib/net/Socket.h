#ifndef PROJ2_SOCKSTREAM_H
#define PROJ2_SOCKSTREAM_H


#include <string>

namespace net {
    class Socket {
    public:
        explicit Socket(int fd);

        ~Socket();

        std::string readLine();

        void send(const std::string &s);

    private:
        int _fd;
        std::string _internal_buf;
    };
}

#endif //PROJ2_SOCKSTREAM_H
