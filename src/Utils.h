#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <limits>
using namespace std;

// Define _CRT_SECURE_NO_WARNINGS for MinGW compatibility
#define _CRT_SECURE_NO_WARNINGS

namespace Utils
{
    int getValidatedInt(const char *prompt, int min, int max);
    void getValidatedString(const char *prompt, char *buffer, int size);
    bool isValidPhone(const char *phone);
    bool isValidGender(char gender);
    void printSeparator(char ch = '=', int length = 80);
    void printHeader(const char *title);
    void clearInputBuffer();
    void clearScreen();
    void pauseScreen();
    // Safe string copy function for older GCC
    void safeStrCopy(char *dest, const char *src, size_t destSize);
}