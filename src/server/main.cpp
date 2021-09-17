#include "main.h"

int main()
{
  Sirocco server(3000);

  // server.get("/", get_home);
  server.get("/secure/id", get_secure);
  server.post("/secure", post_secure);
  server.put("/secure", put_secure);
  server.del("/secure", delete_secure);

  server.listening();

  return EXIT_SUCCESS;
}
