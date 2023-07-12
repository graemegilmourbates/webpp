#include <iostream>
#include <unordered_map>
#include <WEBPP/webpp.hpp>
#include <stdlib.h>
#include <string>
#include <WEBPP/Templater.hpp>

#include "index.hpp"



void home_page(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_html(index().c_str());
}

void sockets(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/sockets.html", "html");
}

void server(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/server.html", "html");
}

void router(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/router.html", "html");
}

void responder(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/responder.html", "html");
}

void favicon(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_image("public/images/favicon.ico");
}

void user_form(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
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
    res.send_html(response.c_str());
  }
}

void user_id(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  std::string response;
  response = "<html><body><h2>User:" + params["user_name"] + "</h2></body></html>";
  res.send_html(response.c_str());
}

void json(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_json(
    "{\n\"JSON\":\"data\",\n\"array\":[1,2,3],\n\"key\":\"value\"\n}"
  );
}

int main(int argc, const char * argv[]) {
  WEBPP::Server t;
  t.add_route("/favicon.ico", favicon);
  t.add_route("/user/", user_form);
  t.add_route("/user/:user_name", user_id);
  t.add_route("/json", json);
  t.add_route("/", home_page);
  t.add_route("/sockets", sockets);
  t.add_route("/server", server);
  t.add_route("/router", router);
  t.add_route("/responder", responder);
  if(argc == 1){
    logger >> "No extra commands passed... Sever not deployed...";
    t.start();
  } else {
    std::string arg = argv[1];
    if(arg=="deploy"){
      t.deploy();
    } else {
      t.start();
    }
  }
  return 0;
}
