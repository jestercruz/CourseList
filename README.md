# CourseList# ABCU Course Planner

## Overview

This repository contains artifacts from two major projects completed as part of the ABCU Computer Science program's Data Structures and Algorithms course. These projects demonstrate my understanding and application of key data structures, algorithm analysis, and program design principles.

- An analysis of time and space complexity for vector, hash table, and binary search tree implementations.
- A working C++ program that uses a hash table to load, organize, and print course data for the ABCU Computer Science advising system.

---

## Portfolio Reflection

### What was the problem you were solving in the projects for this course?

The main objective was to design and implement a system to manage and display course information for a computer science advising program. The system needed to efficiently load course data from a file, support fast lookups, validate prerequisites, and display courses in alphanumeric order.

### How did you approach the problem? Consider why data structures are important to understand.

I approached the problem by first analyzing different data structure options (vector, hash table, binary search tree) for their time and space efficiency in terms of loading data, searching for courses, validating prerequisites, and printing the course list. Understanding the strengths and weaknesses of these structures allowed me to select the hash table as the most appropriate tool for fast lookups and scalability, while still enabling alphanumeric output through sorted key traversal.

### How did you overcome any roadblocks you encountered while going through the activities or project?

Some key challenges included:
- Managing prerequisite validation efficiently.
- Ensuring case-insensitive input handling.
- Implementing alphanumeric sorting despite using a hash table (which doesn’t maintain order).

To overcome these, I used a vector to temporarily store all courses before sorting them for display. I also used careful input processing and modularized the code for readability and reusability.

### How has your work on this project expanded your approach to designing software and developing programs?

This project taught me the importance of analyzing algorithm complexity before committing to a design. It also reinforced the value of breaking down tasks into small, testable functions and maintaining separation between data handling, processing, and user interaction. I now approach software design with performance, modularity, and future scalability in mind.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I’ve learned to:
- Use consistent naming conventions and add meaningful comments.
- Separate logic into dedicated functions for clarity and reuse.
- Choose appropriate data structures based on access patterns.
- Consider edge cases such as empty fields or malformed input files.

These habits make my code easier to debug, extend, and hand off to collaborators.

---

## How to Run the Program

1. Place the CSV input file (e.g., `CS 300 ABCU_Advising_Program_Input.csv`) in the same directory as the source file.
2. Compile the C++ code using a standard compiler:

   ```bash
   g++ -o course_planner course_planner.cpp
