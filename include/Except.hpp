#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <iostream>
#include <string.h>

// Exception for failed log file open
class FailedLogFileOpen : public std::exception{
public:
  char* what(){
    return strdup("Failed to Open Log File...\n");
  }
};

// Excpetion for a socket system call returning a negative integer value.
class SocketSystemCallException : public std::exception{
private:
  char* message;
public:
  SocketSystemCallException(char * msg) : message(msg) {}
  const char* what() {
    std::string tmp("Failed to Create Socket: ");
    tmp += message;
    const char* out = tmp.c_str();
    return (out);
  }
};

// Exception for fork system call failure
class ForkSystemCallException : public std::exception{
public:
  char* what(){
    return strdup("server fork error...");
  }
};

#endif // EXCEPT_HPP
