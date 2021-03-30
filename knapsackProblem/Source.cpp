// ****************************************************************************** //
//  AUTHOR: Liam Guenther (lguenthe@uccs.edu)
//  FOR: CS4720, extra credit assignment
//  
//  WHAT:   This program solves the "knapsack problem" from the book "Algorithms Illuminated Part3"
//          This file contains the 'main' function. Program execution begins and ends there.
//          Inputs are hard-coded. Outputs are written to terminal.
//

#include <iostream>
#include <vector>

#define MAX(x, y) ((x)>=(y)?(x):(y))


using namespace std;

int main()
{
    //inputs (hard coded for simplicity)
    int value[] = { 1, 2, 3, 4, 5 };
    int size[] = { 1, 3, 2, 5, 4 };    //item i has value = size[i-1], and value = value[i-1]
    int capacity = 9;
    int items = 5;

    //allocate table
    vector<vector<int>> table(items + 1, vector<int>(capacity + 1));    // table[col][row]


    //========================== Solve Knapsack Problem =================== //
    //add base case (redundant b/c std::vector initializes to 0. Only added for completeness)
    for (int c = 0; c != table[0].size(); c++) {
        table[0][c] = 0;    //0th column must be all 0
    }

    //Algorithm from "Algorithms Illuminated Part3" pg 128
    for (int i = 1; i != table.size(); i++) {
        for (int c = 0; c != table[i].size(); c++) {
            if (size[i - 1] > c) {  //if item i cannot fit at table[i][c]
                table[i][c] = table[i - 1][c];  //put optimal solution from prior item's column
            }
            else {
                table[i][c] = MAX(table[i - 1][c], table[i - 1][c - size[i - 1]] + value[i - 1]); //max(prior item's solution, prior item's solution at row[capacity - item's size] + item's size)
            }
        }
    }

    //print table
    cout << "Knapsack Table" << endl << "(Columns: increasing from left. Rows: increasing from bottom)" << endl;
    for (int row = table[0].size() - 1; row >= 0; row--) {
        for (int col = 0; col != table.size(); col++) {
            cout << table[col][row] << " ";
        }
        cout << endl;
    }


    // ======================= Reconstruct Solution ======================= //
    //initialize variables
    vector<int> solutionItems;
    int remainingCapacity = capacity;

    //Algorithm from "Algorithms Illuminated Part3" pg 131
    for (int i = table.size() - 1; i >= 1; i--) {
        if (size[i - 1] <= remainingCapacity && table[i - 1][remainingCapacity - size[i - 1]] + value[i - 1] >= table[i - 1][remainingCapacity]) {
            solutionItems.push_back(i); //item i must have been in the solution
            remainingCapacity -= size[i - 1];   //account for space i takes up
        }
    }

    //print items in the solution
    cout << endl << "Items in solution: ";
    for (int i = 0; i != solutionItems.size(); i++) {
        cout << "Item #" << solutionItems[i] << ", ";
    }
    cout << endl;


    return 0;
}
