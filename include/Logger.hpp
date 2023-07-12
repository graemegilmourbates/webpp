#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "Except.hpp"

#define LOG "#### LOG:: "
#define WRN "#### WARNING:: "
#define ERR "#### ERROR:: "

class Logger{
private:
  std::string log_path;
  std::ofstream log_file;
  bool to_file, to_console, is_debug;
public:
  // Constructor Sets default log file...
  Logger() : Logger("/.webpp.log") {}
  Logger(std::string t_log_file_path){
    const char* home_directory = std::getenv("HOME");
    log_path = std::string(home_directory) + t_log_file_path;
    to_file = true;
    to_console = true;
    is_debug = true;
    openLogFile();
  }

  // Copy constructor
  Logger(const Logger& other){
    this->log_path = other.log_path;
    this->to_file = other.to_file;
    this->to_console = other.to_console;
    this->is_debug = other.is_debug;
  }

  // Copy assignment operator
  Logger& operator=(const Logger& other){
    if(this != &other){
      this->log_path = other.log_path;
      this->to_file = other.to_file;
      this->to_console = other.to_console;
      this->is_debug = other.is_debug;
    }
    return *this;
  }

  // Move Constructor
  Logger(Logger&& other) noexcept{
    this->log_path = std::move(other.log_path);
    this->to_file = std::move(other.to_file);
    this->to_console = std::move(other.to_console);
    this->is_debug = std::move(other.is_debug);
  }

  // Move assignment
  Logger& operator=(Logger&& other) noexcept{
    if(this != &other){
      this->log_path = std::move(other.log_path);
      this->to_file = std::move(other.to_file);
      this->to_console = std::move(other.to_console);
      this->is_debug = std::move(other.is_debug);
    }
    return *this;
  }

  // Destruct
  ~Logger(){
    if(log_file.is_open()){
      closeLogFile();
    }
  }

  // Set debug state
  void debug(bool t_state){
    is_debug = t_state;
  }

  const std::string get_time(){
    std::time_t current_time = std::time(nullptr);
    std::string formatted_time = std::ctime(&current_time);
    formatted_time.pop_back(); // Remove newline char from ctime
    return formatted_time;
  }

  void openLogFile(){
    log_file.open(log_path, std::ios::app);
    try{
      if(!log_file.is_open()){
        throw FailedLogFileOpen();
      }
      log_file << "=== Log Started: " << get_time() << " ===" << std::endl;
    }
    // If log file fails to open... Print to console or exit;
    catch(FailedLogFileOpen flfo){
      if(to_console){
        std::cout << flfo.what();
      } else {
        // Will Terminate:
        // File cannot be accessed and console output is disabled
        exit(EXIT_FAILURE);
      }
    }
  }

  void closeLogFile(){
    if(log_file.is_open()){
      log_file << "=== Log Ended: " << get_time() << " ===" << std::endl;
      log_file.close();
    }
  }

  // Log status { error, warning, log } : { 0, 1, 2 }
  std::stringstream gen_message(const int log_status, const char* &message){
    std::string formatted_time = get_time();
    std::stringstream msg;
    if(log_status == 0){ msg << ERR; } // ERROR
    else if(log_status == 1){ msg << WRN; } // WARNING
    else { msg << LOG; } // LOG
    msg << formatted_time << ": " << message;
    return msg;
  }

  void log(const int log_status, const char* &message){
    std::stringstream msg = gen_message(log_status, message);

    if(to_console){
      std::cout << msg.str() << std::endl;
    }
    if(to_file && log_file.is_open()){
      log_file << msg.str() << std::endl;
    }
  }

  // Log: Log
  void operator()(const char* message){
    log(2, message);
  }
  void operator()(const std::string message){
    const char* msg = message.c_str();
    log(2, msg);
  }

  // Log: Log Warning
  void operator>>(const char* message){
    log(1, message);
  }
  void operator>>(const std::string message){
    const char* msg = message.c_str();
    log(1, msg);
  }

  // Log: Log Error
  void operator<<(const char* message){
    log(0, message);
  }
  void operator<<(const std::string message){
    const char* msg = message.c_str();
    log(0, msg);
  }


};

extern Logger logger;

#endif // LOGGER_HPP
