# CSCE 2110 – Project 2
## Milestone 1

### Project Description

This project is a Campus Facility Management System written in C++. It uses different data structures to manage campus facilities, building connections, and departments.

Milestone 1 focuses on loading data from files, storing information, searching for records, and displaying results.

### Features

**Facility Management**
- Load facility information from a text file.
- Validate facility records.
- Display all facilities.
- Search for facilities by ID using a hash table.

**Campus Graph**
- Store campus buildings and connections using an adjacency list.
- Display buildings and their connections.
- Use Breadth-First Search (BFS) to find reachable buildings.
- Display distances between buildings.

**Department Tree**
- Load departments from a text file.
- Store departments in a general tree.
- Add departments under existing departments.
- Search for departments by name.
- Display the department hierarchy.
- Perform preorder traversal.

### Data Structures Used

- **Hash table:** Searches for facilities by ID.
- **Graph (adjacency list):** Represents connections between buildings.
- **Queue:** Supports BFS traversal.
- **General tree:** Stores parent-child department relationships.
- **Vectors:** Store collections of data.

### Project Structure

```text
Project2/
├── include/
│   ├── Facility.h
│   ├── CampusGraph.h
│   ├── DepartmentTree.h
│   └── Helpers.h
├── src/
│   ├── Facility.cpp
│   ├── CampusGraph.cpp
│   ├── DepartmentTree.cpp
│   └── main.cpp
├── data/
└── README.md
```

### How to Compile and Run

From the project directory, compile with g++:

```bash
g++ -std=c++11 -Iinclude src/*.cpp -o project2
```

Run on Windows:

```powershell
.\project2.exe
```

Run on Linux or macOS:

```bash
./project2
```

Place the four required assignment input files in the `data/` folder before running the program.

### Input Files

The program reads four assignment-provided input files containing facilities, buildings, connections, and departments. Invalid records should be skipped with a warning.

### Milestone 1 Scope

This milestone covers basic facility management, campus graph operations, and department tree operations. Department statistics and additional tree traversals are reserved for the final milestone.

