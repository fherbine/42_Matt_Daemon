#include "../includes/Matt_daemon.hpp"

extern Tintin_reporter g_logger;

int main(void) {
  if (!Utility::OS::amIRoot()) {
    std::cerr << "Must be root !" << std::endl;
    return -1;
  }

  g_logger.info("Started.");

  for (int sgnum = 1; sgnum < NSIG; sgnum++)
    signal(sgnum, []([[ maybe_unused ]]int _){
      g_logger.info("Signal handler.");
    });

  Lock lock = Lock("/var/lock/matt_daemon.lock");

  lock.acquire();

  g_logger.info("Creating server.");
  Server server = Server(g_logger);
  g_logger.info("Server created.");

  g_logger.info("Entering Daemon mode.");
  Utility::OS::start_daemon();
  g_logger.info("started PID:" + std::to_string(getpid()));

  server.run();

  lock.release();

  g_logger.info("Quitting.");

  return 0;
}