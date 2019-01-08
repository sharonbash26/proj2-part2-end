//
// Created by sharon_i4 on 08/01/2019.
//

#ifndef PROJ2_TIMEOUTEXCEPTION_H
#define PROJ2_TIMEOUTEXCEPTION_H

#include <exception>
#include <string>

namespace net {

    class TimeoutException : public std::exception {
    public:
        TimeoutException(const char *msg = "Timeout has occured") : message(msg) {}

        const char *what() const noexcept {
            return message.c_str();
        }

    private:
        std::string message;
    };
}

#endif //PROJ2_TIMEOUTEXCEPTION_H
