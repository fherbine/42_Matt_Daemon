#ifndef LOCK_CLASS_HPP
# define LOCK_CLASS_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <filesystem>
# include <sys/file.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "./utility.hpp"

class Lock {
public:

    Lock(void);
    Lock(std::string lockPath);
    Lock(Lock const & src);
    ~Lock(void);

    Lock & operator=(Lock const & rhs);

    std::string const & getLockPath(void) const;
    bool isLocked(void) const;

    void acquire(void);
    void release(void);

    class ResourceBusyError: public std::exception
    {
    public:
        virtual const char *what() const throw() {
            return ("Cannot acquire lock.");
        }
    };

private:

    std::string const _lockPath;
    bool _locked;
    int _fd;
};

std::ostream & operator<<(std::ostream & o, Lock const & i);

#endif