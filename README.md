# Inverted Search Engine Using Hashing Techniques

## Overview
The Inverted Search Engine is a command-line application written in **C** that helps users quickly identify which text files contain a specific word and how many times it appears in each file. The project builds an **indexed database of words** from multiple text files using **hashing and linked lists**, similar to the basic working principle of search engines.

This project demonstrates practical usage of **data structures, file handling, and system-level C programming**.

---

## Features
- Indexes words from multiple text files into a searchable database  
- Allows searching for a word and displays matching files with occurrence counts  
- Displays the complete indexed database in a structured format  
- Saves the indexed database to a `.txt` file for persistence  
- Updates the database by loading data from a previously saved file  
- Validates input files and handles empty or duplicate files  
- Uses hash-based indexing with linked lists for efficient search  
- Menu-driven command-line interface for easy interaction  

---

## Technologies Used
- C (Advanced)
- Hash Tables
- Singly Linked Lists
- Dynamic Memory Allocation
- File I/O Operations
- String Manipulation
- Modular Programming
- Makefile
- GCC Compiler

---


---

## How It Works
1. The program reads multiple text files provided by the user.
2. Each word is processed and mapped to a hash index.
3. Hash collisions are handled using linked lists.
4. Each node stores the word, the file name, and occurrence count.
5. Users can search for words, view the full database, or save/load indexed data.
6. All memory is dynamically allocated and freed to avoid leaks.

---

## Example usage
./inverted_search file1.txt file2.txt file3.txt

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database
6. Exit


