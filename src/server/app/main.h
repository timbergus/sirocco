#include <functional>

#include "sirocco.h"
#include "json.h"
#include "comm.h"
#include "utils.h"

std::function<void(Comm)> get_home = [](Comm comm)
{
  comm.response.set_status_code(200);
  comm.send_file("index.html");
};

std::function<void(Comm)> get_secure = [](Comm comm)
{
  comm.response.set_status_code(500);
  comm.send_html("<h1>Server is dead!</h1><br /><p>" +
                 Utils::stringify_vector(comm.request.parsed.path) +
                 "</p><br /><p>" +
                 Utils::stringify_map(comm.request.parsed.query) + "</p>");
};

std::function<void(Comm)> post_secure = [](Comm comm)
{
  comm.response.set_status_code(200);
  comm.send_text("Thanks for the info!");
};

std::function<void(Comm)> put_secure = [](Comm comm)
{
  std::map<std::string, std::string> data{{"hello", "world"}, {"bye", "moon"}};

  comm.response.set_status_code(202);
  comm.send_json(JSON::stringify(data));
};

std::function<void(Comm)> delete_secure = [](Comm comm)
{
  comm.response.set_status_code(401);
  comm.send_html("<h1>Sorry. Not enough permission!</h1>");
};
