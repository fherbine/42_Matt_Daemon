#ifndef AREPORTER_ABSTRACT_HPP
# define AREPORTER_ABSTRACT_HPP

# define REPORT_LEVEL_DBG 0
# define REPORT_LEVEL_INF 1
# define REPORT_LEVEL_WRN 2
# define REPORT_LEVEL_ERR 3

# include <cstdint>
# include <iostream>
# include <fstream>
# include <string>

typedef uint8_t log_level_t;


class AReporter {
public:

    AReporter(void);
    AReporter(std::ostream & outputStream);
    AReporter(log_level_t logLevel);
    AReporter(std::ostream & outputStream, log_level_t logLevel);
    AReporter(std::string logfile);
    AReporter(std::string logfile, log_level_t logLevel);
    AReporter(AReporter const & src);

    virtual ~AReporter(void);

    virtual AReporter & operator=(AReporter const & rhs);

    virtual void setLogLevel(log_level_t logLevel);
    virtual void setOutputStream(std::ostream *outputStream);
    virtual std::ostream *getOutputStream(void) const;
    virtual log_level_t getLogLevel(void) const;

    virtual void debug(std::string const & message) const;
    virtual void info(std::string const & message) const;
    virtual void log(std::string const & message) const;
    virtual void warning(std::string const & message) const;
    virtual void error(std::string const & message) const;

protected:

    log_level_t _logLevel;
    std::ostream *_outputStream;
    
    virtual void _log(std::string const & message, std::string const & levelToken) const;

};

std::ostream & operator<<(std::ostream & o, AReporter const & i);

#endif