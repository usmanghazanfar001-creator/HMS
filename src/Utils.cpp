#include "Utils.h"
#include <cstdlib>
namespace Utils
{
    void safeStrCopy(char *dest, const char *src, size_t destSize)
    {
        strncpy(dest, src, destSize - 1);
        dest[destSize - 1] = '\0';
    }

    int getValidatedInt(const char *prompt, int min, int max)
    {
        int value;
        bool valid = false;

        do
        {
            cout << prompt;
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                clearInputBuffer();
                cout << "Invalid input. Please enter a number.\n";
            }
            else if (value < min || value > max)
            {
                cout << "Value must be between " << min << " and " << max << ".\n";
            }
            else
            {
                valid = true;
            }
        } while (!valid);

        clearInputBuffer();
        return value;
    }

    void getValidatedString(const char *prompt, char *buffer, int size)
    {
        do
        {
            cout << prompt;
            cin.getline(buffer, size);

            if (strlen(buffer) == 0)
            {
                cout << "Input cannot be empty. Please try again.\n";
            }
        } while (strlen(buffer) == 0);
    }

    bool isValidPhone(const char *phone)
    {
        int len = strlen(phone);
        if (len < 10 || len > 15)
            return false;

        for (int i = 0; i < len; i++)
        {
            if (!isdigit(phone[i]))
                return false;
        }
        return true;
    }

    bool isValidGender(char gender)
    {
        gender = toupper(gender);
        return (gender == 'M' || gender == 'F');
    }

    void printSeparator(char ch, int length)
    {
        for (int i = 0; i < length; i++)
        {
            cout << ch;
        }
        cout << endl;
    }

    void printHeader(const char *title)
    {
        printSeparator('=', 80);
        cout << setw(40) << title << endl;
        printSeparator('=', 80);
    }

    void clearInputBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void clearScreen()
    {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }
    void pauseScreen()
    {
        clearInputBuffer();
        cout << "\nPress Enter to continue...";
        cin.get();
    }

}