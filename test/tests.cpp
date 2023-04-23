// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include "textgen.h"
typedef std::deque<std::string> prefix;

TEST(test1, test_Prefix) {
    std::string text = read_file("file1.txt");
    std::vector<std::string> words = split_text(text);
    std::deque<prefix> prefixes = Prefix(words);

    int expected_count = 2;
    EXPECT_EQ(prefixes[0].size(), expected_count);
}

TEST(test2, test_Prefix_Suffix) {
    std::string text = read_file("file1.txt");
    std::vector<std::string> words = split_text(text);
    std::map<prefix, std::vector<std::string>>
        statetab = Prefix_Suffix(words);
    prefix new_prefix;
    new_prefix.push_back("What");
    new_prefix.push_back("is");
    std::string suf = Generation_pref_suf(new_prefix);
    std::string suf_expected = "this";
    EXPECT_EQ(suf, suf_expected);
}

TEST(test3, test_Prefix_Suffix2) {
    std::string text = read_file("file1.txt");
    std::vector<std::string> words = split_text(text);
    std::map < prefix, std::vector < std::string>>
        statetab = Prefix_Suffix(words);
    prefix new_prefix;
    new_prefix.push_back("time");
    new_prefix.push_back("to");
    std::vector<std::string> suffixes;
    suffixes.push_back("stand");
    suffixes.push_back("see");
    suffixes.push_back("turn");
    suffixes.push_back("wait");

    std::string suf = Generation_pref_suf(new_prefix);
    bool flag = false;
    bool expected_flag = true;
    for (int i = 0; i < suffixes.size(); i++) {
        if (suffixes[i] == suf) flag = true;
    }
    EXPECT_EQ(flag, expected_flag);
}

TEST(test4, test_LengthText) {
    std::string text = read_file("file1.txt");
    std::vector<std::string> words = split_text(text);
    std::map<prefix, std::vector<std::string>>
        statetab = Prefix_Suffix(words);
    std::string generate_text = Generation();
    std::vector<std::string> txt_split = split_text(generate_text);
    int expected_length = 1000;
    
    EXPECT_EQ(txt_split.size(), expected_length);
}

