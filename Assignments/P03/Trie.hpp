#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Trie {
    bool isLeaf; //used to signify is a node is a leaf (aka its good)
    Trie* character[128]; //list of chars cus iteration and stuff, but the characters are actually trie pointers.

    //default constructor
    Trie() {
        isLeaf = false;
        for(int i = 65; i < 128; i++) {
            character[i] = nullptr; // IF WE DONT INITIALIZE ALL THE LETTERS
        }                           // TO NULL THEN THERE WILL BE ISSUES!!!
    }
    void insert(string key) {
        Trie* current = this; //we're pretty current
        for(int i = 0; i < key.length(); i++) { //loop through all letters in key
           //check if a path exists on the character. If it doesn't, make one
           if(current->character[key[i]] == nullptr) {
               cout << key[i] << " SHOULD BE NON NULL" << endl;
                current->character[key[i]] = new Trie();
            }
            //advance to next node
            current = current->character[key[i]];
        }
        //if the loop has completed, then we've reached the end of a word
        //therefore, this is a complete word aka a "leaf"
        current->isLeaf = true;
    }
    string trieToString() {
        string werg = "";
        for(int i = 0; i < 128; i++) {
            if(this->character[i]) {
                werg = werg + char(i);
            }
        }
        return werg;
    }
     int children() {
        Trie* current = this;
        int i = 0;
        for(int i = 65; i < 128; i++) {
            if(current->character[i]) {
                i++;
            }
        }
        return i;
    }
    vector<Trie> findall(Trie* startpoint, vector<Trie> vec)  {
        Trie* current = startpoint;
        if(current->isLeaf) {
            vec.push_back(*current);
        } 
            for(int i = 0; i < 128; i++) {
                if(current->character[i]) {
                    findall(current->character[i], vec);
                }
            }
        return vec;
    }

    bool find(string key) {
         // return false if Trie is empty
    if (this == nullptr) {
        return false;
    }
 
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
    }

    vector<Trie> findall(string key) {
        vector<Trie> vec;
        bool failed = false;
        Trie* current = this;
        for(int i = 0; i < key.length(); i++) {
            if(current->character[key[i]]) {
                current = current->character[key[i]];
            } else {
                failed = true;
            }
        }
        if(!failed) {
            vec = findall(current, vec);
            return vec;
        }
    }


};