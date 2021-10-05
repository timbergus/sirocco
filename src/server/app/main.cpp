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

int main()
{
  /**
   * The sever constructor receives an options map with the
   * following keys:
   *
   * * port: the port to listen on
   * * public_path: the path to the public directory
   * * debug: whether or not to enable debug mode
   *
   * Depending on the keys passed, certain features may be
   * enabled.
   */

  Sirocco server({{"port", 3000}, {"public_path", "public"}});

  server.get("/", get_home);
  server.get("/secure", get_secure);
  server.post("/secure", post_secure);
  server.put("/secure/id", put_secure);
  server.del("/secure/id", delete_secure);

  server.listening();

  return EXIT_SUCCESS;
}
