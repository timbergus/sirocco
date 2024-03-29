#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "utils.h"
#include "comms.h"
#include "database.h"

Database db;
nlohmann::json data;

// Get all users.

static int get_users_callback([[maybe_unused]] void *NotUsed, int argc, char **argv, char **azColName)
{
  std::map<std::string, std::string> db_result;

  for (int i = 0; i < argc; i++)
  {
    db_result[azColName[i]] = argv[i] ? argv[i] : "NULL";
  }

  data = nlohmann::json::parse(stringify_map(db_result));

  return EXIT_SUCCESS;
}

const auto get_users = [](Comms comms)
{
  db.execute_query("SELECT * from users", get_users_callback);
  comms.send_contents(data.dump(4), "json");
};

// Create a new user.

static int post_users_callback(
    [[maybe_unused]] void *NotUsed,
    [[maybe_unused]] int argc,
    [[maybe_unused]] char **argv,
    [[maybe_unused]] char **azColName)
{
  return EXIT_SUCCESS;
}

const auto post_users = [](Comms comms)
{
  try
  {
    nlohmann::json data = nlohmann::json::parse(comms.request.payload);

    std::string query = fmt::format("INSERT INTO users (name, surname, email) VALUES ('{}', '{}', '{}')",
                                    static_cast<std::string>(data["name"]),
                                    static_cast<std::string>(data["surname"]),
                                    static_cast<std::string>(data["email"]));

    db.execute_query(query.data(), post_users_callback);
    comms.send_contents(data.dump(4), "json");
  }
  catch (const std::exception &e)
  {
    comms.send_contents(fmt::format("<h1>Unexpected server error</h1><br><p>{}</p>", e.what()), "html", 500);
  }
};
