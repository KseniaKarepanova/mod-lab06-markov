// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <ctime>
#include <stdlib.h>
#include"textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string>> statetab;

std::string read_file(std::string filename) {
    std::ifstream input_file(filename.c_str());
    if (!input_file.is_open()) {
        std::cout << "Error: could not open file \""
            << filename << "\"" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string input_text = "";
    std::string line;
    while (getline(input_file, line)) {
        input_text += line + "\n";
    }
    input_file.close();
    return input_text;
}

std::vector<std::string> split_text(std::string input_text) {
    std::vector<std::string> words;
    std::string word = "";
    for (unsigned int i = 0; i < input_text.length(); i++) {
        if (input_text[i] == ' ' || input_text[i] == '\n' ||
            input_text[i] == '\r' || input_text[i] == '\t') {
            if (word != "") {
                words.push_back(word);
                word = "";
            }
        }
        else {
            word += input_text[i];
        }
    }
    if (word != "") {
        words.push_back(word);
    }
    return words;
}

std::deque<prefix> Prefix(std::vector<std::string> words) {
    std::deque <prefix> prefixes;
    std::string word = "";
    for (int i = 0; i < words.size() - NPREF; i++)
    {
        prefix temp;
        for (int j = 0; j < NPREF; j++)
        {
            temp.push_back(words[j + i]);
        }
        prefixes.push_back(temp);
    }
    return prefixes;
}

std::vector<std::string> Suffix(prefix prefixes,
    std::vector<std::string> words) {
    std::vector<std::string> suffix;
    for (int i = 0; i < words.size() - NPREF; i++) {
        for (int j = 0; j < NPREF; j++) {
            if (prefixes[j] != words[i + j]) {
                break;
            }
            if (j == NPREF - 1)
                suffix.push_back(words[i + NPREF]);
        }
    }
    return suffix;
}

std::map<prefix, std::vector<std::string>> Prefix_Suffix
(std::vector<std::string> words) {
    std::deque<prefix> prefixes = Prefix(words);

    for (int i = 0; i < prefixes.size(); i++) {
        std::map<prefix, std::vector<std::string>>::iterator
            it = statetab.find(prefixes[i]);
        if (it == statetab.end()) {
            statetab.insert({ prefixes[i],Suffix(prefixes[i],words) });
        }
        else {
            std::vector<std::string> suf = it->second;
            for (int i = 0; i < Suffix(prefixes[i], words).size(); i++) {
                suf.push_back(Suffix(prefixes[i], words)[i]);
            }
        }
    }
    return statetab;
}

prefix GenerationPrefix() {
    int index = rand() % statetab.size();
    std::deque<prefix> keys;
    for (auto it = statetab.begin(); it != statetab.end(); it++) {
        keys.push_back(it->first);
    }
    prefix prefix_new = keys[index];
    return prefix_new;
}

std::string Generation_pref_suf(prefix prefix_new) {
    std::string text = "";
    srand(time(NULL));
    std::vector<std::string> suffixes;
    for (int i = 0; i < statetab.size(); i++) {
        std::map<prefix, std::vector<std::string>>::iterator
            it = statetab.find(prefix_new);
        if (it != statetab.end()) {
            suffixes = it->second;
            break;
        }
    }
    if (suffixes.size() == 0) {
        return "";
    }
    else {
        int index = rand() % suffixes.size();
        return suffixes[index];
    }
}

std::string Generation() {
    std::string text = "";
    srand(time(NULL));
    prefix prefix_new = GenerationPrefix();
    for (int i = 0; i < prefix_new.size(); i++) {
        text = text + " " + prefix_new[i];
    }
    for (int j = 0; j < MAXGEN; j++) {
        std::vector<std::string> suffixes;
        for (int i = 0; i < statetab.size(); i++) {
            std::map<prefix, std::vector<std::string>>::iterator
                it = statetab.find(prefix_new);
            if (it != statetab.end()) {
                suffixes = it->second;
                break;
            }
        }
        if (suffixes.size() == 0) {
            break;
        }
        else {
            int index = rand() % suffixes.size();
            text = text + " " + suffixes[index];
            prefix_new.pop_front();
            prefix_new.push_back(suffixes[0]);
        }
    }
    return text;
}
