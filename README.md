# WEBPP

A lightweight HTTP server framework written in C++ from raw POSIX sockets. Built as a learning project in systems programming, WEBPP exposes a simple Express-style routing API for serving static files and handling HTTP requests without any third-party networking libraries.

> **Note:** This is an experimental project. It has been run in production (briefly hosted its own documentation site) but is not battle-hardened — expect rough edges around concurrency and error handling.

## Features

- HTTP server built from raw socket programming (no Boost.Asio, no libuv)
- Express-style route registration with `add_route()`
- Static file serving with MIME type hints
- URL parameter support via `URL_PARAMETERS`
- Separate `start()` (local) and `deploy()` (server) modes
- Built and installed as a shared library via CMake

## Requirements

- C++11 or later
- CMake 3.x+
- POSIX-compatible OS (Linux / macOS)

## Installation

```bash
git clone https://github.com/graemegilmourbates/webpp.git
cd webpp
mkdir build && cd build
cmake ..
sudo make install
```

This installs the `WEBPP` library and headers to your system's default prefix. When compiling your own project, link against `-lwebpp`. A compile script is included in the `demo/` folder for reference.

## Usage

```cpp
#include <WEBPP/webpp.hpp>

void home_page(RESPONDER &res, REQUEST &req, URL_PARAMETERS params) {
    res.send_file("pages/app.html", "html");
}

int main(int argc, const char *argv[]) {
    WEBPP::Server server;
    server.add_route("/", home_page);

    if (argc > 1 && std::string(argv[1]) == "deploy") {
        server.deploy();  // bind to 0.0.0.0 for external access
    } else {
        server.start();   // local development mode
    }

    return 0;
}
```

Compile against the installed library:

```bash
g++ -std=c++11 main.cpp -lwebpp -o myapp
```

Or see `demo/` for an example compile script.

## Project Structure

```
webpp/
├── include/        # Public headers (webpp.hpp, etc.)
├── src/            # Server, request/response, router implementation
├── demo/           # Example application and compile script
├── CMakeLists.txt
└── webpp.pc.in     # pkg-config template
```

## Known Limitations

- **No multithreading** — the server handles one connection at a time; sustained load will back up quickly
- **No keep-alive** — each request opens and closes a connection
- **Minimal HTTP compliance** — basic GET/response cycle works; edge cases in headers and chunked encoding are unhandled
- **No TLS** — plaintext HTTP only

These are the main reasons it crashed under real traffic. Contributions welcome.

## Contributing

Pull requests are welcome. Open an issue first to discuss anything you'd like to change or add. You can also reach out directly at [graeme.gilmour.bates@gmail.com](mailto:graeme.gilmour.bates@gmail.com).

## License

[MIT](https://choosealicense.com/licenses/mit/)
