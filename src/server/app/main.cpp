#include <sqlite3.h>

#include "sirocco.h"
#include "actions.h"

// static int callback(void *data, int argc, char **argv, char **azColName)
// {
//   int i;
//   fprintf(stderr, "%s: \n", (const char *)data);

//   for (i = 0; i < argc; i++)
//   {
//     printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//   }

//   printf("\n");
//   return 0;
// }

int main()
{
  // DDBB

  /* sqlite3 *db;

  if (sqlite3_open("src/server/public/test.db", &db))
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return (0);
  }
  else
  {
    fprintf(stderr, "Opened database successfully\n");

    std::string sql;
    char *zErrMsg = 0;
    const char *data = "Callback function called";

    sql = "SELECT * from user";

    if (sqlite3_exec(db, sql.c_str(), callback, (void *)data, &zErrMsg) != SQLITE_OK)
    {
      std::cout << "ERROR!" << std::endl;
      sqlite3_free(zErrMsg);
    }
    else
    {
      std::cout << "SUCCESS!" << std::endl;
    }
  }

  sqlite3_close(db); */

  // DDBB.
  sqlite3 *connection = nullptr;

  int result = sqlite3_open("src/server/public/test.db", &connection);

  if (result != SQLITE_OK)
  {
    std::cout << sqlite3_errmsg(connection) << std::endl;
    sqlite3_close(connection);
    return result;
  }

  sqlite3_stmt *query = nullptr;

  result = sqlite3_prepare_v2(connection, "select 'Hello, World!'", -1, &query, nullptr);

  if (result != SQLITE_OK)
  {
    std::cout << sqlite3_errmsg(connection) << std::endl;
    sqlite3_close(connection);
    return result;
  }

  while (SQLITE_ROW == sqlite3_step(query))
  {
    std::cout << sqlite3_column_text(query, 0) << std::endl;
  }

  sqlite3_finalize(query);
  sqlite3_close(connection);

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

  /* Sirocco server({{"port", 3000}, {"public_path", "public"}});

  server.get("/", get_home);
  server.get("/secure", get_secure);
  server.post("/secure", post_secure);
  server.put("/secure/id", put_secure);
  server.del("/secure/id", delete_secure);

  server.listening(); */

  return EXIT_SUCCESS;
}
