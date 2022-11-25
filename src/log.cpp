//
// Created by jcc on 22-11-15.
//
# include "log.h"

using namespace mp;
void log::output(string text, log_level act_level){
    string prefix;
    if(act_level == debug) prefix = "\033[93m[DEBUG]   ";
    else if(act_level == info) prefix = "\033[92m[INFO]    ";
    else if(act_level == warning) prefix = "\033[95m[WARNING] ";
    else if(act_level == error) prefix = "\033[91m[ERROR]   ";
    else prefix = "";
    prefix += __FILE__;
    prefix += " ";
    string output_content = prefix + get_curTime() + " : " + text + "\n";
    cout << output_content;
}


void log::DEBUG(string text){
    this->output(text, debug);
}

void log::INFO(string text){
    this->output(text, info);
}

void log::WARNING(string text){
    this->output(text, warning);
}

void log::ERROR(string text){
    this->output(text, error);
}



log::log(log::log_target target, log::log_level level,string path) {
    this->_target = target;
    this->_path = std::move(path);
    this->_log_level = level;
    string tmp = "";  // 双引号下的常量不能直接相加，所以用一个string类型做转换
    string welcome_dialog = tmp + "[Welcome] " + __FILE__ + " " + get_curTime() + " : " + "=== Start logging ===\n";
    if (target != terminal){
        this->_outfile.open(path, ios::out | ios::app);   // 打开输出文件
        this->_outfile << welcome_dialog;
    }
    if (target != file){
        // 如果日志对象不是仅文件
        cout << welcome_dialog;
    }
}

log::log() {
    this->_target = terminal;
    this->_log_level = debug;
    cout << "\033[92m[WELCOME] " << __FILE__ << " " << get_curTime() << " : " << "=== Start logging ===" << endl;
}

std::string log::get_curTime() {
    char tmp[64];
    time_t ptime;
    time(&ptime);
    strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return tmp;
}


