#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <algorithm>
# include <string>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>



namespace Utility {
    
    namespace String {

        inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
            s.erase(s.find_last_not_of(t) + 1);
            return s;
        }

        inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
            s.erase(0, s.find_first_not_of(t));
            return s;
        }

        inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") {
            return ltrim(rtrim(s, t), t);
        }

        inline std::string & to_lower(std::string & s) {
            std::for_each(s.begin(), s.end(), [](char & c) {c = ::tolower(c);});
            return s;
        }

        inline std::string & to_upper(std::string & s) {
            std::for_each(s.begin(), s.end(), [](char & c) {c = ::toupper(c);});
            return s;
        }
    };

    namespace OS {
        inline bool amIRoot(void) {
            return (getuid() == 0) ? true : false;
        }
        
        pid_t start_daemon(void);

        class OSError : std::exception {
            virtual const char *what() const throw() {
                return ("OS Error");
            }
        };
    }

};

#endif