#include <string>

using namespace std;

struct Trie {
    bool isLeaf; //used to signify is a node is a leaf (aka its good)
    Trie* character[128]; //list of chars cus iteration and stuff

    //default constructor
    Trie() {
        isLeaf = false;
        for(int i = 0; i < 128; i++) {
            character[i] = nullptr; // IF WE DONT INITIALIZE ALL THE LETTERS
        }                           // TO NULL THEN THERE WILL BE ISSUES!!!
    }
    void insert(string key) {
        Trie* current = this; //we're pretty current
        for(int i = 0; i < key.length(); i++) { //loop through all letters in key
           //check if a path exists on the character. If it doesn't, make one
           if(current->character[key[i]] == nullptr) {
                current->character[key[i]] = new Trie();
            }
            //advance to next node
            current = current->character[key[i]];
        }
        //if the loop has completed, then we've reached the end of a word
        //therefore, this is a complete word aka a "leaf"
        current->isLeaf = true;
    }


}