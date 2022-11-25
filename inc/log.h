//
// Created by jcc on 22-11-15.
//

#ifndef SDR_LOG_H
#define SDR_LOG_H

#include "iostream"
#include "string"
#include <ctime>
#include <cstdlib>
#include "fstream"

using std::cout;
using std::string;
using std::endl;
using std::to_string;
using std::ios;

namespace mp {
    class log {
    public:
        enum log_level {
            debug, info, warning, error
        };
        enum log_target {
            terminal, file
        };

    private:
        log_target _target;
        log_level _log_level;
        string _path;
        std::ofstream _outfile;

        void output(std::string text, log_level act_level);

        std::string get_curTime();

    public:
        log();

        log(log_target target, log_level level, string path);

        void DEBUG(string text);

        void INFO(string text);

        void WARNING(string text);

        void ERROR(string text);

    };
}
#endif //SDR_LOG_H
