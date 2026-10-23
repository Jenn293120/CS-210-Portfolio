
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

// CS 210 Project Three - Corner Grocer
// Grocery Item Tracking Program
// Student: Jenny Thomas

// This class manages grocery items and purchase counts.
class GroceryTracker {

private:
    // Store each grocery item and how often it appears.
    map<string, int> itemFrequency;

public:

    // Read the grocery items from the input file.
    bool LoadData(const string& filename) {
        ifstream inputFile(filename);
        string item;

        // Check that the file opened successfully.
        if (!inputFile.is_open()) {
            cout << "Error: Unable to open "
                << filename << endl;
            return false;
        }

        itemFrequency.clear();

        // Count each item purchased.
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
        return true;
    }

    // Create a backup file automatically.
    bool SaveData() const {
        ofstream outputFile("frequency.dat");

        if (!outputFile.is_open()) {
            cout << "Error creating frequency.dat"
                << endl;
            return false;
        }

        // Write each item and its frequency.
        for (const auto& item : itemFrequency) {
            outputFile << item.first << " "
                << item.second << endl;
        }

        outputFile.close();

        if (!outputFile) {
            cout << "Error writing frequency.dat"
                << endl;
            return false;
        }

        return true;
    }

    // Menu Option 1: Search for one grocery item.
    void SearchItem() const {
        string item;

        cout << "\nEnter the item to search for: ";
        cin >> item;

        auto found = itemFrequency.find(item);

        if (found != itemFrequency.end()) {
            cout << item << " was purchased "
                << found->second << " times."
                << endl;
        }
        else {
            cout << item << " was purchased 0 times."
                << endl;
        }
    }

    // Menu Option 2: Display all grocery frequencies.
    void DisplayFrequencies() const {
        cout << "\n================================\n";
        cout << "    Grocery Purchase Frequencies\n";
        cout << "================================\n";

        for (const auto& item : itemFrequency) {
            cout << item.first << " "
                << item.second << endl;
        }

        cout << "================================\n";
    }

    // Menu Option 3: Display a histogram.
    void DisplayHistogram() const {
        cout << "\n================================\n";
        cout << "     Grocery Purchase Histogram\n";
        cout << "================================\n";

        for (const auto& item : itemFrequency) {
            cout << item.first << " ";

            // Print one star for each purchase.
            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }

            cout << endl;
        }

        cout << "================================\n";
    }
};

// Main function controls the program menu.
int main() {

    GroceryTracker tracker;
    int choice = 0;

    // Read the provided grocery purchase file.
    if (!tracker.LoadData(
        "CS210_Project_Three_Input_File.txt")) {
        return 1;
    }

    // Automatically create the backup file.
    if (!tracker.SaveData()) {
        return 1;
    }

    // Display the menu until the user chooses Exit.
    do {
        cout << "\n================================\n";
        cout << "        CORNER GROCER\n";
        cout << "     Grocery Tracking Program\n";
        cout << "================================\n";

        cout << "1. Search for a grocery item\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display grocery histogram\n";
        cout << "4. Exit program\n";

        cout << "================================\n";
        cout << "Enter your choice (1-4): ";

        // Check for invalid input.
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Enter a number "
                << "between 1 and 4.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n');

            continue;
        }

        // Process the selected menu option.
        switch (choice) {

        case 1:
            tracker.SearchItem();
            break;

        case 2:
            tracker.DisplayFrequencies();
            break;

        case 3:
            tracker.DisplayHistogram();
            break;

        case 4:
            cout << "\nThank you for using "
                << "Corner Grocer!" << endl;
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "\nInvalid choice. "
                << "Please enter 1, 2, 3, or 4."
                << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}

