#include "../includes/Lock.class.hpp"

Lock::Lock(void) : Lock("/tmp/lock.lock") {}

Lock::Lock(std::string lockPath) : _lockPath(lockPath), _locked(false) {}

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

std::string const & Lock::getLockPath(void) const {
    return this->_lockPath;
}

bool Lock::isLocked(void) const {
    return this->_locked;
}

void Lock::acquire(void) {
    if (std::filesystem::exists(this->_lockPath))
        throw Lock::ResourceBusyError();

    std::ofstream ofs;

    ofs.open(this->_lockPath);
    ofs.close();
    _locked = true;
}

void Lock::release(void) {
    std::filesystem::remove(this->_lockPath);
    _locked = false;
}

std::ostream & operator<<(std::ostream & o, Lock const & i) {
    o << "Lock instance with the fololowing lock file: " << i.getLockPath();
    return o;
}