/**
 * Make sure before running, you copy necessary .hpp files
 * into your project folder so they can be found.
 * 
 * Trying to run this code as is will fail since the .hpp
 * files our in the resources folder. 
 * 
 */
#include "Trie.hpp"
#include <iostream>
#include "JsonFacade.hpp"       // need to grab a copy from resources folder
#include <time.h>
#include <chrono> 
#include "timer.hpp"            // need to grab a copy from resources folder

using namespace std;

void loadTrie(Trie& trie, vector<string> keys) {
    int i = 0;
    for(string s : keys) {
        trie.insert(s);
        i++;
    }
    cout << "size: " << i << endl;
}

int main(){
    cout << ((int) 'z') << endl;
    Timer T;
    T.Start();
    JsonFacade J("dict_w_defs.json");   // create instance of json class
    T.End(); 
    double s = T.Seconds();
    long m = T.MilliSeconds();

    cout <<s << " seconds" <<endl;
    cout <<m << " milli" <<endl;
    int index = 0;                      // 
    string key;                         // key variable to access json object

    vector<string> keys = J.getKeys();
    Trie werg;
    loadTrie(werg, keys);
    cout << werg.children();
    // cout<<keys.size()<<endl;
    // index = rand() % keys.size();
    // key = J.getKey(index);

    // cout<<key<<" = "<<J.getValue(key)<<endl;
}