#include "actions.h"
#include "library/sirocco.h"

int main()
{
  Sirocco server(3000);

  server.handle_response("GET", "/home", get_home);
  server.handle_response("GET", "/home/id", get_home);
  server.handle_response("POST", "/home", get_home);
  server.handle_response("PUT", "/home", get_home);
  server.handle_response("DELETE", "/home", get_home);

  server.listening();

  return EXIT_SUCCESS;
}
