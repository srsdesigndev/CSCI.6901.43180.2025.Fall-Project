# Peer Study Matching System - Simple Project Plan

**Student:** Sundar Raj Sharma (Y00889901)  
**Course:** Principles of Computer Programming

---

## Project Goal

Create a **simple** C++ console program that matches students into study groups.

**What it does:**
- Add students with their info
- Save/load from a text file
- Match students based on simple criteria
- Display groups

---
## Simple 3-Phase Plan

### Phase 1: Basic Classes (Days 1-3)
**Make it work first!**

Create 3 simple classes:
```cpp
class Student {
    string name;
    string subject;  // what they're good at
    string needs;    // what they need help with
};

class StudyGroup {
    vector<Student> members;
    int groupID;
};
```

**Tasks:**
- Make Student class with basic info
- Make StudyGroup class 
- Test creating students in main()

---

### Phase 2: File Save/Load & Menu (Days 4-7)

**Simple text file storage:**
```
John,Math,English
Sarah,English,Math
Mike,Science,History
```

**Simple menu:**
```
1. Add Student
2. View Students  
3. Make Groups
4. Exit
```

**Tasks:**
- Save students to `students.txt`
- Load students from file
- Make basic console menu
- Add input validation

---

### Phase 3: Matching & Polish (Days 8-10)

**Simple matching:**
- If Student A is good at what Student B needs → Match!
- Put 3-4 students per group
- Save groups to file

**Tasks:**
- Write simple matching function
- Display groups nicely
- Test everything
- Write 2-page report

---

## File Structure (Keep it Simple!)

```
project/
├── main.cpp           # Everything in one file is OK!
├── students.txt       # Data file
└── groups.txt         # Output file
```

**OR** if you want to split it:
```
project/
├── main.cpp
├── Student.h
├── Student.cpp
├── students.txt
└── groups.txt
```

---

## What You MUST Include (Assignment Requirements)

✅ **Classes** - Student, StudyGroup (2 classes minimum)  
✅ **Inheritance** - Person → Student (simple base/derived)  
✅ **Vectors** - `vector<Student>` to store students  
✅ **Functions** - makeGroups(), saveFile(), loadFile()  
✅ **File I/O** - Read/write students.txt  
✅ **User Input** - Console menu with cin/cout  
✅ **Exception Handling** - Try/catch for file errors  

---

## Simple Matching Logic

```cpp
// Match students who can help each other
if (student1.goodAt == student2.needsHelpWith) {
    // They match! Put in same group
}
```

That's it! Don't overthink it.

---

## Quick Start

**Day 1-2:** Make Student class, test it  
**Day 3-4:** Add file save/load  
**Day 5-6:** Make simple menu  
**Day 7-8:** Add matching function  
**Day 9:** Test everything  
**Day 10:** Write report (2 pages)

---

## Report Outline (Keep it Short!)

**Page 1:**
- What the program does
- What classes you made
- How matching works

**Page 2:**
- Problems you had
- How you fixed them
- Future improvements

Done!

---

## Tips

1. Start with everything in `main.cpp` - it's okay!
2. Test after every small change
3. Don't add fancy features - basic is fine
4. If stuck, ask for help early
5. Simple working code > complicated broken code

---

Ready to start coding? Let me know which part you want to build first!