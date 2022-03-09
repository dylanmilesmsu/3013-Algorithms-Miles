///////////////////////////////////////////////////////////////////////////////
//
// Author:           Dylan Miles    
// Email:            dylanbmiles@gmail.com
// Label:            P02
// Title:            Program 2 - Processing in Linear Time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       This project is about loading a singly linked list with dictionary words, then timing how it takes to look them up.
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "JsonFacade.hpp"
#include "Trie.hpp"
#include <iostream>
#include <fstream>
#include "timer.hpp"
#include "mygetch.hpp"
#include "termcolor.hpp"
using namespace std;

/**
 * @brief 
 *  Converts a string of text to lowercase
 * @param s 
 */
void toLower(string &s) {
    for(char x : s) {
        x = tolower(x);
    }
}
/**
 * @brief 
 * filles a Trie by reference with the data from file 'filename'.
 * @param list 
 * @param filename 
 */
void loadTrie(Trie& trie, string name) {
    JsonFacade J(name);   // create instance of json class
    vector<string> keys = J.getKeys();
    int i = 0;
    for(string s : keys) {
        trie.insert(s);
        i++;
    }
    cout << "size: " << i << endl;
}


int main() {
    //initialize things
    Trie trie;
    string s = "dict_w_defs.json";
    Timer T;

    //Benchmark filling the list
    T.Start();
    loadTrie(trie, s);
    T.End();
    //output
    cout << T.Seconds() << "s to read in \'" << s << "\'!\n";

    char g;
    string searchword = "";
    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;
    //updates every time a key is pressed.
    while((g = getch()) != 'Z') {
        if((int) g == 127) { //if the user types a backspace
            if(searchword.size() > 0) {
                searchword = searchword.substr(0, searchword.size() - 1); //remove a letter from the end of our searchword
                continue; //optimization bro
            }
        }
            //check if the user inputted something that is not alphanumeric
            if(!isalpha(g)) {
                cout << "You tried typing something that is not a letter.\n";
                continue;
            }
            //everything past here should be valid but gotta convert to lowercase
            if ((int)g < 97) {
                g += 32;
            }
            searchword += g; // append char to word
            T.Start(); // begin benchmarking
            //finds matching words and adds them to a vector of strings
            // vector<string> words = list.findWords(searchword); 
            vector<string> words = trie.findall(searchword); 
            int index;
            int k = 0;
            //If the user didn't input a space
            if ((int)g != 32) {
                //end the benchmark
                T.End();
                //output the results
                cout << termcolor::red << searchword << termcolor::reset << endl;
                cout << words.size() << " words found in " << T.Seconds() << "s!" << endl;
                //loop through the list of results
                for (int i = 0; i < words.size(); i++) {
                    //limit the output to 10
                    if(k < 10) {
                        // find the substring in the word
                        index = words[i].find(searchword);
                        // only output if the found string is at the start of the word
                        if (index == 0) {
                            //print one letter at a time turning on red or green
                            // depending on if the matching subtring is being printed
                            for (int j = 0; j < words[i].size(); j++) {
                                // if we are printing the substring turn it red
                                if (j >= index && j <= index + searchword.size() - 1) {
                                    cout << termcolor::red;
                                } else {
                                    cout << termcolor::green;
                                }
                                cout << words[i][j];
                            }
                            cout << termcolor::green;
                            cout << " ";
                            k++;
                        }
                    }
                }
                    cout << termcolor::reset << endl
                        << endl;
                    }


    }
    return 0;
}