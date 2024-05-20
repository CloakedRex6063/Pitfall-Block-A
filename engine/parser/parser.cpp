#include "precomp.h"
#include "parser.h"

int** Parser::ParseCSV(const char* file, int& rowsCount, int& columnsCount)
{
    // Adapted from Lynn's method https://pastebin.com/qiFrGhm6
    // & Max's method https://gist.github.com/mxcop/0f2f59dc7b06e12f485e0bce3585bce9
    int row = 0, column = 0;
    int number = 0;
    bool isNegative = false;

    const string csv = TextFileRead(file);
    FindSize(csv, rowsCount, columnsCount);

    // Create an array from the size found
    int** array = new int* [rowsCount];
    for (int i = 0; i < rowsCount; i++)
    {
        array[i] = new int[columnsCount];
    }


    for (const char i : csv)
    {
        if (i == '-')
        {
            isNegative = true;
        }
        // Check if the current character is a number
        if (i >= '0' && i <= '9')
        {
            // Add the current digit to the previously accumulated number which is multiplied by 10
            // to allow for multi digit numbers
            number = number * 10 + (i - '0');
        }
        // If encountering a comma, use the currently stored number and store it in the tilemap index,
        // and increase the columns
        else if (i == ',')
        {
            array[row][column] = number * (isNegative ? -1 : 1);
            number = 0;
            column++;
            isNegative = false;
        }
        // If encountering a newline, do the same but reset the column and increase the rows,
        // (as we have reached the next line)
        else if (i == '\n')
        {
            array[row][column] = number * (isNegative ? -1 : 1);
            number = 0;
            row++;
            column = 0;
            isNegative = false;
        }
    }
    return array;
}

void Parser::FindSize(const string& text, int& rows, int& columns)
{
    int tempColumns = 0;
    for (const char c : text)
    {
        if (c == ',')
        {
            tempColumns++;
        }
        if (c == '\n')
        {
            tempColumns++;
            rows++;
            columns = tempColumns;
            tempColumns = 0;
        }
    }
}

