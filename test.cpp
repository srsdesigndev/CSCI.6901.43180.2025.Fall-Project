#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    string name, email, age;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your age: ";
    getline(cin, age);

    // Create JSON object
    json profile;
    profile["name"] = name;
    profile["email"] = email;
    profile["age"] = age;

    // Save JSON to file
    ofstream file("profile.json");
    if (file.is_open()) {
        file << profile.dump(4); // pretty print with 4 spaces
        file.close();
        cout << "Profile saved to profile.json successfully!" << endl;
    } else {
        cout << "Error: Could not open file for writing." << endl;
    }

    return 0;
}
