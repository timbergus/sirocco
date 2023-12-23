#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

void split(std::string_view, std::string_view, std::vector<std::string> &);
std::string stringify_vector(const std::vector<std::string> &);
std::string stringify_map(const std::map<std::string, std::string> &);

std::string read_file(std::string_view fileName);
void read_env_file(std::string_view envFile, std::map<std::string, std::string> &env);
