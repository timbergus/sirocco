#include "../include/actions.h"
#include "../include/server.h"

int main(int, char **)
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

  Server server({{"port", 3000}, {"public_path", "public"}});

  server.get("/", get_home);
  server.get("/secure", get_secure);
  server.post("/secure", post_secure);
  server.put("/secure", put_secure);
  server.del("/secure", delete_secure);

  server.listening();

  return EXIT_SUCCESS;
}
