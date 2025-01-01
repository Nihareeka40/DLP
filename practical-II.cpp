#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    // Define DFA details
    int numInputSymbols = 3;                       // Number of input symbols
    vector<char> inputSymbols = {'a', 'b', 'c'};   // Input symbols (a, b, c)
    int numStates = 5;                             // Number of states
    vector<string> states = {"q1", "q_a", "q_b", "q_c", "q_reject"};  // State names
    int initialState = 0;                          // Index of initial state (q1)
    vector<int> finalStates = {1, 2, 3};           // Final states (q_a, q_b, q_c)

    // Transition table: Rows represent states, columns represent inputs
    vector<vector<int>> transitionTable = {
        {1, 2, 3},  // q1: a -> q_a, b -> q_b, c -> q_c
        {1, 1, 4},  // q_a: a -> q_a, b -> q_a, c -> q_reject
        {4, 2, 2},  // q_b: a -> q_reject, b -> q_b, c -> q_b
        {3, 4, 3},  // q_c: a -> q_reject, b -> q_reject, c -> q_c
        {4, 4, 4}   // q_reject: Trap state
    };

    // Display DFA details
    cout << "DFA Details:\n";
    cout << "No. of input symbols: " << numInputSymbols << " (";
    for (size_t i = 0; i < inputSymbols.size(); ++i) {
        cout << inputSymbols[i] << (i < inputSymbols.size() - 1 ? ", " : "");
    }
    cout << ")\n";
    cout << "No. of states: " << numStates << " (";
    for (size_t i = 0; i < states.size(); ++i) {
        cout << states[i] << (i < states.size() - 1 ? ", " : "");
    }
    cout << ")\n";
    cout << "Initial state: " << states[initialState] << "\n";
    cout << "No. of final states: " << finalStates.size() << "\n";
    cout << "Final state(s): ";
    for (size_t i = 0; i < finalStates.size(); ++i) {
        cout << states[finalStates[i]] << (i < finalStates.size() - 1 ? ", " : "");
    }
    cout << "\n\n";

    // Display transition functions
    cout << "Transition Functions:\n";
    for (size_t i = 0; i < transitionTable.size(); ++i) {
        for (size_t j = 0; j < inputSymbols.size(); ++j) {
            cout << states[i] << ", " << inputSymbols[j] << " -> " << states[transitionTable[i][j]] << "\n";
        }
    }
    cout << "\n";

    // User input string
    string inputString;
    cout << "Enter a string over {a, b, c}: ";
    cin >> inputString;

    // Process the input string
    int currentState = initialState;
    for (char c : inputString) {
        // Find input index
        int inputIndex = (c == 'a') ? 0 : (c == 'b') ? 1 : (c == 'c') ? 2 : -1;

        // Validate input
        if (inputIndex == -1) {
            cout << "Invalid input! Only {a, b, c} are allowed.\n";
            return 1;
        }

        // Perform state transition
        currentState = transitionTable[currentState][inputIndex];
    }

    // Check if final state is valid
    bool isAccepted = (find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end());
    if (isAccepted) {
        cout << "The string is accepted.\n";
    } else {
        cout << "The string is rejected.\n";
    }

    return 0;
}
