#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Facility.h"

using namespace std;

struct CategoryInfo {
    string category;
    int count = 0;
};

void generateCategoryReport(const vector<Facility>) { 
        if (facilities.empty()) {
            cout << "There are no Facilities available. Total amount of facilities:
                    0/n";
            return;
        }
    
