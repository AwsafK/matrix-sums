/*
Program Name: Assignment 1 Matrix
Date due: 01/26/2024
Author: Awsaf Ahmad Kabir
Module Purpose:
This program reads matrices from an input file, determines whether or not it is vertically additive symmetric, and then sorts and outputs the rows of each matrix in ascending order 
*/

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const unsigned MAX_MATRIX_SIZE = 20;
const unsigned WIDTH_DISPLAY = 12;

bool    readMatrixFromFile(int[][MAX_MATRIX_SIZE], unsigned&, unsigned&, ifstream&);
void         displayMatrix(int[][MAX_MATRIX_SIZE], unsigned, unsigned);
void displayCalcMatrixSums(int[][MAX_MATRIX_SIZE], unsigned, unsigned, int[MAX_MATRIX_SIZE]);
void   symmetryCheckMatrix(int[], unsigned, unsigned);
void        sortMatrixRows(int[][MAX_MATRIX_SIZE], unsigned, unsigned);


int main() {
    unsigned height = 0,
             width = 0;
    int      matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE],
             colSums[MAX_MATRIX_SIZE];
    string   INPUT_FILE_NAME = "matrixes.txt";
    ifstream inputFileStreamObj(INPUT_FILE_NAME);

    if (inputFileStreamObj.fail()) {
        cout << "File " << INPUT_FILE_NAME << " could not be opened !" << endl;
        cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
        exit(EXIT_FAILURE);
    }

    do {

        if (readMatrixFromFile(matrix, height, width, inputFileStreamObj))
            break;  //If true is returned from readMatrixFromFile function, then it breaks out of this loop, and exits the program.

        cout << fixed << "Input:" << endl;
        displayMatrix(matrix, height, width);
        displayCalcMatrixSums(matrix, height, width, colSums);
        symmetryCheckMatrix(colSums, width, height);
        sortMatrixRows(matrix, width, height);
        cout << "Sorted:" << endl;
        displayMatrix(matrix, height, width);

        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();

    } while (true);  

    cout << "Program Done" << endl;

    exit(EXIT_SUCCESS);
}


bool readMatrixFromFile(int matrix[][MAX_MATRIX_SIZE], unsigned& height, unsigned& width, ifstream& inputFileStreamObj) {
    
    string lineCheck;
    char charCheck;

    if (inputFileStreamObj)  //If the file is open, it returns false, meaning there is more to read in the file
    {
        inputFileStreamObj >> height >> width;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                inputFileStreamObj >> matrix[i][j];
            }
        }
        inputFileStreamObj.ignore();
        return false;
    }
    
    //Once there is nothing else left to read in the file, it returns true which means the program will exit   

    return(true);
}


void displayMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width) {

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << setw(10) << right << matrix[i][j];
        }
        cout << endl;
    }

}


void displayCalcMatrixSums(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width, int colSums[MAX_MATRIX_SIZE]) {

    
    for (int i = 0; i < width; i++)  
    {
        int sum = 0;
        for (int j = 0; j < height; j++)  //Loops through each colum, and adds up the values
        {
            sum += matrix[j][i];
            colSums[i] = sum;
        }
        
    }

    cout << endl << "Sums:" << endl;
    for (int i = 0; i < width; i++) {
        cout << setw(10) << right << colSums[i];
    }
    cout << endl;

}


void symmetryCheckMatrix(int colSums[], unsigned width, unsigned height) {

    bool isSymmetric = true;
    for (int i = 0, j = width - 1; i < j ; i++, j--)
    {
        if(colSums[i] != colSums[j])  //This goes through the entire array, and checks for symmetry. If any one is not symmetric, then it changes to false
        {
            isSymmetric = false;
            break;
        }
    }
    if (isSymmetric == true)
    {
        cout << endl << "Vertical additive symmetry : Yes" << endl;
    }
    else
    {
        cout << endl << "Vertical additive symmetry : No" << endl;
    }

}

void sortMatrixRows(int matrix[][MAX_MATRIX_SIZE], unsigned width, unsigned height) {
    int tempHolder = 0;
    for (int i = 0; i < height; i++)  //Iterating through the rows
    {
        for (int j = 0; j < width - 1; j++)  //Using Bubble sort this is the lower bound
        {
            for (int k = 0; k < width - j - 1; k++)  //Using Bubble sort this is the upper bound
            {
                if (matrix[i][k] > matrix[i][k + 1])
                {
                    tempHolder = matrix[i][k];
                    matrix[i][k] = matrix[i][k + 1];
                    matrix[i][k + 1] = tempHolder;
                }
            }
        }
    }
}
