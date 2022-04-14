#include "../includes/Tintin_reporter.class.hpp"

Tintin_reporter::Tintin_reporter(void) : AReporter() {}

Tintin_reporter::Tintin_reporter(std::ostream & outputStream) : AReporter(outputStream) {}
Tintin_reporter::Tintin_reporter(log_level_t logLevel) : AReporter(logLevel) {}
Tintin_reporter::Tintin_reporter(std::ostream & outputStream, log_level_t logLevel) : AReporter(outputStream, logLevel) {}
Tintin_reporter::Tintin_reporter(std::string logfile) : AReporter(logfile) {}
Tintin_reporter::Tintin_reporter(std::string logfile, log_level_t logLevel) : AReporter(logfile, logLevel) {}

Tintin_reporter::Tintin_reporter(Tintin_reporter const & src) : AReporter(src) {}

Tintin_reporter::~Tintin_reporter(void) {
    AReporter::~AReporter();
    return ;
}

Tintin_reporter & Tintin_reporter::operator=(Tintin_reporter const & rhs) {
    return dynamic_cast<Tintin_reporter &>(AReporter::operator=(rhs));
}

void Tintin_reporter::_log(std::string const & message, std::string const & levelToken) const {
    std::stringstream datetime;
    std::time_t tt = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());
    struct std::tm *ptm = std::localtime(&tt);
    datetime << std::put_time(ptm, "[%d/%m/%Y - %H:%M:%S]");

    *this->getOutputStream() << datetime.str() << " [" + levelToken + "] " << message << std::endl;
}

std::ostream & operator<<(std::ostream & o, Tintin_reporter const & i) {
    std::string logLevelToken = "UNKNOWN";

    switch (i.getLogLevel())
    {
    case REPORT_LEVEL_DBG:
        logLevelToken = "DEBUG";
        break;

    case REPORT_LEVEL_INF:
        logLevelToken = "INFO";
        break;

    case REPORT_LEVEL_WRN:
        logLevelToken = "WARNING";
        break;

    case REPORT_LEVEL_ERR:
        logLevelToken = "ERROR";
        break;
    
    default:
        break;
    }

    o << "This is Tintin_reporter logger in `" << logLevelToken << "` level.";
    return o;
}
