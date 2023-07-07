#include <iostream>
#include <fstream>

#ifndef LOGGER
#define LOGGER

class Logger{
private:
  bool to_screen=true;
  bool to_file=false;
  bool debug=true;
  std::ofstream log_file;
public:
  Logger(){}

  Logger(std::string file){
    to_file=true;
    set_log_file(file);
  }

  ~Logger(){
    if(log_file.is_open()){
      log_file.close();
    }
  }

  void log_to_screen(bool screen_option){
    to_screen=screen_option;
  }

  void log_to_file(bool file_option){
    to_file=file_option;
    if(file_option==true){
      if(!log_file.is_open()){
        to_file=false;
        throw "No file open";
      }
    }
  }

  void set_log_file(std::string file){
    if(log_file.is_open()){
      log_file.close();
    }
    log_file.open(file);
    if(log_file.is_open()){
      to_file=true;
    } else {
      throw "Could not open file";
    }
  }

  void log(std::string message){
    if(to_screen){
      std::cout << "LOG: " << message << std::endl;
    }
    if(to_file){
      if(log_file.is_open()){
        if(debug){
          log_file << "LOG: " << message << "\n";
        }
      } else {
        throw "No file opened";
      }
    }
  }

  void warning(std::string message){
    if(to_screen){
      std::cout << "WARNING: " << message << std::endl;
    }
    if(to_file){
      if(log_file.is_open()){
        log_file << "WARNING: " << message << "\n";
      } else {
        throw "No file opened";
      }
    }
  }

  void error(std::string message){
    if(to_screen){
      std::cout << "ERROR: " << message << std::endl;
    }
    if(to_file){
      if(log_file.is_open()){
        log_file << "ERROR: " << message << "\n";
      } else {
        throw "No file opened";
      }
    }
  }
};

extern Logger *logger;

#endif
