// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::string text = read_file("file1.txt");
    std::vector<std::string> words = split_text(text);
    std::deque<prefix> prefixes = Prefix(words);
    Prefix_Suffix(words);
    std::string new_text = Generation();
    std::cout << new_text;
}
