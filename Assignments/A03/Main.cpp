/*****************************************************************************
*
*  Author:           Dylan Miles
*  Email:            dylanbmiles@gmail.com
*  Label:            A03
*  Title:            Commenting Code
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Linked list class, commenting code practice
*
*  Usage:
*     ./Main
*
*  Files:            Main.cpp
*****************************************************************************/
#include <iostream>

using namespace std;

int A[100]; //Array of 100 integers

/**
 * @brief 
 * Data structure, stores int and node pointer. Made for linked list
 * Has a default constructor, Node(), and an overloaded one to provide an int
 * node(int n)
 * 
 */
struct Node {
    int x;
    //Node pointer, made to be used for the linked list
    Node *next;
    //Default constructor
    Node() {
        x = -1;
        next = NULL;
    }
    //Overload constructor, populate data value with n
    Node(int n) {
        x = n;
        next = NULL;
    }
};
/**
 * Descrpition:
 * List class, made of nodes that are linked to each other
 * 
 * Contains public methods to:
 * push a value to the list
 * insert a value to the list
 * print th etail
 * print the entire list
 * pop from the list
 * overloaded operators for +, [], <<
 * 
 */
class List {
private:
    Node *Head; //start of list
    Node *Tail; // end of list
    int Size; //number of nodes in the list

public:
//Creates a new empty list object
    List() {
        Head = Tail = NULL;
        Size = 0;
    }
//Appends an int to the list
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
// prepends an int to the list
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }
//Prints the last int in the list to cout
    void PrintTail() {
        cout << Tail->x << endl;
    }
//returns a string containing the entire contents of the array 
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }
    //TODO: This method is not implemented
    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }
//appends one list to another, returns a new list
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }
//Writes the contents of the list to ostream using previously
//defined Print() function.
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1; //empty list l1
    List L2; //empty list l2

//Push numbers 0-24 to L1
    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }
//push 50-99 to L2
    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail(); //prints tail of l1
    L2.PrintTail(); // prints tail of l2

    List L3 = L1 + L2; // Creates new list L3, comprised of L1 and L2 appended together
    cout << L3 << endl; // print contents of L3

    cout << L3[5] << endl; //prints the 5th index item in l3 (3rd object)
    return 0;
}