#include "utils.h"

int main()
{
  std::string contents{read_file("../src/tests/mocks/message.txt")};

  if (contents == "Hello, world!\n")
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
