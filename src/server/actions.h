#include <functional>

#include "library/json.h"
#include "library/comm.h"

std::function<void(Comm, http_url_t)> get_home = [](Comm comm, http_url_t request)
{
  comm.response.set_status(500);
  comm.send_html("<h1>Server is dead!</h1><br /><p>" + Utils::print_vector(request.path) + "</p><br /><p>" + Utils::print_map(request.query) + "</p>");
};

std::function<void(Comm, http_url_t)> post_home = [](Comm comm, __attribute__((unused)) http_url_t request)
{
  comm.response.set_status(200);
  comm.send_text("Thanks for the info!");
};

std::function<void(Comm, http_url_t)> put_home = [](Comm comm, __attribute__((unused)) http_url_t request)
{
  std::map<std::string, std::string> data{{"hello", "world"}, {"bye", "moon"}};

  comm.response.set_status(202);
  comm.send_json(JSON::stringify(data));
};

std::function<void(Comm, http_url_t)> delete_home = [](Comm comm, __attribute__((unused)) http_url_t request)
{
  comm.response.set_status(401);
  comm.send_html("<h1>Sorry. Not enough permission!</h1>");
};
