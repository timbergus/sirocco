#include "actions.h"
#include "library/sirocco.h"

int main()
{
  Sirocco server(3000);

  server.get("/home", get_home);

  server.post("/home", post_home);

  server.put("/home", put_home);

  server.del("/home", delete_home);

  server.listening();

  return EXIT_SUCCESS;
}
