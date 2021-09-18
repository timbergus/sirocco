#include "main.h"

int main()
{
  Sirocco server(3000);

  server.set_public_path("public");

  server.get("/", get_home);
  server.get("/secure", get_secure);
  server.post("/secure", post_secure);
  server.put("/secure/id", put_secure);
  server.del("/secure/id", delete_secure);

  server.listening();

  return EXIT_SUCCESS;
}
