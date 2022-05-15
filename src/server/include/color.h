// color.h

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <map>

class Color
{
private:
  std::map<std::string, std::string> color_map{
      {"black", "30"},
      {"red", "31"},
      {"green", "32"},
      {"yellow", "33"},
      {"blue", "34"},
      {"magenta", "35"},
      {"cyan", "36"},
      {"white", "37"},
  };

  std::map<std::string, std::string> type_map{
      {"reset", "0"},
      {"bold", "1"},
      {"underline", "4"},
      {"blink", "5"},
      {"reverse", "7"},
      {"hidden", "8"},
  };

public:
  Color();
  ~Color();

  std::string set_color(std::string, std::string, std::string);
};

Color::Color()
{
}

Color::~Color()
{
}

std::string Color::set_color(std::string message, std::string color, std::string type = "reset")
{
  return "\033[" + type_map[type] + ";" + color_map[color] + "m" + message + "\033[0m";
}

#endif // COLOR_H
