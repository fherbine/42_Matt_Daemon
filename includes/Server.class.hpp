#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

# include <sys/socket.h> // For socket functions
# include <netinet/in.h> // For sockaddr_in
# include <cstdint> // For uint16_t
# include <iostream> // For cout
# include <unistd.h> // For read
# include <string.h> // For strerror

# include "./utility.hpp"
# include "./AReporter.abstract.hpp"

# define SERVER_DEFAULT_PORT 4242
# define SERVER_MAX_CLIENT 3

typedef uint16_t port_t;

class Server {
public:

    Server(AReporter & logger);
    Server(AReporter & logger, port_t portNo);
    Server(Server const & src);
    ~Server(void);

    Server & operator=(Server const & rhs);

    port_t getPortNo(void) const;
    AReporter & getLogger(void) const;

    void run(void);

    class MaxClientReached : std::exception {
    public:
        virtual const char *what() const throw() {
            return ("Too many clients.");
        }
    };

private:

    AReporter & _logger;
    port_t  _portNo;

    Server(void);

};

std::ostream & operator<<(std::ostream & o, Server const & i);

#endif