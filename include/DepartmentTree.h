#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>

using namespace std;

// Store one department and its links to its parent and children.
struct Department {
    Department(const string& departmentName, Department* parentDepartment);

    string name;
    Department* parent;
    vector<Department*> children;
};

// Manage the department hierarchy.
class DepartmentTree {
private:
    Department* root;

    Department* FindNode(Department* node, const string& name) const;
    void DeleteTree(Department* node);
    void PrintTree(Department* node, int depth) const;
    void PrintPreorder(Department* node) const;

public:
    DepartmentTree();
    ~DepartmentTree();

    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    // Report whether the tree is empty.
    bool IsEmpty() const;
    // Load and validate departments from a pipe-separated file.
    void LoadFromFile(const string& filename);
    // Add a department as the root or as a child of an existing department.
    bool AddDepartment(const string& name,const string& parentName,string& error);
    // Find a department and return its parent, child count, and depth.
    bool SearchDepartment(const string& name,string& departmentName,string& parentName,int& childCount,int& depth) const;
    // Display the hierarchy with indentation.
    void DisplayHierarchy() const;
    // Display the unindented preorder traversal.
    void DisplayPreorder() const;
};

#endif