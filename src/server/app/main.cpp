#include <sqlite3.h>

#include "sirocco.h"
#include "actions.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
  int i;
  fprintf(stderr, "%s: \n", (const char *)data);

  for (i = 0; i < argc; i++)
  {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}

int main()
{
  // DDBB

  sqlite3 *db;

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

  sqlite3_close(db);

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
