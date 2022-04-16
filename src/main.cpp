#include "../includes/Tintin_reporter.class.hpp"
#include "../includes/Lock.class.hpp"
#include "../includes/Server.class.hpp"
#include "../includes/utility.hpp"

int main(void) {
    Utility::OS::start_daemon();
    AReporter *logger = new Tintin_reporter("/tmp/log.txt");
    logger->info("started");
    logger->debug("A random debug message");
    logger->warning("Be careful !");
    logger->error("This time there will be no excuses...");
    
    std::cout << *logger << std::endl;


    Lock lock = Lock();
    Lock lock2 = Lock();
    lock.acquire();

    try {
        lock2.acquire();
    } catch(Lock::ResourceBusyError & e) {
        std::cerr << e.what() << std::endl;
    }

    lock.release();

    Server serv = Server(*logger);

    serv.run();

    delete logger;

    return 0;
}