#include "../includes/Matt_daemon.hpp"

extern Tintin_reporter g_logger;
extern Lock g_lock;

void signal_handler([[ maybe_unused ]]int _) {
  g_logger.info("Signal handler.");
  g_logger.info("Quitting.");

  if (g_lock.isLocked())
    g_lock.release();

  exit(EXIT_SUCCESS);
}

int main(void) {
  if (!Utility::OS::amIRoot()) {
    std::cerr << "Must be root !" << std::endl;
    return -1;
  }

  for (int sgnum = 1; sgnum < NSIG; sgnum++)
    signal(sgnum, &signal_handler);
  
  try {
    g_lock.acquire();
    
    g_logger.info("Started.");

    g_logger.info("Creating server.");
    Server server = Server(g_logger);
    g_logger.info("Server created.");

    g_logger.info("Entering Daemon mode.");
    Utility::OS::start_daemon();
    g_logger.info("started PID:" + std::to_string(getpid()));

    server.run();

    g_lock.release();

    g_logger.info("Quitting.");
  } catch (Lock::ResourceBusyError & e) {
    g_logger.error(e.what());
    std::cerr << e.what() << std::endl;
  } catch (std::exception & e) {
    g_logger.error(e.what());
  }

  return 0;
}