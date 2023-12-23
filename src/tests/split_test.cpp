#include "utils.h"

int main()
{
  std::string sample{"a,b,c,d,e"};

  std::vector<std::string> tokens;

  split(sample, ",", tokens);

  if (tokens.size() == 5)
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
