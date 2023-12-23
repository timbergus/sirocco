#include "utils.h"

int main()
{
  std::vector<std::string> sample{"0", "1", "2", "3", "4", "5"};

  std::string vector = stringify_vector(sample);

  if (vector == "[\"0\", \"1\", \"2\", \"3\", \"4\", \"5\"]")
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
