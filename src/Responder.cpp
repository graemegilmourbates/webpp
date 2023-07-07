#include "Responder.hpp"

WEBPP::Responder::Responder(int t_client){
  client = t_client;
}

void WEBPP::Responder::set_response_header(char *t_header){
  response_header = t_header;
}

void WEBPP::Responder::send_response(const char *t_response){
  //Get total length of response
  char *outflow = new char[strlen(response_header) + strlen(t_response) + 2];
  outflow = strcpy(outflow, response_header);
  outflow = strcat(outflow, "\n");
  outflow = strcat(outflow, t_response);
  if(sizeof(outflow) > 1024){
    std::cout << "Size of response is large needs to be bufferd" << std::endl;
  }
  send(client, outflow, strlen(outflow), 0);
  close(client);
  delete[] outflow;
}

void WEBPP::Responder::send_file(
  std::string t_file_path, std::string t_file_type
){
  // Load in file
  std::ifstream file(t_file_path, std::ios::binary | std::ios::ate);
  // Check that file was obtained
  if(!file){
    perror("FILE DNE:");
    exit(EXIT_FAILURE);
  }
  // Move to end of file to get total size
  file.seekg (0, file.end);
  std::streamsize file_size = file.tellg();
  // Create reponse header
  std::stringstream responseStream;
  responseStream << "HTTP/1.1 200 OK\r\n";
  responseStream << "Content-Type: " << t_file_type << "\r\n";
  responseStream << "Content-Length: " << file_size << "\r\n\r\n";

  std::string response = responseStream.str();
  // Send response Header
  if (send(client, response.c_str(), response.length(), 0) == -1) {
    logger->error("Failed to send HTTP response...");
    exit(EXIT_FAILURE);
  }
  // Return to beginning of the file
  // Initialize chunks of 1024 bytes to send
  file.seekg (0, file.beg);
  char buffer[1024];
  std::streamsize bytes_read;
  while(file_size > 0){
    // read in a chunk
    bytes_read = file.read(buffer, sizeof(buffer)).gcount();
    if(bytes_read <= 0){
      logger->warning("Problem with file read");
      break;
    }
    if(send(client, buffer, bytes_read, 0) == -1){
      logger->error("Failed to send image data");
      exit(EXIT_FAILURE);
    }
    file_size -= bytes_read;
  }
  file.close();
  close(client);
}

void WEBPP::Responder::send_html(const char *t_html){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    send_response(t_html);
}

void WEBPP::Responder::send_json(const char *t_json){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n");
    send_response(t_json);
}

void WEBPP::Responder::send_image(std::string t_image_path){
    int index;
    std::string file_type, content_type;
    index = t_image_path.find_last_of(".");
    file_type = t_image_path.substr(index+1);
    if(file_type == "ico") content_type = "image/x-icon";
    else if (file_type == "jpeg" || file_type == "jpg") content_type = "image/jpeg";
    else if (file_type == "html") content_type = "text/html";
    send_file(t_image_path, content_type);
}
