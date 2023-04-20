#include "textgen.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    string text = read_file("file1.txt");
    vector<string> words = split_text(text);
    deque<prefix> prefixes = Prefix(words);
    Prefix_Suffix(words);
    string new_text = Generation();

    cout << new_text;

}