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
#include <WEBPP/webpp.hpp>

void home_page(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/app.html", "html");
}

int main(int argc, const char * argv[]) {
  WEBPP::Server t;
  t.add_route("/", home_page);
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
```


## Contributing

Pull requests are welcome. Please open issues
to discuss any features you would like to change, or see added. If anyone would like to contribute or has suggestions let me know. I can be reached at graeme.gilmour.bates@gmail.com

## License

[MIT](https://choosealicense.com/licenses/mit/)
