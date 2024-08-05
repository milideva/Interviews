#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// Helper function to perform arithmetic operations
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// Helper function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to evaluate the expression
int evaluateExpression(string expression) {
    stack<int> values;  // Stack to store integers
    stack<char> ops;    // Stack to store operators

    for (int i = 0; i < expression.length(); i++) {
        // Skip whitespace
        if (isspace(expression[i])) continue;

        // If the current character is a number, parse it
        if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;  // Adjust for the for loop's increment
        }
        // If the current character is an opening bracket, push it to 'ops'
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // If the current character is a closing bracket, solve the entire bracket
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOperation(val1, val2, op));
            }
            // Pop the opening bracket from stack
            if (!ops.empty()) ops.pop();
        }
        // If the current character is an operator
        else {
            // While the top of 'ops' has the same or greater precedence to current token,
            // which is an operator, apply the operator on top of 'ops' to the top two elements in values stack
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOperation(val1, val2, op));
            }
            // Push current token to 'ops'.
            ops.push(expression[i]);
        }
    }

    // Apply remaining ops to remaining values
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOperation(val1, val2, op));
    }

    // The top of 'values' contains the result
    return values.top();
}

void test(void) {
    int passed = 0, failed = 0;

    // Test case 1
    string expression1 = "125 - 33 / 3 + 4 * 3";
    int expected1 = 128;
    int result1 = evaluateExpression(expression1);
    cout << "Test case 1: expected = " << expected1 << ", got = " << result1;
    if (result1 == expected1) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 2
    string expression2 = "45 + 3 * 30 / (9 - 3) + ((5 - 1) - 3)";
    int expected2 = 50;
    int result2 = evaluateExpression(expression2);
    cout << "Test case 2: expected = " << expected2 << ", got = " << result2;
    if (result2 == expected2) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 3
    string expression3 = "(10 + 2) * 6";
    int expected3 = 72;
    int result3 = evaluateExpression(expression3);
    cout << "Test case 3: expected = " << expected3 << ", got = " << result3;
    if (result3 == expected3) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 4
    string expression4 = "100 * (2 + 12)";
    int expected4 = 1400;
    int result4 = evaluateExpression(expression4);
    cout << "Test case 4: expected = " << expected4 << ", got = " << result4;
    if (result4 == expected4) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 5
    string expression5 = "100 * (2 + 12) / 14";
    int expected5 = 100;
    int result5 = evaluateExpression(expression5);
    cout << "Test case 5: expected = " << expected5 << ", got = " << result5;
    if (result5 == expected5) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 6
    string expression6 = "3 + (2 * 5) - 9 / 3";
    int expected6 = 10;
    int result6 = evaluateExpression(expression6);
    cout << "Test case 6: expected = " << expected6 << ", got = " << result6;
    if (result6 == expected6) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 7
    string expression7 = "10 - (3 + 2) * (2 + 1)";
    int expected7 = -5;
    int result7 = evaluateExpression(expression7);
    cout << "Test case 7: expected = " << expected7 << ", got = " << result7;
    if (result7 == expected7) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 8
    string expression8 = "((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1))";
    int expected8 = 5;
    int result8 = evaluateExpression(expression8);
    cout << "Test case 8: expected = " << expected8 << ", got = " << result8;
    if (result8 == expected8) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Summary
    cout << "Summary: " << passed << " passed, " << failed << " failed." << endl;
}

int main() {
    test();
    return 0;
}
