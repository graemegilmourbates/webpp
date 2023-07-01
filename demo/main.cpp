#include <iostream>
#include <unordered_map>
#include <WEBPP/webpp.hpp>
#include <WEBPP/Responder.hpp>
#include <stdlib.h>
#include <string>

using REQUEST = std::unordered_map<std::string, std::string>;
using RESPONDER = WEBPP::Responder;
using URL_PARAMETERS = std::unordered_map<std::string, std::string>;

void home_page(RESPONDER res, REQUEST req, URL_PARAMETERS params){
  std::cout << "Sending INDEX PAGE" << std::endl;
  res.send_file("index.html", "html");
}

void favicon(RESPONDER res, REQUEST req, URL_PARAMETERS params){
  std::cout << "Sending FAV" << std::endl;
  res.send_image("public/images/favicon.ico");
}

void user_form(RESPONDER res, REQUEST req, URL_PARAMETERS params){

  std::cout << "REQUEST METHOD: " << req["Method"] << std::endl;
  if(req["Method"] == "GET"){
    res.send_file("user_form.html", "html");
  } else if(req["Method"] == "POST"){
    std::string response;
    std::unordered_map user_form_data = WEBPP::get_form_data(req["Body"]);
    response = "<html><body>";
    response += "<h2>First Name: " + user_form_data["firstName"] + "</h2>";
    response += "<h2>Last Name: " + user_form_data["lastName"] + "</h2>";
    response += "<h2>Email: " + user_form_data["email"] + "</h2>";
    response += "</body></html>";
    std::cout << "First name: " << user_form_data["firstName"] << std::endl;
    std::cout << "Last name: " << user_form_data["lastName"] << std::endl;
    std::cout << "email: " << user_form_data["email"] << std::endl;
    res.send_html(response.c_str());
  }
}

void user_id(RESPONDER res, REQUEST req, URL_PARAMETERS params){
  std::cout << "SENDING URI PARAMS" << std::endl;
  std::string response;
  response = "<html><body><h2>User:" + params["user_name"] + "</h2></body></html>";
  res.send_html(response.c_str());
}

int main(int argc, const char * argv[]) {
    WEBPP::Server t(AF_INET6, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/", home_page);
    t.add_route("/favicon.ico", favicon);
    t.add_route("/user/", user_form);
    t.add_route("/user/:user_name", user_id);
    t.add_route("/json", [](WEBPP::Responder responder, REQUEST req,  URL_PARAMETERS params)->void{
      std::cout << "Sending JSON" << std::endl;
      responder.send_json(
        "{\n\"JSON\":\"data\",\n\"array\":[1,2,3],\n\"key\":\"value\"\n}"
      );
    });
    t.start();
    return 0;
}
