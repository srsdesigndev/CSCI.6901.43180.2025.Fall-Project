# Principles of Computer Programming

## Project Proposal: Peer Study Matching Program

**Your Name:** Sundar Raj Sharma, Y00889901  
**Course Title:** Principles of Computer Programming  
**Instructor's Name:** Rachel E. Gramann  
**Institution:** Youngstown State University  
**Date:** Sep 18, 2025  

---
## Introduction

Forming effective study groups can greatly improve student learning, engagement, and collaboration, especially in large classes or after remote learning periods. This project aims to create a program that helps students connect with peers who complement their academic needs and interests.

---

## Business Idea Description

The Study Group Matching System allows students to input their learning preferences, academic strengths and weaknesses, goals, and availability. The program then suggests compatible peers to form study groups, enhancing collaboration and making learning more efficient and enjoyable. This solution helps build stronger academic communities within schools and universities.

---
## Implementation Plan Using C++ Concepts

The program will be built using object-oriented programming (OOP) principles to model the various components of the study group system. Core classes will include:

- **Student:** Stores information such as name, academic strengths and weaknesses, learning style, interests, and availability.  
- **LearningProfile:** Captures each student’s preferences, skills, and goals for study sessions.  
- **StudyGroup:** Manages the members of each group, schedules, and tracks group performance.  

Vectors will be used to dynamically manage lists of students and study groups, allowing for flexible group sizes and easy addition or removal of members. Functions will calculate compatibility scores based on student attributes, interests, and availability to suggest optimal peer matches.

The program will utilize file I/O operations to save and load student profiles and group assignments, ensuring persistent data across sessions. Exception handling will be implemented to handle incomplete or inconsistent data, such as missing student availability, preventing program crashes and ensuring smooth execution.

This approach demonstrates mastery of key C++ concepts learned in the course, including:

- Classes and objects for modeling real-world entities  
- Inheritance to extend and reuse functionality (if needed)  
- Vectors and arrays for dynamic data management  
- Functions for modular and reusable logic  
- File handling for data persistence  
- Exception handling for robust and professional-grade software  

The design ensures that the project is practical, feasible, and aligned with course objectives, while still providing meaningful functionality in the educational domain.

---

## Conclusion

This project provides a practical and achievable application of C++ programming concepts to a real-world problem. By helping students form compatible study groups, it promotes collaboration, engagement, and more effective learning.
