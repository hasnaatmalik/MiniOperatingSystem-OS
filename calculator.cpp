#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
using namespace std;
int main() {
    cout << "\e[1;32m\n";
    char operation;
    double num1, num2, result;

    cout << "Enter an operation (+, -, *, /): ";
    cin >> operation;
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    switch(operation) {
        case '+':
            result = num1 + num2;
            cout << "Result: " << result << endl;
            break;
        case '-':
            result = num1 - num2;
            cout << "Result: " << result << endl;
            break;
        case '*':
            result = num1 * num2;
            cout << "Result: " << result << endl;
            break;
        case '/':
            if(num2 != 0) {
                result = num1 / num2;
                cout << "Result: " << result << endl;
            } else {
                cout << "Error! Division by zero is not allowed." << endl;
            }
            break;
        default:
            cout << "Invalid operation!" << endl;
    }
    sleep(4);
    return 0;
}
