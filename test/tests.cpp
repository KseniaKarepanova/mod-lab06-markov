// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>

using namespace std;
typedef deque<string> prefix; // очередь префиксов


TEST(test1, test_Prefix) {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file1.txt");
    vector<string> words = split_text(text);
    deque<prefix> prefixes = Prefix(words);

    int expected_count = 2;

    EXPECT_EQ(prefixes[0].size(), expected_count);
}


TEST(test2, test_Prefix_Suffix) {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file1.txt");
    vector<string> words = split_text(text);
    map<prefix, vector<string>> statetab = Prefix_Suffix(words); // префикс-суффиксы
    prefix new_prefix;
    new_prefix.push_back("Куртка");
    new_prefix.push_back("шофёра");

    string suf = Generation_pref_suf(new_prefix);
    string suf_expected = "Пахнет";
    EXPECT_EQ(suf, suf_expected);
}

TEST(test3, test_Prefix_Suffix2) {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file2.txt");
    vector<string> words = split_text(text);
    map<prefix, vector<string>> statetab = Prefix_Suffix(words); // префикс-суффиксы
    prefix new_prefix;
    new_prefix.push_back("Слово");
    new_prefix.push_back("может");
    vector<string> suffixes;
    suffixes.push_back("согреть");
    suffixes.push_back("нам");

    string suf = Generation_pref_suf(new_prefix);
    bool flag = false;
    bool expected_flag = true;
    for (int i = 0; i < suffixes.size(); i++) {
        if (suffixes[i] == suf) flag = true;
    }
    EXPECT_EQ(flag, expected_flag);
}

TEST(test4, test_LengthText1) {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file3.txt");
    vector<string> words = split_text(text);
    Prefix_Suffix(words); // префикс-суффиксы
    string generate_text = Generation();

    vector<string> txt_split = split_text(generate_text);
    int expected_length = 3;
    EXPECT_EQ(txt_split.size(), expected_length);
}

TEST(test5, test_LengthText2) {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file1.txt");
    vector<string> words = split_text(text);
    Prefix_Suffix(words); // префикс-суффиксы
    string generate_text = Generation();

    vector<string> txt_split = split_text(generate_text);
    int expected_length = 3;
    bool flag = false;

    int count_word_in_prefix = 2;
    int max_length = 1000;
    if ((txt_split.size() >= count_word_in_prefix) && (txt_split.size() <= max_length)) flag = true;
    bool expected_flag = true;

    EXPECT_EQ(flag, expected_flag);
}
