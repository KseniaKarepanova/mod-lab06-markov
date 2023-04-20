#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
using namespace std;
typedef deque<string> prefix; // очередь префиксов

string read_file(string filename);
vector<string> split_text(string input_text);
deque<prefix> Prefix(vector<string> words);
vector<string> Suffix(prefix prefixes, vector<string> words);
map<prefix, vector<string>> Prefix_Suffix(vector<string> words);
prefix GenerationPrefix();
string Generation();
string Generation_pref_suf(prefix prefix_new);