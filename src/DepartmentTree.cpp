
#include "../include/DepartmentTree.h"

#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

namespace {

// Remove whitespace at the beginning and end of a field.
string trim(const string& value) {
    string::size_type first = 0;
    while (first < value.size() &&
           isspace(static_cast<unsigned char>(value[first]))) {
        ++first;
    }

    string::size_type last = value.size();
    while (last > first &&
           isspace(static_cast<unsigned char>(value[last - 1]))) {
        --last;
    }

    return value.substr(first, last - first);
}

// Compare two department names without regard to capitalization.
bool same(const string& firstValue, const string& secondValue) {
    const string first = trim(firstValue);
    const string second = trim(secondValue);
    if (first.size() != second.size()) {
        return false;
    }
    for (string::size_type i = 0; i < first.size(); ++i) {
        if (tolower(static_cast<unsigned char>(first[i])) !=
            tolower(static_cast<unsigned char>(second[i]))) {
            return false;
        }
    }
    return true;
}

}

// Initialize a department node and link it to its parent.
Department::Department(const string& departmentName, Department* parentDepartment)
    : name(departmentName), parent(parentDepartment) {}

// Create an empty tree.
DepartmentTree::DepartmentTree() : root(nullptr) {}

// Release all nodes owned by the tree.
DepartmentTree::~DepartmentTree() {
    DeleteTree(root);
}

// Report whether the tree has a root.
bool DepartmentTree::IsEmpty() const {
    return root == nullptr;
}

// Find a department by name.
Department* DepartmentTree::FindNode(Department* node,const string& name) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (same(node->name, name)) {
        return node;
    }
    for (Department* child : node->children) {
        Department* result = FindNode(child, name);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

// Delete a node and all of its descendants.
void DepartmentTree::DeleteTree(Department* node) {
    if (node == nullptr) {
        return;
    }
    for (Department* child : node->children) {
        DeleteTree(child);
    }
    delete node;
}

// Add a root to an empty tree or add a new child under an existing parent.
bool DepartmentTree::AddDepartment(const string& name,const string& parentName,string& error) {
    const string departmentName = trim(name);
    if (departmentName.empty()) {
        error = "Department name cannot be blank.";
        return false;
    }
    if (FindNode(root, departmentName) != nullptr) {
        error = "A department with that name already exists.";
        return false;
    }

    if (root == nullptr) {
        root = new Department(departmentName, nullptr);
        return true;
    }

    const string cleanParent = trim(parentName);
    if (cleanParent.empty()) {
        error = "Parent department cannot be blank.";
        return false;
    }
    Department* parent = FindNode(root, cleanParent);
    if (parent == nullptr) {
        error = "Parent department was not found.";
        return false;
    }
    parent->children.push_back(new Department(departmentName, parent));
    return true;
}

// Load valid department records and report rejected records with line numbers.
void DepartmentTree::LoadFromFile(const string& filename) {
    ifstream input(filename.c_str());
    int accepted = 0;
    int rejected = 0;

    if (!input.is_open()) {
        cout << "Error: unable to open " << filename << "." << endl;
        cout << "Load summary: " << filename << ": 0 accepted, 0 rejected"
             << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        const string record = trim(line);
        if (record.empty() || record[0] == '#') {
            continue;
        }

        const string::size_type separator = record.find('|');
        const bool exactlyTwoFields =
            separator != string::npos &&
            record.find('|', separator + 1) == string::npos;
        string departmentName;
        string parentName;
        if (exactlyTwoFields) {
            departmentName = trim(record.substr(0, separator));
            parentName = trim(record.substr(separator + 1));
        }

        string reason;
        Department* parent = nullptr;
        if (!exactlyTwoFields) {
            reason = "expected exactly two fields separated by '|'";
        } else if (departmentName.empty() || parentName.empty()) {
            reason = "department name and parent are required";
        } else if (FindNode(root, departmentName) != nullptr) {
            reason = "duplicate department name";
        } else if (root == nullptr) {
            if (!same(parentName, "NONE")) {
                reason = "the first department must have parent NONE";
            }
        } else {
            parent = FindNode(root, parentName);
            if (parent == nullptr) {
                reason = "parent department was not accepted on an earlier line";
            }
        }

        if (!reason.empty()) {
            ++rejected;
            cout << "Warning: " << filename << " line " << lineNumber << ": "
                 << reason << "." << endl;
        } else {
            if (root == nullptr) {
                root = new Department(departmentName, nullptr);
            } else {
                parent->children.push_back(
                    new Department(departmentName, parent));
            }
            ++accepted;
        }
    }

    cout << "Load summary: " << filename << ": " << accepted << " accepted, "
         << rejected << " rejected" << endl;
}

// Return the department's name, parent, direct-child count, and depth.
bool DepartmentTree::SearchDepartment(const string& name,string& departmentName,string& parentName,int& childCount,int& depth) const {
    Department* department = FindNode(root, name);
    if (department == nullptr) {
        return false;
    }

    departmentName = department->name;
    parentName = department->parent == nullptr
                     ? "None"
                     : department->parent->name;
    childCount = static_cast<int>(department->children.size());
    depth = 0;
    for (Department* current = department->parent;
         current != nullptr;
         current = current->parent) {
        ++depth;
    }
    return true;
}

// Print the tree in preorder with four spaces of indentation per depth level.
void DepartmentTree::PrintTree(Department* node, int depth) const {
    if (node == nullptr) {
        return;
    }
    cout << string(static_cast<string::size_type>(depth * 4), ' ')
         << node->name << endl;
    for (Department* child : node->children) {
        PrintTree(child, depth + 1);
    }
}

// Display the full hierarchy or an empty-tree message.
void DepartmentTree::DisplayHierarchy() const {
    if (IsEmpty()) {
        cout << "Department tree is empty." << endl;
        return;
    }
    PrintTree(root, 0);
}

// Print the current node followed by each child subtree in insertion order.
void DepartmentTree::PrintPreorder(Department* node) const {
    if (node == nullptr) {
        return;
    }
    cout << node->name << endl;
    for (Department* child : node->children) {
        PrintPreorder(child);
    }
}

// Display the preorder sequence or an empty-tree message.
void DepartmentTree::DisplayPreorder() const {
    if (IsEmpty()) {
        cout << "Department tree is empty." << endl;
        return;
    }
    PrintPreorder(root);
}
