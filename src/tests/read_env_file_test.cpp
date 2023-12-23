#include "utils.h"

int main()
{
  std::map<std::string, std::string> env;

  read_env_file("../src/tests/mocks/.env", env);

  if (env["ROOT_PATH"] == "src/server")
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
