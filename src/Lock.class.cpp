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
    if ((this->_fd = open(this->getLockPath().c_str(), 0666)) == -1)
        throw Utility::OS::OSError();
    

    if (flock(this->_fd, LOCK_EX | LOCK_NB) == -1) {
        switch (errno)
        {
        case EWOULDBLOCK:
            throw Lock::ResourceBusyError();
            break;
        
        default:
            throw Utility::OS::OSError();
            break;
        }
    }
    
    _locked = true;
}

void Lock::release(void) {
    if (flock(this->_fd, LOCK_UN) == -1)
        throw Utility::OS::OSError();

    close(this->_fd);
    _locked = false;
}

std::ostream & operator<<(std::ostream & o, Lock const & i) {
    o << "Lock instance with the fololowing lock file: " << i.getLockPath();
    return o;
}