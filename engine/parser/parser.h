#pragma once

class Parser
{
public:
    /**
     * \brief Parse the csv file into a 2 dimensional array
     * \param file The csv file to parse
     * \param columnsCount The number of columns in the csv file
     * \param rowsCount The number of rows in the csv file
     * \return a 2 dimensional array from the file
     */
    static int** ParseCSV(const char* file, int& rowsCount, int& columnsCount);

    /**
     * \brief Find the size of the csv file in columns and rows
     * \param text The text to derive the size from
     * \param rows The number of rows in the text
     * \param columns The number of columns in the text
     */
    static void FindSize(const string& text, int& rows, int& columns);
};
