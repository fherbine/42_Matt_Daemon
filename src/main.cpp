#include "../includes/Tintin_reporter.class.hpp"

#include <fstream>

int main(void) {
    AReporter *logger = new Tintin_reporter("toto.txt");
    logger->info("started");
    logger->debug("A random debug message");
    logger->warning("Be careful !");
    logger->error("This time there will be no excuses...");
    
    std::cout << *logger << std::endl;

    delete logger;

    return 0;
}