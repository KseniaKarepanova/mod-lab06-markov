// Copyright 2021 GHA Test Team
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>

typedef std::deque<std::string> prefix;

std::string read_file(std::string filename);
std::vector<std::string> split_text(std::string input_text);
std::deque<prefix> Prefix(std::vector<std::string> words);
std::vector<std::string> Suffix(prefix prefixes,
    std::vector<std::string> words);
std::map<prefix, std::vector<std::string>> Prefix_Suffix
(std::vector<std::string> words);
prefix GenerationPrefix();
std::string Generation();
std::string Generation_pref_suf(prefix prefix_new);
