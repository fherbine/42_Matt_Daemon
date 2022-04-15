#include "../includes/Lock.class.hpp"

Lock::Lock(void) : Lock("/tmp/lock.lock") {}

Lock::Lock(std::string lockPath) : _lockPath(lockPath) {}

Lock::Lock(Lock const & src) {
    *this = src;
    return ;
}

Lock::~Lock(void) {
    return ;
}

Lock & Lock::operator=(Lock const & rhs) {
    if (this == &rhs)
        return *this;
    return *(new Lock(rhs));
}

void Lock::acquire(void) {
    if (std::filesystem::exists(this->_lockPath))
        throw Lock::ResourceBusyError();

    std::ofstream ofs;

    ofs.open(this->_lockPath);
    ofs.close();
}

void Lock::release(void) {
    std::filesystem::remove(this->_lockPath);
}