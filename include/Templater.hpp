#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Logger.hpp"

#ifndef TEMPLATER
#define TEMPLATER

namespace HTML {
  // Forward declarations
  class Node;
  class Doc;

  // Attribute class for HTML tags
  class Attribute {
  public:
    std::string name;
    std::vector<std::string> values;

    Attribute(std::string t_name) : name(t_name) {}

    Attribute(std::string t_name, std::vector<std::string> t_values) : name(t_name) {
      for(const std::string& value : t_values){
        add_value(value);
      }
    }

    void add_value(std::string t_value) {
      values.push_back(t_value);
    }
  };

  // The actual HTML tags
  class Node {
    public:
    std::string name;
    std::string body;
    bool self_closing;
    std::vector<Node> content;
    std::vector<Attribute> attributes;
    Node(std::string t_name, bool is_self_closing = false)
        : name(t_name), self_closing(is_self_closing) {}

    // Method for adding attributes like <a attribute="value value" />
    Node& operator()(std::string t_attribute, std::vector<std::string> t_values) {
      Attribute attr(t_attribute);
      for (std::string value : t_values) {
        attr.add_value(value);
      }
      attributes.push_back(attr);
      return *this;
    }

    // Method for adding body content like <a>body</a>
    Node& operator()(std::string t_body) {
      body = t_body;
      return *this;
    }

    // Method for adding child nodes
    Node& operator()(const Node& node) {
      content.push_back(node);
      return *this;
    }

    // Generate the opening tag
    std::string open() const {
      std::stringstream out;
      out << "<" << name;
      for (const Attribute& attr : attributes) {
        logger->log("Adding attribute");
        out << " " << attr.name << "=\"";
        for (const std::string& attr_value : attr.values) {
          out << attr_value << " ";
        }
        out << "\"";
      }
      if (self_closing) {
        out << "/";
      }
      out << ">";
      return out.str();
    }

    // Generate the closing tag
    std::string close() const {
      if (!self_closing) {
        std::stringstream out;
        out << "</" << name << ">\n";
        return out.str();
      }
      return "";
    }

    // Render the node and its child nodes as HTML string
    std::string render() const {
      std::stringstream out;
      out << open();
      if (!self_closing) {
        out << body;
        for (const Node& element : content) {
          out << element.render();
        }
        out << close();
      }
      return out.str();
    }
  };

  // Wrapper to create a complete HTML page
  class Doc {
  private:
    std::string file_type;
    Node html;
    Node head; // html.content[0]
    Node body; // html.content[1]

  public:
    Doc()
        : file_type("<!DOCTYPE html>"), html("html"), head("head"), body("body") {
      html(head)(body);
    }

    // Method for adding content to the <head> tag
    Doc& operator()(const Node& t_content) {
      html.content[0](t_content);
      return *this;
    }

    // Method for adding content to the <body> tag
    Doc& operator[](const Node& t_content) {
      html.content[1](t_content);
      return *this;
    }

    // Render the HTML document as a string
    std::string render() const {
      std::stringstream out;
      out << file_type << "\n" << html.render();
      return out.str();
    }
  };

  // Convenience function to create an attribute
  inline Attribute attr(
    const std::string& name,
    const std::vector<std::string> values
  ) {
    Attribute attribute(name, values);
    return attribute;
  }

  // Convenience function to create an HTML tag with attributes and body
  inline Node tag(
    const std::string& name,
    const std::vector<Attribute> t_attributes,
    const std::string& body) {
    Node node(name);
    for(const auto& attribute : t_attributes){
      node(attribute.name, attribute.values);
    }
    node(body);
    return node;
  }

  // Convenience function to create an HTML tag with attributes
  inline Node tag(
    const std::string& name,
    const std::vector<Attribute> t_attributes
  ) {
    Node node(name);
    for(const auto& attribute : t_attributes){
      node(attribute.name, attribute.values);
    }
    return node;
  }

  // Convenience function to create an HTML tag with body
  inline Node tag(const std::string& name, const std::string& body) {
    Node node(name);
    node(body);
    return node;
  }

  // Convenience function to create a self-closing HTML tag
  inline Node selfClosingTag(const std::string& name) {
    return Node(name, true);
  }

  // Convenience function to create an HTML tag without attributes or body
  inline Node tag(const std::string& name) {
    return Node(name);
  }
}

#endif
