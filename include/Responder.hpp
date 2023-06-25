#ifndef RESPONDER_HPP
#define RESPONDER_HPP

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <unordered_map>
#include <sys/time.h>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace WEBPP{
  class Responder{
  private:
    char *response_header;
    int client;

    void set_response_header(char *t_header);
    void send_response(const char *t_response);
  public:
    Responder(int t_client);
    void send_html(const char *t_html);
    void send_json(const char *t_json);
    void send_file(std::string t_file_path, std::string t_file_type);
    void send_image(std::string t_image_path);
    void send_video(std::string t_image_path);
    void send_audio(std::string t_image_path);
  };
}

#endif // RESPONDER_HPP
