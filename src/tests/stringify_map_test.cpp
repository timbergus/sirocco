#include "utils.h"

int main()
{
  std::map<std::string, std::string> sample{{"a", "0"}, {"b", "1"}, {"c", "2"}};

  std::string map = stringify_map(sample);

  if (map == "{\n  \"a\": \"0\",\n  \"b\": \"1\",\n  \"c\": \"2\"\n}")
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
