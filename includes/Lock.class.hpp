#ifndef LOCK_CLASS_HPP
# define LOCK_CLASS_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <filesystem>

class Lock {
public:

    Lock(void);
    Lock(std::string lockPath);
    Lock(Lock const & src);
    ~Lock(void);

    Lock & operator=(Lock const & rhs);

    std::string const & getLockPath(void) const;

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
};

std::ostream & operator<<(std::ostream & o, Lock const & i);

#endif