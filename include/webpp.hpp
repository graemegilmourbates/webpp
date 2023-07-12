#include "Server.hpp"
#include "BaseSocket.hpp"
#include "BindingSocket.hpp"
#include "HttpHelpers.hpp"
#include "Router.hpp"
#include "Responder.hpp"
#include "Logger.hpp"
#include "Except.hpp"

using REQUEST = std::unordered_map<std::string, std::string>;
using RESPONDER = WEBPP::Responder;
using URL_PARAMETERS = std::unordered_map<std::string, std::string>;
