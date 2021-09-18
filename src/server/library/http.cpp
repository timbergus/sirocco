#include "include/http.h"

HTTP::HTTP()
{
}

HTTP::~HTTP()
{
}

std::string HTTP::get_status_message(int http_status_code)
{
  return http_status_messages[http_status_code];
}

std::string HTTP::get_content_type(std::string extension)
{
  return content_types[extension];
}
