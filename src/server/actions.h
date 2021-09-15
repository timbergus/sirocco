#include <functional>

#include "library/json.h"
#include "library/comm.h"

std::function<void(Comm)> get_home = [](Comm comm)
{
  comm.response.set_status(500);
  comm.send_html("<h1>Server is dead!</h1><br /><p>" +
                 Utils::print_vector(comm.request.as_tokens.path) +
                 "</p><br /><p>" +
                 Utils::print_map(comm.request.as_tokens.query) + "</p>");
};

std::function<void(Comm)> post_home = [](Comm comm)
{
  comm.response.set_status(200);
  comm.send_text("Thanks for the info!");
};

std::function<void(Comm)> put_home = [](Comm comm)
{
  std::map<std::string, std::string> data{{"hello", "world"}, {"bye", "moon"}};

  comm.response.set_status(202);
  comm.send_json(JSON::stringify(data));
};

std::function<void(Comm)> delete_home = [](Comm comm)
{
  comm.response.set_status(401);
  comm.send_html("<h1>Sorry. Not enough permission!</h1>");
};
