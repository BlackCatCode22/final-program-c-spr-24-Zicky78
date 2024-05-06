#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Contact {
private:
    string name;
    string phoneNumber;
    string email;

public:
    Contact(string name, string phoneNumber, string email)
    : name(move(name)), phoneNumber(move(phoneNumber)), email(move(email)) {}

    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    const string& getPhoneNumber() const {
        return phoneNumber;
    }

    void setPhoneNumber(const string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }

    const string& getEmail() const {
        return email;
    }

    void setEmail(const string& newEmail) {
        email = newEmail;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << "Contact{name='" << contact.name << "', phoneNumber='" << contact.phoneNumber << "', email='" << contact.email << "'}";
        return os;
    }
};

// Linear Search Function
int linearSearch(const vector<Contact>& contacts, const string& target) {
    int iterations = 0;
    for (size_t i = 0; i < contacts.size(); ++i) {
        iterations++;
        if (contacts[i].getName() == target) {
            cout << "Linear search iterations: " << iterations << endl;
            return i;
        }
    }
    cout << "Linear search iterations: " << iterations << endl;
    return -1;
}

// Binary Search Function
int binarySearch(const vector<Contact>& contacts, const string& target) {
    int left = 0;
    int right = contacts.size() - 1;
    int iterations = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        iterations++;

        if (contacts[mid].getName() == target) {
            cout << "Binary search iterations: " << iterations << endl;
            return mid;
        }

        if (contacts[mid].getName() < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << "Binary search iterations: " << iterations << endl;
    return -1;
}

// Binary Recursive Search Helper Function
int binaryRecursionHelper(const vector<Contact>& contacts, const string& target, int left, int right, int& iterations) {
    // Base case
    if (left > right) {
        cout << "Binary recursive search iterations: " << iterations << endl;
        return -1;
    }

    // Recursive case
    int mid = left + (right - left) / 2;
    iterations++;

    // Check if the target is found
    if (contacts[mid].getName() == target) {
        cout << "Binary recursive search iterations: " << iterations << endl;
        return mid;
        // Check if the target is in the right half
    } else if (contacts[mid].getName() < target) {
        // Recursively search the right half
        return binaryRecursionHelper(contacts, target, mid + 1, right, iterations);
        // Check if the target is in the left half
    } else {
        // Recursively search the left half
        return binaryRecursionHelper(contacts, target, left, mid - 1, iterations);
    }
}

// Binary Recursive Search Function
int binaryRecursive(const vector<Contact>& contacts, const string& target) {
    int iterations = 0;
    return binaryRecursionHelper(contacts, target, 0, contacts.size() - 1, iterations);
}


int main() {
    vector<Contact> contacts;
    contacts.emplace_back("Alice", "123-456-7890", "alice@email.com");
    contacts.emplace_back("Bob", "987-654-3210", "bob@email.com");
    contacts.emplace_back("Charlie", "456-789-1234", "charlie@email.com");

    string targetName;
    cout << "Enter the name to search: ";

    bool validInput = false;

    // loop until valid input is entered
    while(!validInput) {
        // get the target name
        getline(cin, targetName);
        //check if input is empty or only spaces
        if (targetName.empty() || targetName.find_first_not_of(' ') == string::npos){
            cout << "Invalid input. Please enter a valid name: ";
        } else {
            //check if first char is uppercase
            if (isupper(targetName[0])) {
                validInput = true;
            // if not, capitalize the first letter
            } else {
                targetName[0] = toupper(targetName[0]);
                validInput = true;
            }
        }
    }

    cout << "\n Target name is: " + targetName + "\n";

    // Get the current time before the search
    auto startLinear = high_resolution_clock::now();
    // Perform Linear Search
    int resultLinear = linearSearch(contacts, targetName);
    // Get the current time after the search and calculate the duration
    auto endLinear = high_resolution_clock::now();
    auto durationLinear = duration_cast<microseconds>(endLinear - startLinear).count();

    if (resultLinear != -1) {
        cout << "Contact found by linear search at index: " << resultLinear << endl;
        cout << "Time taken for linear search: " << durationLinear << " microseconds" << endl << endl;
    } else {
        cout << "Contact not found by linear search." << endl << endl;
    }

    // Get the current time before the search
    auto startBinary = high_resolution_clock::now();
    // Perform Binary Search
    int resultBinary = binarySearch(contacts, targetName);
    // Get the current time after the search and calculate the duration
    auto endBinary = high_resolution_clock::now();
    auto durationBinary = duration_cast<microseconds>(endBinary - startBinary).count();

    if (resultBinary != -1) {
        cout << "Contact found by binary search at index: " << resultBinary << endl;
        cout << "Time taken for binary search: " << durationBinary << " microseconds" << endl << endl;
    } else {
        cout << "Contact not found by binary search." << endl << endl;
    }

    // Get the current time before the search
    auto startBinaryRecursive = high_resolution_clock::now();
    // Perform Binary Recursive Search
    int resultBinaryRecursive = binaryRecursive(contacts, targetName);
    // Get the current time after the search and calculate the duration
    auto endBinaryRecursive = high_resolution_clock::now();
    auto durationBinaryRecursive = duration_cast<microseconds>(endBinaryRecursive - startBinaryRecursive).count();

    if (resultBinaryRecursive != -1) {
        cout << "Contact found by binary recursive search at index: " << resultBinaryRecursive << endl;
        cout << "Time taken for binary recursive search: " << durationBinaryRecursive << " microseconds" << endl << endl;
    } else {
        cout << "Contact not found by binary recursive search." << endl << endl;
    }

    return 0;
}
