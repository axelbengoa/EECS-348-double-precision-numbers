#include <iostream>
#include <iomanip> // For formatting
#include <string>
using namespace std;

// input extraction
double extractNumeric(const string& str) {
    if (str.empty() || str.length() > 20) {
        return -999999.99; // Invalid length
    }

    int signCount = 0, decimalCount = 0;
    bool hasDigits = false; 

    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (ch == '+' || ch == '-') {
            // one sign at the beginning
            if (i != 0 || signCount > 0) {
                return -999999.99;
            }
            signCount++;
        } else if (ch == '.') {
            // One decimal point allowed
            decimalCount++;
            if (decimalCount > 1) {
                return -999999.99;
            }
        } else if (isdigit(ch)) {
            hasDigits = true; // Have a valid digit
        } else {
            // Invalid character
            return -999999.99;
        }
    }

    // At least one digit in the input
    if (!hasDigits) {
        return -999999.99;
    }

    // Valid string to a double manually
    double result = 0.0;
    double fraction = 1.0;
    bool isNegative = (str[0] == '-');
    bool isFraction = false;

    for (char ch : str) {
        if (ch == '+' || ch == '-') {
            continue; // Skip the sign
        }
        if (ch == '.') {
            isFraction = true; // Switch to parsing the fractional part
            continue;
        }

        if (isdigit(ch)) {
            if (isFraction) {
                // Parsing the fractional part
                fraction /= 10;
                result += (ch - '0') * fraction;
            } else {
                // Parsing the integer part
                result = result * 10 + (ch - '0');
            }
        }
    }

    // Apply the negative sign
    if (isNegative) {
        result = -result;
    }

    return result;
}

int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
