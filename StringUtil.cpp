#include <iostream>
#include <cwchar>
#include <cstdlib>

#include "StringUtil.h"

#pragma warning(disable:4996)

char* convertWideToNarrow(const wchar_t* wcharArray) {
    // Determine the size needed for the narrow character array
    size_t size = wcstombs(NULL, wcharArray, 0);
    if (size == static_cast<size_t>(-1)) {
        // Handle error, wcstombs failed
        std::cerr << "Conversion error" << std::endl;
        return nullptr;
    }

    // Allocate memory for the narrow character array
    char* charArray = new char[size + 1];

    // Convert wide character array to narrow character array
    if (wcstombs(charArray, wcharArray, size + 1) == static_cast<size_t>(-1)) {
        // Handle error, conversion failed
        std::cerr << "Conversion error" << std::endl;
        delete[] charArray; // Free allocated memory before returning
        return nullptr;
    }

    // Null-terminate the narrow character array
    charArray[size] = '\0';

    return charArray;
}