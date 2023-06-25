#include "HttpHelpers.hpp"

std::unordered_map<std::string, std::string> WEBPP::parse_http_request(
  char *http_request
){
    std::string line, request_type, url, proto, tmp;
    std::istringstream request(http_request);
    //Our map
    std::unordered_map<std::string, std::string> parsed_request;
    // Get first line (aka request type)
    std::getline(request, line);
    request_type = line.substr(0, line.find(" "));
    tmp = line.substr(line.find(" ")+1, line.length()-1);
    url = tmp.substr(0, tmp.find(" "));
    proto = tmp.substr(tmp.find(" ")+1, tmp.length()-1);
    parsed_request.insert({"type", request_type});
    parsed_request.insert({"route", url});
    parsed_request.insert({"proto", proto});
    while(std::getline(request, line)){
        if(line.length() > 1){
            std::string first = line.substr(0, line.find(" "));
            std::string second = line.substr(line.find(" ")+1, line.length()-1);
            parsed_request.insert({{first, second}});
        }
    }
    return parsed_request;
}

SSL_CTX *WEBPP::create_sll_context(){
  SSL_load_error_strings();
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  const SSL_METHOD *method;
  SSL_CTX *ctx;
  method = TLS_server_method();
  ctx = SSL_CTX_new(method);
  if(!ctx) {
    perror("Unable to create SSL Context");
    exit(EXIT_FAILURE);
  }
  SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE);
  return ctx;
}

void WEBPP::configure_ssl_context(SSL_CTX *ctx){
  /* Set the key and cert */
  if (SSL_CTX_use_certificate_file(ctx, "/usr/local/ssl/certs/cert.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  if (SSL_CTX_use_PrivateKey_file(ctx, "/usr/local/ssl/certs/key.pem", SSL_FILETYPE_PEM) <= 0 ) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }
}

int WEBPP::SSL_read_all(SSL *ssl, char *buffer, int num){
  char* ptr = reinterpret_cast<char*>(buffer);
  int read_bytes = 0;
  while (read_bytes < num)
  {
       int r = SSL_read(ssl, ptr + read_bytes, num - read_bytes);
       if (r <= 0)
           return r;
       read_bytes += r;
  }
  return read_bytes;
}

void WEBPP::shut_down_ssl(SSL *ssl){
  SSL_shutdown(ssl);
  SSL_free(ssl);
}
