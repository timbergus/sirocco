#pragma once

#include <string>
#include <vector>
#include <map>

void split(const std::string &, const std::string &, std::vector<std::string> &);
std::string stringify_vector(const std::vector<std::string> &);
std::string stringify_map(const std::map<std::string, std::string> &);

std::string read_file(std::string);
void read_env_file(std::string, std::map<std::string, std::string> &);
