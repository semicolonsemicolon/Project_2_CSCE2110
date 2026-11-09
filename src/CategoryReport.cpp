#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "../include/FacilityRecords.h"

using namespace std;

struct CategoryInfo {
    string category;
    int count = 0;
};

void generateCategoryReport(const vector<Facility> facilities) { 
	if (facilities.empty()) {
		cout << "There are no Facilities available.";
		return;
	}
}