#include <fstream>
#include <nlohmann/json.hpp>

#include "comm.h"
#include "utils.h"

const auto get_home = [](Comm comm)
{
  comm.response.set_status_code(200);
  comm.send_file("index.html");
};

const auto get_secure = [](Comm comm)
{
  comm.response.set_status_code(500);
  comm.send_html("<h1>Server is dead!</h1><br /><p>" +
                 Utils::stringify_vector(comm.request.parsed.path) +
                 "</p><br /><p>" +
                 Utils::stringify_map(comm.request.parsed.query) + "</p>");
};

const auto post_secure = [](Comm comm)
{
  comm.response.set_status_code(200);
  comm.send_text("Thanks for the info!");
};

const auto put_secure = [](Comm comm)
{
  nlohmann::json data;
  std::ifstream json_file("src/server/public/database.json");

  if (json_file.is_open())
  {
    json_file >> data;
    comm.response.set_status_code(202);
  }
  else
  {
    data = nlohmann::json::object();
    comm.response.set_status_code(404);
  }

  comm.send_json(data.dump(4));
};

const auto delete_secure = [](Comm comm)
{
  comm.response.set_status_code(401);
  comm.send_html("<h1>Sorry. Not enough permission!</h1>");
};
