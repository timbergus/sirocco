#include "http.h"

sirocco::HTTP::HTTP()
{
}

sirocco::HTTP::~HTTP()
{
}

std::string sirocco::HTTP::get_status_message(int http_status_code)
{
  return http_status_messages[http_status_code];
}
