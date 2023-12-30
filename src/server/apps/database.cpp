#include "database.h"

Database::Database()
{
  read_env_file("src/server/.env", env);

  int rc = sqlite3_open(env["DB_PATH"].data(), &db);

  if (rc)
  {
    fmt::print("Can't open database: {}\n", sqlite3_errmsg(db));
    sqlite3_close(db);
  }
}

Database::~Database()
{
  sqlite3_close(db);
}

void Database::execute_query(std::string query, int (*callback)(void *, int, char **, char **))
{
  char *zErrMsg = 0;

  int rc = sqlite3_exec(db, query.data(), callback, 0, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    fmt::print("SQL error: {}\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
}
