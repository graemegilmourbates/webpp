#include <string>
#include <sstream>
#include <vector>
#include <map>

#ifndef TEMPLATER
#define  TEMPLATER

namespace HTML{
  // Things like, style, href, class etc...
  class Attribute{
  public:
    std::string name;
    std::vector<std::string> values;

    Attribute(std::string t_name){
      name = t_name;
    }

    void add_value(std::string t_value){
      values.push_back(t_value);
    }
  };
  // The actual html tags
  class Node{
  public:
    // Here body is text like: <a>body</a>
    // and content is inner tags like: <a><content>body</content></a>
    std::string name, body;
    bool self_closing;
    std::vector<Node> content;
    std::vector<Attribute>  attributes;

    Node(std::string t_name){
      name = t_name;
      self_closing = false;
    }
    Node(std::string t_name, bool is_self_closing) : Node(t_name){
      self_closing = is_self_closing;
    }
    // Adding attributes like <a attribute="value value" />
    void add_attribute(
      std::string t_attribute,
      std::vector<std::string> t_values
    ){
      Attribute attr(t_attribute);
      for(std::string value : t_values){
        attr.add_value(value);
      }
    }
    void add_body(std::string t_body){
      body = t_body + "\n";
    }
    // Generate the open and close tag
    // Note: for self closing, only use open.
    std::string open(){
      std::stringstream out;
      out << "<" << name;
      for(Attribute attr : attributes){
        out << " ";
        out << attr.name << "=\"";
        for(std::string attr_value : attr.values){
          out << attr_value << " ";
        }
        out << "\"";
      }
      if(self_closing) out << "/";
      out << ">";
      return out.str();
    }
    std::string close(){
      std::stringstream out;
      out << "</" << name << ">\n";
      return out.str();
    }
    // Return string of html
    std::string render(){
      std::stringstream out;
      out << open();
      if(!self_closing){
        out << "\n" << body;
        for(Node element : content){
          out << element.render();
        }
        out << close();
      }
      return out.str();
    }
  };
  // Wrapper to create complete html page.
  // Always access head and body with 0 and 1 respectivly in html.content[]
  class Doc{
  private:
    std::string file_type;
    Node html;
    Node head; // html.content[0]
    Node body; // html.content[1]
  public:
    Doc(): html("html"), head("head"), body("body"){
      file_type = "<!DOCTYPE html>";
      html.content.push_back(head);
      html.content.push_back(body);
    }

    void add_to_head(Node t_content){
      html.content[0].content.push_back(t_content);
    }

    void add_to_body(Node t_content){
      html.content[1].content.push_back(t_content);
    }

    std::string render(){
      std::stringstream out;
      out << file_type;
      out << "\n";
      out << html.render();
      return out.str();
    }
  };

}

#endif
