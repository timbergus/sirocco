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
