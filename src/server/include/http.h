// http.h

#pragma once

#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <map>

static std::map<int, std::string> status_messages{
    {100, "Continue"},
    {101, "Switching Protocols"},
    {103, "Checkpoint"},
    {200, "OK"},
    {201, "Created"},
    {202, "Accepted"},
    {203, "Non-Authoritative Information"},
    {204, "No Content"},
    {205, "Reset Content"},
    {206, "Partial Content"},
    {300, "Multiple Choices"},
    {301, "Moved Permanently"},
    {302, "Found"},
    {303, "See Other"},
    {304, "Not Modified"},
    {306, "Switch Proxy"},
    {307, "Temporary Redirect"},
    {308, "Resume Incomplete"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {402, "Payment Required"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {406, "Not Acceptable"},
    {407, "Proxy Authentication Required"},
    {408, "Request Timeout"},
    {409, "Conflict"},
    {410, "Gone"},
    {411, "Length Required"},
    {412, "Precondition Failed"},
    {413, "Request Entity Too Large"},
    {414, "Request-URI Too Long"},
    {415, "Unsupported Media Type"},
    {416, "Requested Range Not Satisfiable"},
    {417, "Expectation Failed"},
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"},
    {505, "HTTP Version Not Supported"},
    {511, "Network Authentication Required"},
};

static std::map<std::string, std::string> content_types{
    {"html", "text/html"},
    {"css", "text/css"},
    {"txt", "text/plain"},
    {"csv", "text/csv"},
    {"xml", "text/xml"},
    {"js", "application/javascript"},
    {"json", "application/json"},
    {"jpg", "image/jpeg"},
    {"jpeg", "image/png"},
    {"png", "image/png"},
    {"ico", "image/x-icon"},
};

#endif
