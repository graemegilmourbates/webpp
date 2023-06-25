#ifndef HTTP_HELPERS_HPP
#define HTTP_HELPERS_HPP

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace WEBPP{
  std::unordered_map<std::string, std::string> parse_http_request(
    char *http_request
  );

  SSL_CTX *create_sll_context();

  void configure_ssl_context(SSL_CTX *ctx);

  int SSL_read_all(SSL *ssl, char *buffer, int num);

  void shut_down_ssl(SSL *ssl);
}

#endif // HTTP HELPERS
