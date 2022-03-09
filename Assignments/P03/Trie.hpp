#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief 
 * Trie structure
 * Should be good for text auto-completion, as the subset of items that need
 * to be iterated through gets smaller as the user types
 * Methods:
 * void insert(string) - insert a key into the Trie
 * int children() - returns how many children a trie node has (used for debugging)
 * vector<string> findall - finds all leaf nodes under a trie node that is found by a provided key
 * 
 */
struct Trie {
    bool isLeaf; //used to signify is a node is a leaf (i.e. the end of a word)
    Trie* character[128]; //list of chars. 128 is excessive, most of the words only use 26,
    //                                       but i didn't spend the time optimizing this

    //default constructor
    Trie() {
        isLeaf = false;
        for(int i = 0; i < 128; i++) {
            character[i] = nullptr; // IF WE DONT INITIALIZE ALL THE LETTERS
        }                           // TO NULL THEN THERE WILL BE ISSUES!!!
    }
    /**
     * @brief 
     * insert a key into current trie node
     * @param key 
     */
    void insert(string key) {
        Trie* current = this; //current node this insert function is being called on
        for(int i = 0; i < key.length(); i++) { //loop through all letters in key
           //check if a pointer exists on the character. If it doesn't, make one
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
    /**
     * @brief 
     * returns the number of children a trie node has.
     * used for debugging mainly
     * @return int 
     */
     int children() {
        Trie* current = this;
        int x = 0;
        for(int i = 0; i < 128; i++) {
            if(current->character[i]) {
                x++;
            }
        }
        return x;
    }
    /**
     * @brief returns a vector of strings for every leaf node under the provided trie node.
     * not currently used outside of this class, but could be useful.
     * 
     * @param startpoint 
     * @param vec 
     * @param word 
     * @return vector<string> 
     */
    vector<string> findall(Trie* startpoint, vector<string>& vec, string word)  {
        Trie* current = startpoint;
        if(current->isLeaf) { //if the current node is a leaf
            vec.push_back(word); //then push the word to the provided vector
        } 
            for(int i = 0; i < 128; i++) { //loop through every pointer on the trie 
                if(current->character[i]) { //check if the pointers are valid, if so
                    findall(current->character[i], vec, word + char(i)); //recurse, and add a letter to the word string
                }
            }
        return vec;
    }

    vector<string> findall(string key) {
        vector<string> vec; //create a new vector to be returned later
        bool failed = false; //in case the key isn't even in the trie
        Trie* current = this; //current trie pointer
        for(int i = 0; i < key.length(); i++) { //loop through the letters in the key
            if(current->character[key[i]]) { //check if the trie contains pointers to those letters
                current = current->character[key[i]]; //traverse down to the end of the key 
            } else {
                failed = true; //the key does not exist in this trie, nothing can be returned
            }
        }
        if(!failed) {
            vec = findall(current, vec, key); //find all leaf nodes under the trie that we traversed to
        } 
        return vec;
    }


};