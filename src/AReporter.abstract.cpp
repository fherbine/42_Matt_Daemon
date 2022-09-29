#include "../includes/AReporter.abstract.hpp"

AReporter::AReporter(void) : _logLevel(REPORT_LEVEL_INF), _outputStream(&std::cout) {
    return ;
}

AReporter::AReporter(std::ostream & outputStream) : _logLevel(REPORT_LEVEL_INF), _outputStream(&outputStream) {
    return ;
}

AReporter::AReporter(log_level_t logLevel) : _logLevel(logLevel), _outputStream(&std::cout) {
    return ;
}

AReporter::AReporter(std::ostream & outputStream, log_level_t logLevel) : _logLevel(logLevel), _outputStream(&outputStream) {
    return ;
}

AReporter::AReporter(std::string logfile, log_level_t logLevel) : _logLevel(logLevel) {

    if (!Utility::OS::amIRoot()) {
        std::cerr << "Must be root !" << std::endl;
        exit(-1);
    }

    if (!std::filesystem::exists(std::filesystem::path(logfile).parent_path()))
        Utility::OS::Path::create_folder_tree(std::filesystem::path(logfile).parent_path());
        
    std::ofstream *ofs = new std::ofstream();
    ofs->open(logfile, std::ios_base::app);

    this->setOutputStream(ofs);
    return ;
}

AReporter::AReporter(std::string logfile) : AReporter(logfile, REPORT_LEVEL_INF) {}

AReporter::AReporter(AReporter const & src) : _outputStream(src.getOutputStream()) {
    *this = src;
    return ;
}

AReporter::~AReporter(void) {
    try {
        std::ofstream & ofs = dynamic_cast<std::ofstream &>(*(this->getOutputStream()));

        if (ofs.is_open()) {
            ofs.close();
            delete this->getOutputStream();
            this->setOutputStream(&std::cout);
        }
        
    } catch (std::bad_cast & _) {
        return ;
    }
    return ;
}

AReporter & AReporter::operator=(AReporter const & rhs) {
    if (this == &rhs)
        return *this;
    
    this->setLogLevel(rhs.getLogLevel());
    this->setOutputStream(rhs.getOutputStream());

    return *this;
}

void AReporter::setLogLevel(log_level_t logLevel) {
    this->_logLevel = logLevel;
}

void AReporter::setOutputStream(std::ostream *outputStream) {
    this->_outputStream = outputStream;
}

std::ostream *AReporter::getOutputStream(void) const {
    return this->_outputStream;
}

log_level_t AReporter::getLogLevel(void) const {
    return this->_logLevel;
}

void AReporter::debug(std::string const & message) const {
    if (this->getLogLevel() > REPORT_LEVEL_DBG)
        return ;
    
    this->_log(message, "DEBUG");
}

void AReporter::info(std::string const & message) const {
    if (this->getLogLevel() > REPORT_LEVEL_INF)
        return ;
    
    this->_log(message, "INFO");
}

void AReporter::log(std::string const & message) const {
    if (this->getLogLevel() > REPORT_LEVEL_INF)
        return ;
    
    this->_log(message, "LOG");
}

void AReporter::warning(std::string const & message) const {
    if (this->getLogLevel() > REPORT_LEVEL_WRN)
        return ;
    
    this->_log(message, "WARNING");
}

void AReporter::error(std::string const & message) const {
    this->_log(message, "ERROR");
}

void AReporter::_log(std::string const & message, std::string const & levelToken) const {
    *this->getOutputStream() << "[" + levelToken + "] " << message << std::endl; 
}

std::ostream & operator<<(std::ostream & o, AReporter const & i) {
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

    o << "This is AReporter logger in `" << logLevelToken << "` level.";
    return o;
}
