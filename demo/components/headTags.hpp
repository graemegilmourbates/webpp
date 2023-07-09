#include <WEBPP/Templater.hpp>
#include <string>
#include <vector>

std::vector<Node> head_tags(){
  std::vector<Node> tgs;
  // Meta
  tgs.push_back(cls_tag("meta", {attr("charset", {"utf-8"})}));
  tgs.push_back(cls_tag("meta", {
    attr("name", {"viewport"}),
    attr("content", {"width=device-width, initial-scale=1"})
  }));
  // Link bootstrap
  tgs.push_back(
    tag("link", {
        attr("rel", {"stylesheet"}),
        attr("href", {"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css"}),
        attr("integrity", {"sha384-..."}), // Add the integrity attribute if needed
        attr("crossorigin", {"anonymous"}) // Add the crossorigin attribute if needed
      }
    )
  );
  return tgs;
}
