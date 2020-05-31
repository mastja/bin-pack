/*  Project Name : Bin Packing Problem
    Date: 5/31/2020
    Programmer: Jacob Mast
    Description: The program to executes three common algorithms to solve
                the bin packing problem. A formal definition of the 
                bin packing (BP) problem follows.
                Definition  (Bin  Packing  Problem).  Given  a  list  of 
                objects  and  their  weights,  and  a collection of bins of 
                fixed size, find the smallest number of bins so that all of 
                the objects are assigned to a bin.  The three algorithms used in
                this program to solve the BP problem are First-Fit,
                First-Fit Decreasing, and Best-Fit.  Those algorithms are described
                in the function descriptions below.
                All input from user is received through an input file labeled "bin.txt".
                All output is written to the terminal at runtime.
*/


#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

// function drives the First-Fit Algorithm, also used in First-Fit Decreasing
int firstFit(int weight[], int n, int c);

// function drives the First-Fit Decreasing Algorithm
int firstFitDec(int weight[], int n, int c);

// function drives the Best-Fit Algorithm
int bestFit(int weight[], int n, int c);


int main(){

    // declare variables
    // c is bin capacity and n is number of items, t is the number of test cases
    int c, n, t = 0;
    // dynamically allocate pointer to new array
    int * weight = NULL;
    // input file
    ifstream inFile;

    // open input file and verify the file was opened
    inFile.open("bin.txt");
    if (!inFile.is_open()){
        cout << "Cannot Open file 'data.txt'.  Check to make sure it is in this directory" << endl;
        return 1;
    }

    // Read test cases from input file
    if (!inFile.eof( )){
        inFile >> t;
    }

    // Read test cases from input file
    while (!inFile.eof( )){

        // get data and call functions for each test case
        for(int i = 0; i < t; i++){
            cout << "Test case " << i;
            inFile >> c;
            inFile >> n;
            
            // set weight array size
            weight = new int [n];
    
            // fill weight array with values from input file
            for (int j = 0; j <= n; j++){
                inFile >> weight[j];
            }

            int bestFitSolution = bestFit(weight, n, c);
            cout << " First Fit: " << firstFit(weight, n, c)
                << ", First Fit Decreasing: " << firstFitDec(weight, n, c)
                << ", Best Fit: " << bestFitSolution << endl;

            // clear/delete weight[] array
            delete [] weight;
            weight = NULL; 
        }
    }

    // close the opened file
    inFile.close();

    return 0;

}


/* The firstFit() function uses the First-Fit Heuristic and algorithm to
solve the classic, Bin Packing Problem. A formal definition of 
the bin packing (BP) problem is included in the program description above.

The First-Fit algorithm is explained below:
First  Fit  Heuristic  (BP-FF). 
Place  the  items  in  the  order  in  which they arrive. 
Place the next item into the lowest numbered bin in which it fits.
If it does not fit into any open bin, start a new bin.

passed: array of item weights, n total items, c is bin capacity
returns: int, number of bins required using first fit algorithm 

source citation: https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/
*/

int firstFit(int weight[], int n, int c) { 
    
    // Initialize result to 0 (bin count) 
    int res = 0; 
  
    // Create array to store remaining space in bins 
    // Can be at most n bins (n total items)
    int bin_rem[n]; 
  
    // Place items one by one in bins
    for (int i = 0; i < n; i++) { 

        // Find the first bin that can accommodate weight[i] 
        int j; 
        for (j = 0; j < res; j++) { 

            // if item weight is less than available capacity in current bin
            if (bin_rem[j] >= weight[i]) { 
                bin_rem[j] = bin_rem[j] - weight[i]; 
                break; 
            } 
        } 
  
        // If no bin could accommodate weight[i], store item in a new bin
        // and increase bin count
        if (j == res) { 
            bin_rem[res] = c - weight[i]; 
            res++; 
        } 
    } 

    return res; 
} 


/* The firstFitDec() function uses the First-Fit-Decreasing Heuristic and algorithm to
solve the classic, Bin Packing Problem. A formal definition of 
the bin packing (BP) problem is included in the program description above.

The First-Fit-Decreasing algorithm is explained below:
First  Fit  Decreasing  Heuristic  (BP-FFD).
Sort  the  items  in  decreasing order. 
Place the next item into the lowest numbered bin in which it fits. 
If it does not fit into any open bin, start a new bin.

passed: array of item weights, n total items, c is bin capacity
returns: int, number of bins required using first fit algorithm 

source citation: https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/
*/

int firstFitDec(int weight[], int n, int c) 
{ 
    // Sort item weights in decreasing order 
    sort(weight, weight + n, std::greater<int>()); 
  
    // Call firstFit() using sorted items 
    return firstFit(weight, n, c); 
} 


/* The bestFit() function uses the Best-Fit Heuristic and algorithm to
solve the classic, Bin Packing Problem. A formal definition of 
the bin packing (BP) problem is included in the program description above.

The Best-Fit algorithm is explained below:
Best  Fit  Heuristic  (BP-BF). 
Place  the  items  in  the  order  in  which  they arrive. 
Place the next item into that bin which will leave the least room left over 
after the item is placed in the bin. 
If it does not fit in any bin, start a new bin.

passed: array of item weights, n total items, c is bin capacity
returns: int, number of bins required using first fit algorithm 

source citation: https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/
*/

int bestFit(int weight[], int n, int c){

    // Initialize result to 0 (bin count) 
    int res = 0; 
  
    // Create array to store remaining space in bins 
    // Can be at most n bins (n total items)
    int bin_rem[n]; 
  
    // Place items one by one in bins
    for (int i = 0; i < n; i++) { 

        // Find the first bin that can accommodate weight[i] 
        int j; 
  
        // Initialize minimum space left and index of best bin 
        int min = c + 1, bi = 0;

        // for each bin, if item weight can fit and leftover space is less than current min
        for (j = 0; j < res; j++) { 
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < min) { 

                // record bin index of current best bin with lowest min, leftover space
                bi = j; 

                // record new min
                min = bin_rem[j] - weight[i]; 
            } 
        } 
  
        // If no bin could accommodate weight[i], create a new bin 
        if (min == c + 1) { 
            bin_rem[res] = c - weight[i]; 
            res++; 
        } 
        else // Assign the item to best bin 
            bin_rem[bi] -= weight[i]; 
    } 

    return res; 
} 