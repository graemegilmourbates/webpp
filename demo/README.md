# Web ++ Demo

This Demo Project is currently up and running [here](http://webxplusplus.com).

## Installation

The installation requires cmake and has not been tested on windows.
Download the git repo. Navigate inside and...

```bash
mkdir build
cd build
cmake ..
sudo make install
```

This should install the headers and library in your user default location. I believe on ubuntu I had to link the path.

## Usage

```cpp
#include <WEBPP/webpp.hpp>

void home(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
    res.send_file("index.html");
}
int main(){
    WEBPP::Server serv;
    serv.add_route("/", home);
    serv.start();
    return 0;
}
```
I have included a compile.sh script to make it easy, following the naiming main.cpp

## Functionality

```cpp
// Below are some functionality examples:

// Using json response
void json_response(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
    // Here is the simple functionality, in practice a json parsing
    // library would be helpful.
    res.send_json(
    "{\n\"JSON\":\"data\",\n\"array\":[1,2,3],\n\"key\":\"value\"}"
  );
}

// Handling Favicon Image.
void favicon(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
    res.send_image("public/images/favicon.ico");
}

// Handling form data
void user_form(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  if(req["Method"] == "GET"){
    res.send_file("user_form.html", "html");
  } else if(req["Method"] == "POST"){
    std::string response;
    std::unordered_map user_form_data = WEBPP::get_form_data(req["Body"]);
    // Accessing form data.
    std::cout << "name: " << user_form_data["name"] << std::endl;
    std::cout << "email: " << user_form_data["email"] << std::endl;

    res.send_html("<html><body><h1>User Submitted</h1></body></html>");
  }
}

```



## License

[MIT](https://choosealicense.com/licenses/mit/)
