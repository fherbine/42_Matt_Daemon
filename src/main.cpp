#include "../includes/Tintin_reporter.class.hpp"
#include "../includes/Lock.class.hpp"
#include "../includes/Server.class.hpp"
#include "../includes/utility.hpp"

int main(void) {
  if (!Utility::OS::amIRoot()) {
    std::cerr << "Must be root !" << std::endl;
    return -1;
  }

  AReporter *logger = new Tintin_reporter("/var/log/matt_daemon/matt_daemon.log");

  logger->info("Started.");

  Lock lock = Lock("/var/lock/matt_daemon.lock");

  lock.acquire();

  logger->info("Creating server.");
  Server server = Server(*logger);
  logger->info("Server created.");

  logger->info("Entering Daemon mode.");
  Utility::OS::start_daemon();
  logger->info("started PID:" + std::to_string(getpid()));

  server.run();

  lock.release();

  logger->info("Quitting.");

  delete logger;

  return 0;
}