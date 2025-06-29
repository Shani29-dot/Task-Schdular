Task Scheduler (C++)
A console-based task management system designed to handle and display different types of tasks using custom data structures. The project aims to simulate a productivity tool that organizes tasks based on their type and priority.

🛠️ Features
Add Tasks

High-priority tasks (stored in a doubly linked list as a priority queue)

General tasks (stored in a singly linked list)

Repeating tasks (stored in a circular linked list)

Complete Tasks

Handles task completion by priority (high > general > repeating)

Completed tasks are stored in a stack

Display Tasks

View all task categories including completed tasks

Console color coding for better visualization

User-Friendly Interface

Welcome screen

Input validation

Menu-driven options

Color-coded output using Windows API

📌 Data Structures Used
Task Type	Data Structure
High-Priority	Doubly Linked List (Priority Queue)
General Tasks	Singly Linked List
Repeating Tasks	Circular Linked List
Completed Tasks	Stack

💻 Technologies Used
Language: C++

Platform: Windows Console

Libraries: iostream, stack, windows.h, limits, cstdlib

📸 Sample Output (Features)

==============================================
     Welcome to the Advanced Task Manager!     
==============================================
 Manage your tasks efficiently with features like:
 -> High-priority task handling
 -> General task tracking
 -> Repeating task management
 -> Task completion history
----------------------------------------------
       Your productivity partner awaits!       
==============================================
📂 How to Run
Compile using any standard C++ compiler (e.g., g++, Dev C++, Code::Blocks)

Run the compiled executable

Follow the on-screen menu options

🧠 Learning Outcomes
Practical implementation of custom data structures

Understanding of task scheduling logic

Command-line UI and interaction flow

Priority handling and task classification logic

📌 Note
This project was built for educational purposes to practice C++ and understand core data structure concepts. It does not include file storage or GUI features.
