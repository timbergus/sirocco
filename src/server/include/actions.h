#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "utils.h"
#include "comms.h"

const auto get_home = [](Comms comms)
{
  comms.send_file(comms.request.path_tokens[1]);
};

const auto get_secure = [](Comms comms)
{
  comms.send_contents("<h1>Server is dead!</h1><br /><p>" +
                          stringify_vector(comms.request.path_tokens) +
                          "</p><br /><p>" +
                          stringify_map(comms.request.query_tokens) + "</p>",
                      "html", 500);
};

const auto post_secure = [](Comms comms)
{
  comms.send_contents("Thanks for the info!", "txt");
};

const auto put_secure = [](Comms comms)
{
  nlohmann::json data;
  std::string file = read_file("src/server/public/database.json");

  if (file.empty())
  {
    data = nlohmann::json::object();
    set_status_code(404, comms.response);
  }
  else
  {
    data = nlohmann::json::parse(file);
    set_status_code(202, comms.response);
  }

  comms.send_contents(data.dump(4), "json");
};

const auto delete_secure = [](Comms comms)
{
  comms.send_contents("<h1>Sorry. Not enough permission!</h1>", "html", 401);
};
