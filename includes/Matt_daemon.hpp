#ifndef MATT_DAEMON_HPP
# define MATT_DAEMON_HPP

# include <csignal>
# include "../includes/Tintin_reporter.class.hpp"
# include "../includes/Lock.class.hpp"
# include "../includes/Server.class.hpp"
# include "../includes/utility.hpp"

Tintin_reporter g_logger("/var/log/matt_daemon/matt_daemon.log");

#endif