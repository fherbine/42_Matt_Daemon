#ifndef TINTIN_REPORTER_CLASS_HPP
# define TINTIN_REPORTER_CLASS_HPP

# include <iomanip>      // std::put_time
# include <ctime>        // std::time_t, struct std::tm, std::localtime
# include <chrono>       // std::chrono::system_clock
# include "./AReporter.abstract.hpp"

class Tintin_reporter : public AReporter {
public:

    Tintin_reporter(void);
    Tintin_reporter(std::ostream & outputStream);
    Tintin_reporter(log_level_t logLevel);
    Tintin_reporter(std::ostream & outputStream, log_level_t logLevel);
    Tintin_reporter(std::string logfile);
    Tintin_reporter(std::string logfile, log_level_t logLevel);
    Tintin_reporter(Tintin_reporter const & src);
    ~Tintin_reporter(void);

    Tintin_reporter & operator=(Tintin_reporter const & rhs);

private:

    void _log(std::string const & message, std::string const & levelToken) const;

};

std::ostream & operator<<(std::ostream & o, Tintin_reporter const & i);


#endif