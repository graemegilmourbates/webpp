#include <WEBPP/Templater.hpp>
#include <string>
#include <vector>
#include <sstream>

Node generate_copy(std::string t_title, std::string t_copy){
  Node copy = tag("div", {attr("class", {"col"})});
  copy[{
    tag("h3")(t_title),
    tag("p", {attr("class", {"lead"})})(t_copy)
  }];
  return copy;
}

Node home_page(){
  Node content = tag("div", {attr("class", {"container", "mt-2"})});
  content(tag("h1", {attr("class", {"display-4"})})("Web Plus Plus")(
    tag("small", {attr("class", {"text-muted"})})(": Hello World")
  ));

  std::stringstream hello_world;
  hello_world << "// Simple Example\n";
  hello_world << "#include &ltWEBPP/webpp.hpp&gt\n";
  hello_world << "#include &ltWEBPP/Template.hpp&gt\n";
  hello_world << "\n";
  hello_world << "using REQUEST = std::unordered_map&ltstd::string, std::string&gt;\n";
  hello_world << "using RESPONDER = WEBPP::Responder;\n";
  hello_world << "using URL_PARAMETERS = std::unordered_map&ltstd::string, std::string&gt;\n";
  hello_world << "\n";
  hello_world << "void hello_world(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){\n";
  hello_world << "\tHTML::Doc doc;\n";
  hello_world << "\tdoc[HTML::tag(\"h1\")(\"Hello World\")];\n";
  hello_world << "\tres.send_html(doc.render().c_str());\n";
  hello_world << "}\n";
  hello_world << "\n";
  hello_world << "int main(){\n";
  hello_world << "\tWEBPP::Server serv(AF_INET6, SOCK_STREAM, 0, 80, INADDR_ANY, 100);\n";
  hello_world << "\tserv.add_route(\"/\", hello_world);\n";
  hello_world << "\treturn 0;\n";
  hello_world << "}\n";
  content(tag("pre")(
    hello_world.str()
  ));
  return content;
}
