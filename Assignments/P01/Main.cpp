
///////////////////////////////////////////////////////////////////////////////
//
// Author:           Dylan Miles    
// Email:            dylanbmiles@gmail.com
// Label:            P01
// Title:            Program 1 - Array Based Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "mygetch.hpp"

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
private:
    int *A;   // pointer to array of int's
    int size; // current max stack size
    int top;  // top of stack
    double threshHold = .85;

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    int maxSize = 0;
    int resizes = 0;
    int commandsProcessed = 0;
    double growThresh = 1.0;
    double shrinkThresh = 0.15;
    double growMultiplier = 2.0;
    double shrinkMultiplier = 0.5;

/**
 * Int finalsize
 * essentially a getter for private int size
 * no params
 */
    int finalSize() {
        return size;
    }
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
    }

/**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - int  grow threshold shrink threshold grow multiplier shrink multiplier
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int _growThresh, int _shrinkThresh, int _growMultiplier, int _shrinkMultiplier) {
        size = 10;
        A = new int[size];
        top = -1;
        growThresh = _growThresh;
        shrinkThresh = _shrinkThresh;
        growMultiplier = _growMultiplier;
        shrinkMultiplier = _shrinkMultiplier;
    }

/**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
    }
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - int size grow threshold shrink threshold grow multiplier shrink multiplier
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s, int _growThresh, int _shrinkThresh, int _growMultiplier, int _shrinkMultiplier) {
        size = 10;
        A = new int[size];
        top = -1;
        growThresh = _growThresh;
        shrinkThresh = _shrinkThresh;
        growMultiplier = _growMultiplier;
        shrinkMultiplier = _shrinkMultiplier;
    }

/**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full() {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
        if (!Empty()) {
            checkResize();
            return A[top--];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print() {
        for (int i = 0; i <= top; i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x) {
        if (Full()) {
            ContainerGrow();
        }
        if (!Full()) {
            A[++top] = x;

            checkResize();
            return true;
        }
    }

    /**
  * Public void: ContainerGrow

  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerGrow() {
        int newSize = size * growMultiplier;    // double size of original
        if(newSize > maxSize) {
            maxSize = newSize;
        }
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }
/**
 * 
 * Calculates the ratio of items in the list to the size
 * then determins if that ratio is in thresholds to grow or shrink
 * returns nothing, has no params
 * 
 */
    void checkResize() {
        double ratio = (((double)top)/size);
        if(ratio >= growThresh) {
            ContainerGrow();
            resizes++;
        }
        if(size > 10 && ratio <= shrinkThresh) {
            ContainerShrink();
            resizes++;
        }
    }

    /**
  * Public void: ContainerShrink

  * 
  * Description:
  *      shrinks the container for the stack by halving
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerShrink() {
        int newSize = size * shrinkMultiplier;    // double size of original
        if(newSize < 10)
            newSize = 10;
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char *argv[]) {
    ArrayStack stack;
    //default input file
    string inputFile = "test_nums.dat";
    //if there are 5 arguments, use default input file, fill configuration
   if (argc == 5) {
        stack.growThresh = atof(argv[1]);
        stack.shrinkThresh = atof(argv[2]);
        stack.growMultiplier = atof(argv[3]);
        stack.shrinkMultiplier = atof(argv[4]);
    } 
    //if there are six, fill configuration and define input file
    if (argc == 6) {
        stack.growThresh = atof(argv[1]);
        stack.shrinkThresh = atof(argv[2]);
        stack.growMultiplier = atof(argv[3]);
        stack.shrinkMultiplier = atof(argv[4]);
        inputFile = argv[5];
    }
    //open input file
    ifstream infile;
    infile.open(inputFile);

    //define int num, which will be the number read in from input file
    int num;
    while(infile >> num) {
        //increment the number of commands processed
        stack.commandsProcessed++;
        //if the number is even
        if(num % 2 == 0) {
            //push it to the arraystack
            stack.Push(num);
        } else {
            //otherwise, pop from the array stack
            stack.Pop();
        }
    }
    cout << "##################################################################\n";
    cout << "   Assignment 4 - Resizing the Satck\n   CMPS 3013\n   Dylan Miles\n\n";
    cout << "   Config Params:\n";
    cout << "     Full Threshold: " << stack.growThresh << endl;
    cout << "     Shrink Threshold: " << stack.shrinkThresh << endl;
    cout << "     Grow Ratio: " << stack.growMultiplier << endl;
    cout << "     Shrink Ratio: " << stack.shrinkMultiplier << endl << endl;

    cout << "   Processed commands: " << stack.commandsProcessed << endl << endl;

    cout << "   Max Stack Size: " << stack.maxSize << endl;
    cout << "   End Stack Size: " << stack.finalSize() << endl;
    cout << "   Stack Resized: " << stack.resizes << " times" << endl;
    cout << "##################################################################\n";
    return 0;
}
