# WEBPP

WEBPP(Web plus plus) is a C++ framework for web servers.

## Installation

Using cmake and make install.(This will install to default path)

```bash
mkdir build
cd build
cmake ..
sudo make install
```
When compiling one must use the link the WEBPP library.
There is a compile srcipt in the demo folder.

## Usage

```cpp
#include <webpp.hpp>

// Use webpp to send static html files
void home_page(RESPONDER res, REQUEST req, URL_PARAMETERS params){
  res.send_file("index.html", "html");
}

// One can also use route parameters:
void url_param(RESPONDER res, REQUEST req, URL_PARAMETERS params){
  std::string response;
  response = "<html><body><h2>User:" + params["user_name"] + "</h2></body></html>";
  res.send_html(response.c_str());
}

int main(){
    WEBPP::Server t(AF_INET6, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/", home_page);
    // Add routes with lambda signature...
    t.add_route("/hello_world", []WEBPP::Responder responder, REQUEST req,  URL_PARAMETERS params)->void{
        responder.send_html("<html><body><h1>Hello World</h1></body></html>");
    });
    // Define url parameters...
    t.add_route("/user/:user_name", url_param);
    return 0;
}
```


## Contributing

Pull requests are welcome. Please open issues
to discuss any features you would like to change, or see added. If anyone would like to contribute or has suggestions let me know. I can be reached at graeme.gilmour.bates@gmail.com

## License

[MIT](https://choosealicense.com/licenses/mit/)
