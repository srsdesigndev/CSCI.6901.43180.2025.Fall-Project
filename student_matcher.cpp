#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Forward declarations
class LearningProfile;
class Student;
class StudyGroup;
class JSONHandler;

// ==================== UTILITY FUNCTIONS ====================

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-"
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
       << setfill('0') << setw(2) << ltm->tm_mday;
    return ss.str();
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==================== LEARNING PROFILE CLASS ====================

class LearningProfile {
private:
    string learningStyle;
    vector<string> strengths;
    vector<string> weaknesses;
    vector<string> interests;
    vector<string> availability;
    string goals;

public:
    LearningProfile() {
        learningStyle = "Visual";
        goals = "";
    }
    
    LearningProfile(string style, string studyGoals) {
        learningStyle = style;
        goals = studyGoals;
    }
    
    // Getters
    string getLearningStyle() const { return learningStyle; }
    vector<string> getStrengths() const { return strengths; }
    vector<string> getWeaknesses() const { return weaknesses; }
    vector<string> getInterests() const { return interests; }
    vector<string> getAvailability() const { return availability; }
    string getGoals() const { return goals; }
    
    // Setters
    void setLearningStyle(string style) { learningStyle = style; }
    void setGoals(string studyGoals) { goals = studyGoals; }
    void addStrength(string strength) { strengths.push_back(strength); }
    void addWeakness(string weakness) { weaknesses.push_back(weakness); }
    void addInterest(string interest) { interests.push_back(interest); }
    void addAvailability(string time) { availability.push_back(time); }
    void clearStrengths() { strengths.clear(); }
    void clearWeaknesses() { weaknesses.clear(); }
    void clearAvailability() { availability.clear(); }
    
    void display() const {
        cout << "  Learning Style: " << learningStyle << endl;
        cout << "  Goals: " << goals << endl;
        
        cout << "  Strengths: ";
        if (strengths.empty()) cout << "None";
        else {
            for (size_t i = 0; i < strengths.size(); i++) {
                cout << strengths[i];
                if (i < strengths.size() - 1) cout << ", ";
            }
        }
        cout << endl;
        
        cout << "  Weaknesses: ";
        if (weaknesses.empty()) cout << "None";
        else {
            for (size_t i = 0; i < weaknesses.size(); i++) {
                cout << weaknesses[i];
                if (i < weaknesses.size() - 1) cout << ", ";
            }
        }
        cout << endl;
        
        cout << "  Availability: ";
        if (availability.empty()) cout << "Not specified";
        else {
            for (size_t i = 0; i < availability.size(); i++) {
                cout << availability[i];
                if (i < availability.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
    
    int calculateCompatibility(const LearningProfile& other) const {
        int score = 0;
        
        // Complementary strengths/weaknesses (60 points)
        int complementScore = 0;
        for (const string& myStrength : strengths) {
            for (const string& theirWeakness : other.weaknesses) {
                if (myStrength == theirWeakness) complementScore += 15;
            }
        }
        for (const string& myWeakness : weaknesses) {
            for (const string& theirStrength : other.strengths) {
                if (myWeakness == theirStrength) complementScore += 15;
            }
        }
        score += min(complementScore, 60);
        
        // Matching availability (25 points)
        int availMatch = 0;
        for (const string& myTime : availability) {
            for (const string& theirTime : other.availability) {
                if (myTime == theirTime) availMatch += 8;
            }
        }
        score += min(availMatch, 25);
        
        // Similar learning style (15 points)
        if (learningStyle == other.learningStyle) score += 15;
        
        return min(score, 100);
    }
    
    json toJSON() const {
        return json{
            {"learningStyle", learningStyle},
            {"strengths", strengths},
            {"weaknesses", weaknesses},
            {"interests", interests},
            {"availability", availability},
            {"goals", goals}
        };
    }
    
    static LearningProfile fromJSON(const json& j) {
        LearningProfile profile;
        profile.learningStyle = j.value("learningStyle", "Visual");
        profile.strengths = j.value("strengths", vector<string>());
        profile.weaknesses = j.value("weaknesses", vector<string>());
        profile.interests = j.value("interests", vector<string>());
        profile.availability = j.value("availability", vector<string>());
        profile.goals = j.value("goals", "");
        return profile;
    }
};

// ==================== STUDENT CLASS ====================

class Student {
private:
    string studentId;
    string name;
    string email;
    string major;
    int year;
    string enrollmentDate;
    LearningProfile profile;
    string groupId;
    bool isActive;

public:
    Student() {
        studentId = "";
        name = "";
        email = "";
        major = "";
        year = 1;
        enrollmentDate = getCurrentDate();
        groupId = "";
        isActive = true;
    }
    
    Student(string id, string studentName, string studentEmail, string studentMajor, int studentYear) {
        studentId = id;
        name = studentName;
        email = studentEmail;
        major = studentMajor;
        year = studentYear;
        enrollmentDate = getCurrentDate();
        groupId = "";
        isActive = true;
    }
    
    // Getters
    string getStudentId() const { return studentId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getMajor() const { return major; }
    int getYear() const { return year; }
    string getEnrollmentDate() const { return enrollmentDate; }
    LearningProfile& getProfile() { return profile; }
    const LearningProfile& getProfile() const { return profile; }
    string getGroupId() const { return groupId; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setName(string n) { name = n; }
    void setEmail(string e) { email = e; }
    void setMajor(string m) { major = m; }
    void setYear(int y) { year = y; }
    void setProfile(const LearningProfile& p) { profile = p; }
    void setGroupId(string gId) { groupId = gId; }
    void setIsActive(bool active) { isActive = active; }
    
    void display() const {
        cout << "\n========================================" << endl;
        cout << "         STUDENT PROFILE" << endl;
        cout << "========================================" << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Major: " << major << endl;
        cout << "Year: " << year << endl;
        cout << "Enrolled: " << enrollmentDate << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
        cout << "Group: " << (groupId.empty() ? "Not assigned" : groupId) << endl;
        cout << "\nLearning Profile:" << endl;
        profile.display();
        cout << "========================================\n" << endl;
    }
    
    void displaySummary() const {
        cout << studentId << " | " << name << " | " << major 
             << " | Year " << year 
             << " | Group: " << (groupId.empty() ? "None" : groupId) << endl;
    }
    
    int calculateCompatibility(const Student& other) const {
        return profile.calculateCompatibility(other.profile);
    }
    
    json toJSON() const {
        return json{
            {"studentId", studentId},
            {"name", name},
            {"email", email},
            {"major", major},
            {"year", year},
            {"enrollmentDate", enrollmentDate},
            {"learningProfile", profile.toJSON()},
            {"groupId", groupId},
            {"isActive", isActive}
        };
    }
    
    static Student fromJSON(const json& j) {
        Student student;
        student.studentId = j.value("studentId", "");
        student.name = j.value("name", "");
        student.email = j.value("email", "");
        student.major = j.value("major", "");
        student.year = j.value("year", 1);
        student.enrollmentDate = j.value("enrollmentDate", getCurrentDate());
        student.groupId = j.value("groupId", "");
        student.isActive = j.value("isActive", true);
        
        if (j.contains("learningProfile")) {
            student.profile = LearningProfile::fromJSON(j["learningProfile"]);
        }
        
        return student;
    }
};

// ==================== STUDY GROUP CLASS ====================

class StudyGroup {
private:
    string groupId;
    string groupName;
    vector<string> members;
    string createdDate;
    vector<string> meetingSchedule;
    string subject;
    int maxMembers;
    float compatibilityScore;
    bool isActive;

public:
    StudyGroup() {
        groupId = "";
        groupName = "";
        createdDate = getCurrentDate();
        subject = "";
        maxMembers = 4;
        compatibilityScore = 0.0;
        isActive = true;
    }
    
    StudyGroup(string id) {
        groupId = id;
        groupName = "";
        createdDate = getCurrentDate();
        subject = "";
        maxMembers = 4;
        compatibilityScore = 0.0;
        isActive = true;
    }
    
    // Getters
    string getGroupId() const { return groupId; }
    string getGroupName() const { return groupName; }
    vector<string> getMembers() const { return members; }
    int getSize() const { return members.size(); }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setGroupName(string name) { groupName = name; }
    void setIsActive(bool active) { isActive = active; }
    
    bool addMember(string studentId) {
        if (members.size() >= (size_t)maxMembers) return false;
        if (find(members.begin(), members.end(), studentId) != members.end()) return false;
        members.push_back(studentId);
        return true;
    }
    
    bool hasMember(string studentId) const {
        return find(members.begin(), members.end(), studentId) != members.end();
    }
    
    bool isFull() const {
        return members.size() >= (size_t)maxMembers;
    }
    
    void display() const {
        cout << "\n========================================" << endl;
        cout << "         STUDY GROUP" << endl;
        cout << "========================================" << endl;
        cout << "Group ID: " << groupId << endl;
        cout << "Name: " << (groupName.empty() ? "Unnamed Group" : groupName) << endl;
        cout << "Members: " << members.size() << "/" << maxMembers << endl;
        
        if (!members.empty()) {
            cout << "\nMember IDs:" << endl;
            for (size_t i = 0; i < members.size(); i++) {
                cout << "  " << (i + 1) << ". " << members[i] << endl;
            }
        }
        cout << "========================================\n" << endl;
    }
    
    void displaySummary() const {
        cout << groupId << " | " << members.size() << "/" << maxMembers << " members" << endl;
    }
    
    json toJSON() const {
        return json{
            {"groupId", groupId},
            {"groupName", groupName},
            {"members", members},
            {"createdDate", createdDate},
            {"meetingSchedule", meetingSchedule},
            {"subject", subject},
            {"maxMembers", maxMembers},
            {"compatibilityScore", compatibilityScore},
            {"isActive", isActive}
        };
    }
    
    static StudyGroup fromJSON(const json& j) {
        StudyGroup group;
        group.groupId = j.value("groupId", "");
        group.groupName = j.value("groupName", "");
        group.members = j.value("members", vector<string>());
        group.createdDate = j.value("createdDate", getCurrentDate());
        group.meetingSchedule = j.value("meetingSchedule", vector<string>());
        group.subject = j.value("subject", "");
        group.maxMembers = j.value("maxMembers", 4);
        group.compatibilityScore = j.value("compatibilityScore", 0.0f);
        group.isActive = j.value("isActive", true);
        return group;
    }
};

// ==================== JSON HANDLER CLASS ====================

class JSONHandler {
private:
    static const string STUDENTS_FILE;
    static const string GROUPS_FILE;

public:
    static bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.good();
    }
    
    static void initializeFiles() {
        if (!fileExists(STUDENTS_FILE)) {
            json emptyStudents = {
                {"students", json::array()},
                {"metadata", {{"totalStudents", 0}, {"version", "1.0"}}}
            };
            ofstream file(STUDENTS_FILE);
            file << emptyStudents.dump(4);
            file.close();
        }
        
        if (!fileExists(GROUPS_FILE)) {
            json emptyGroups = {
                {"groups", json::array()},
                {"metadata", {{"totalGroups", 0}, {"version", "1.0"}}}
            };
            ofstream file(GROUPS_FILE);
            file << emptyGroups.dump(4);
            file.close();
        }
    }
    
    static bool saveAllStudents(const vector<Student>& students) {
        try {
            json data;
            data["students"] = json::array();
            
            for (const Student& student : students) {
                data["students"].push_back(student.toJSON());
            }
            
            data["metadata"] = {{"totalStudents", students.size()}, {"version", "1.0"}};
            
            ofstream file(STUDENTS_FILE);
            if (!file.is_open()) return false;
            file << data.dump(4);
            file.close();
            return true;
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            return false;
        }
    }
    
    static vector<Student> loadAllStudents() {
        vector<Student> students;
        try {
            if (!fileExists(STUDENTS_FILE)) return students;
            
            ifstream file(STUDENTS_FILE);
            if (!file.is_open()) return students;
            
            json data = json::parse(file);
            file.close();
            
            if (data.contains("students") && data["students"].is_array()) {
                for (const auto& studentJson : data["students"]) {
                    students.push_back(Student::fromJSON(studentJson));
                }
            }
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        return students;
    }
    
    static bool studentExists(const string& studentId) {
        vector<Student> students = loadAllStudents();
        for (const Student& student : students) {
            if (student.getStudentId() == studentId) return true;
        }
        return false;
    }
    
    static Student findStudent(const string& studentId) {
        vector<Student> students = loadAllStudents();
        for (const Student& student : students) {
            if (student.getStudentId() == studentId) return student;
        }
        return Student();
    }
    
    static bool updateStudent(const Student& updatedStudent) {
        vector<Student> students = loadAllStudents();
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getStudentId() == updatedStudent.getStudentId()) {
                students[i] = updatedStudent;
                return saveAllStudents(students);
            }
        }
        return false;
    }
    
    static bool deleteStudent(const string& studentId) {
        vector<Student> students = loadAllStudents();
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getStudentId() == studentId) {
                students[i].setIsActive(false);
                students[i].setGroupId("");
                return saveAllStudents(students);
            }
        }
        return false;
    }
    
    static bool saveAllGroups(const vector<StudyGroup>& groups) {
        try {
            json data;
            data["groups"] = json::array();
            
            for (const StudyGroup& group : groups) {
                data["groups"].push_back(group.toJSON());
            }
            
            data["metadata"] = {{"totalGroups", groups.size()}, {"version", "1.0"}};
            
            ofstream file(GROUPS_FILE);
            if (!file.is_open()) return false;
            file << data.dump(4);
            file.close();
            return true;
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            return false;
        }
    }
    
    static vector<StudyGroup> loadAllGroups() {
        vector<StudyGroup> groups;
        try {
            if (!fileExists(GROUPS_FILE)) return groups;
            
            ifstream file(GROUPS_FILE);
            if (!file.is_open()) return groups;
            
            json data = json::parse(file);
            file.close();
            
            if (data.contains("groups") && data["groups"].is_array()) {
                for (const auto& groupJson : data["groups"]) {
                    groups.push_back(StudyGroup::fromJSON(groupJson));
                }
            }
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        return groups;
    }
    
    static StudyGroup findGroup(const string& groupId) {
        vector<StudyGroup> groups = loadAllGroups();
        for (const StudyGroup& group : groups) {
            if (group.getGroupId() == groupId) return group;
        }
        return StudyGroup();
    }
};

const string JSONHandler::STUDENTS_FILE = "students.json";
const string JSONHandler::GROUPS_FILE = "groups.json";

// ==================== MENU FUNCTIONS ====================

void displayMainMenu();
void enrollNewStudent();
void viewMyProfile();
void updateMyProfile();
void withdrawEnrollment();
void generateGroups();
void viewMyGroup();
void viewAllGroups();
void viewAllStudents();
void viewStatistics();
string generateGroupId();

int main() {
    JSONHandler::initializeFiles();
    
    int choice;
    
    cout << "\n========================================" << endl;
    cout << "  PEER STUDY MATCHING SYSTEM" << endl;
    cout << "========================================\n" << endl;
    
    do {
        displayMainMenu();
        cout << "Enter choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: enrollNewStudent(); break;
            case 2: viewMyProfile(); break;
            case 3: updateMyProfile(); break;
            case 4: withdrawEnrollment(); break;
            case 5: generateGroups(); break;
            case 6: viewMyGroup(); break;
            case 7: viewAllGroups(); break;
            case 8: viewAllStudents(); break;
            case 9: viewStatistics(); break;
            case 10:
                cout << "\nThank you for using Peer Study Matching System!\n" << endl;
                break;
            default:
                cout << "\n❌ Invalid choice.\n" << endl;
        }
        
    } while(choice != 10);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n========================================" << endl;
    cout << "           MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. Enroll as New Student" << endl;
    cout << "2. View My Profile" << endl;
    cout << "3. Update My Profile" << endl;
    cout << "4. Withdraw Enrollment" << endl;
    cout << "5. Generate Study Groups" << endl;
    cout << "6. View My Group" << endl;
    cout << "7. View All Groups" << endl;
    cout << "8. View All Students" << endl;
    cout << "9. View Statistics" << endl;
    cout << "10. Exit" << endl;
    cout << "========================================" << endl;
}

void enrollNewStudent() {
    cout << "\n--- STUDENT ENROLLMENT ---\n" << endl;
    
    string studentId, name, email, major, learningStyle, goals;
    int year;
    
    cout << "Student ID: ";
    getline(cin, studentId);
    
    if (JSONHandler::studentExists(studentId)) {
        cout << "\n❌ Student ID already exists!\n" << endl;
        return;
    }
    
    cout << "Name: ";
    getline(cin, name);
    cout << "Email: ";
    getline(cin, email);
    cout << "Major: ";
    getline(cin, major);
    cout << "Year (1-4): ";
    cin >> year;
    clearInputBuffer();
    
    Student newStudent(studentId, name, email, major, year);
    
    cout << "\nLearning Style: ";
    getline(cin, learningStyle);
    cout << "Goals: ";
    getline(cin, goals);
    
    LearningProfile profile(learningStyle, goals);
    
    cout << "\nAdd Strengths (type 'done' to finish):" << endl;
    string strength;
    while (true) {
        cout << "  ";
        getline(cin, strength);
        if (strength == "done") break;
        if (!strength.empty()) profile.addStrength(strength);
    }
    
    cout << "\nAdd Weaknesses (type 'done' to finish):" << endl;
    string weakness;
    while (true) {
        cout << "  ";
        getline(cin, weakness);
        if (weakness == "done") break;
        if (!weakness.empty()) profile.addWeakness(weakness);
    }
    
    cout << "\nAdd Availability (type 'done' to finish):" << endl;
    string time;
    while (true) {
        cout << "  ";
        getline(cin, time);
        if (time == "done") break;
        if (!time.empty()) profile.addAvailability(time);
    }
    
    newStudent.setProfile(profile);
    
    vector<Student> students = JSONHandler::loadAllStudents();
    students.push_back(newStudent);
    
    if (JSONHandler::saveAllStudents(students)) {
        cout << "\n✅ Enrollment successful!\n" << endl;
    } else {
        cout << "\n❌ Error saving data.\n" << endl;
    }
}

void viewMyProfile() {
    string studentId;
    cout << "\nEnter Student ID: ";
    getline(cin, studentId);
    
    if (!JSONHandler::studentExists(studentId)) {
        cout << "\n❌ Student not found!\n" << endl;
        return;
    }
    
    Student student = JSONHandler::findStudent(studentId);
    student.display();
}

void updateMyProfile() {
    string studentId;
    cout << "\nEnter Student ID: ";
    getline(cin, studentId);
    
    if (!JSONHandler::studentExists(studentId)) {
        cout << "\n❌ Student not found!\n" << endl;
        return;
    }
    
    Student student = JSONHandler::findStudent(studentId);
    
    cout << "\n1. Update Name\n2. Update Email\n3. Update Major\n4. Update Goals\n5. Back\nChoice: ";
    int choice;
    cin >> choice;
    clearInputBuffer();
    
    if (choice == 1) {
        string name;
        cout << "New Name: ";
        getline(cin, name);
        student.setName(name);
    } else if (choice == 2) {
        string email;
        cout << "New Email: ";
        getline(cin, email);
        student.setEmail(email);
    } else if (choice == 3) {
        string major;
        cout << "New Major: ";
        getline(cin, major);
        student.setMajor(major);
    } else if (choice == 4) {
        string goals;
        cout << "New Goals: ";
        getline(cin, goals);
        student.getProfile().setGoals(goals);
    }
    
    if (choice >= 1 && choice <= 4) {
        if (JSONHandler::updateStudent(student)) {
            cout << "\n✅ Updated!\n" << endl;
        } else {
            cout << "\n❌ Error updating.\n" << endl;
        }
    }
}

void withdrawEnrollment() {
    string studentId;
    cout << "\nEnter Student ID: ";
    getline(cin, studentId);
    
    string confirm;
    cout << "Confirm withdrawal (yes/no): ";
    getline(cin, confirm);
    
    if (confirm == "yes") {
        if (JSONHandler::deleteStudent(studentId)) {
            cout << "\n✅ Withdrawn.\n" << endl;
        } else {
            cout << "\n❌ Error.\n" << endl;
        }
    }
}

string generateGroupId() {
    static int counter = 1;
    return "GROUP_" + to_string(counter++);
}

void generateGroups() {
    vector<Student> allStudents = JSONHandler::loadAllStudents();
    vector<Student> unassigned;
    
    for (const Student& s : allStudents) {
        if (s.getIsActive() && s.getGroupId().empty()) {
            unassigned.push_back(s);
        }
    }
    
    if (unassigned.size() < 2) {
        cout << "\nNeed at least 2 students.\n" << endl;
        return;
    }
    
    vector<StudyGroup> newGroups;
    vector<bool> assigned(unassigned.size(), false);
    
    for (size_t i = 0; i < unassigned.size(); i++) {
        if (assigned[i]) continue;
        
        StudyGroup group(generateGroupId());
        group.addMember(unassigned[i].getStudentId());
        assigned[i] = true;
        
        for (size_t j = i + 1; j < unassigned.size() && !group.isFull(); j++) {
            if (!assigned[j]) {
                int compat = unassigned[i].calculateCompatibility(unassigned[j]);
                if (compat > 30) {
                    group.addMember(unassigned[j].getStudentId());
                    assigned[j] = true;
                }
            }
        }
        
        for (size_t j = 0; j < unassigned.size() && group.getSize() < 3; j++) {
            if (!assigned[j]) {
                group.addMember(unassigned[j].getStudentId());
                assigned[j] = true;
            }
        }
        
        newGroups.push_back(group);
    }
    
    for (Student& student : allStudents) {
        for (const StudyGroup& group : newGroups) {
            if (group.hasMember(student.getStudentId())) {
                student.setGroupId(group.getGroupId());
                break;
            }
        }
    }
    
    JSONHandler::saveAllStudents(allStudents);
    
    vector<StudyGroup> allGroups = JSONHandler::loadAllGroups();
    allGroups.insert(allGroups.end(), newGroups.begin(), newGroups.end());
    JSONHandler::saveAllGroups(allGroups);
    
    cout << "\n✅ Created " << newGroups.size() << " groups!\n" << endl;
}

void viewMyGroup() {
    string studentId;
    cout << "\nEnter Student ID: ";
    getline(cin, studentId);
    
    if (!JSONHandler::studentExists(studentId)) {
        cout << "\n❌ Not found!\n" << endl;
        return;
    }
    
    Student student = JSONHandler::findStudent(studentId);
    if (student.getGroupId().empty()) {
        cout << "\nNot in a group.\n" << endl;
        return;
    }
    
    StudyGroup group = JSONHandler::findGroup(student.getGroupId());
    group.display();
}

void viewAllGroups() {
    vector<StudyGroup> groups = JSONHandler::loadAllGroups();
    cout << "\nTotal Groups: " << groups.size() << "\n" << endl;
    for (const StudyGroup& g : groups) {
        if (g.getIsActive()) g.displaySummary();
    }
    cout << endl;
}

void viewAllStudents() {
    vector<Student> students = JSONHandler::loadAllStudents();
    cout << "\nTotal Students: " << students.size() << "\n" << endl;
    for (const Student& s : students) {
        if (s.getIsActive()) s.displaySummary();
    }
    cout << endl;
}

void viewStatistics() {
    vector<Student> students = JSONHandler::loadAllStudents();
    vector<StudyGroup> groups = JSONHandler::loadAllGroups();
    
    int active = 0, assigned = 0;
    for (const Student& s : students) {
        if (s.getIsActive()) {
            active++;
            if (!s.getGroupId().empty()) assigned++;
        }
    }
    
    cout << "\n=== STATISTICS ===" << endl;
    cout << "Active Students: " << active << endl;
    cout << "Assigned to Groups: " << assigned << endl;
    cout << "Total Groups: " << groups.size() << endl;
    cout << "==================\n" << endl;
}