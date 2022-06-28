#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
using namespace std;
int main(int argc, char *argv[]) {
  vector<string> tokens;
    set <string> unique;
    string next_line;
    string filename = argv[1];
    ifstream in(filename);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) {      
                if (isalpha(c)) {
                    nopunct +=c;       
                }
            }
	          tokens.push_back(nopunct);
		        unique.insert(nopunct);
	    }
    }
    cout << "Number of words "<<tokens.size()<<endl;
    cout << "Number of unique words "<<unique.size()<<endl;
    ofstream setfile(filename+"_set.txt");
    for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) 
    {
        setfile << ' ' << *it;
    }
    cout << endl;

    const int M = 2;
    map<list<string>, vector<string>> wordmap;
    list<string> state; 
    for (int i = 0; i < M; i++) {
      state.push_back("");
    }

    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
      wordmap[state].push_back(*it);
      state.push_back(*it);
      state.pop_front();
    }

    srand(time(NULL));

    state.clear();
    for (int i = 0; i < M; i++) {
      state.push_back("");
    }
    for (int i = 0; i < 100; i++) {
      int ind = rand() % wordmap[state].size();
      cout << wordmap[state][ind] << " "; 
      state.push_back(wordmap[state][ind]);
      state.pop_front(); 
    }
}