#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>
#include"textgen.h"
using namespace std;

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе
typedef deque<string> prefix; // очередь префиксов
map<prefix, vector<string>> statetab; // префикс-суффиксы


string read_file(string filename) {
    ifstream input_file(filename.c_str());
    if (!input_file.is_open()) {
        cout << "Error: could not open file \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    string input_text = "";
    string line;
    while (getline(input_file, line)) {
        input_text += line + "\n";
    }
    input_file.close();
    return input_text;


}

vector<string> split_text(string input_text) {
    vector<string> words;
    string word = "";
    for (unsigned int i = 0; i < input_text.length(); i++) {
        if (input_text[i] == ' ' || input_text[i] == '\n' || input_text[i] == '\r' || input_text[i] == '\t') {
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


deque<prefix> Prefix(vector<string> words) {

    deque <prefix> prefixes;


    string word = "";
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

vector<string> Suffix(prefix prefixes, vector<string> words) {

    vector<string> suffix;
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


map<prefix, vector<string>> Prefix_Suffix(vector<string> words) {
    deque<prefix> prefixes = Prefix(words);

    for (int i = 0; i < prefixes.size(); i++) {
        map<prefix, vector<string>>::iterator it = statetab.find(prefixes[i]);
        if (it == statetab.end()) {
            statetab.insert({ prefixes[i],Suffix(prefixes[i],words) });
        }
        else {
            vector<string> suf = it->second;
            for (int i = 0; i < Suffix(prefixes[i], words).size(); i++) {
                suf.push_back(Suffix(prefixes[i], words)[i]);
            }
        }
    }

    return statetab;
}

prefix GenerationPrefix() {
    int index = rand() % statetab.size();
    deque<prefix> keys;
    for (auto it = statetab.begin(); it != statetab.end(); it++) {
        keys.push_back(it->first);

    }
    prefix prefix_new = keys[index];
    return prefix_new;
}

string Generation_pref_suf(prefix prefix_new) {
    string text = "";
    srand(time(NULL));

    vector<string> suffixes;
    for (int i = 0; i < statetab.size(); i++) {
        map<prefix, vector<string>>::iterator it = statetab.find(prefix_new);
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


string Generation() {
    string text = "";
    srand(time(NULL));

    prefix prefix_new = GenerationPrefix();

    for (int i = 0; i < prefix_new.size(); i++) {
        text = text + " " + prefix_new[i];
    }

    for (int j = 0; j < MAXGEN; j++) {
        vector<string> suffixes;
        for (int i = 0; i < statetab.size(); i++) {
            map<prefix, vector<string>>::iterator it = statetab.find(prefix_new);
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
