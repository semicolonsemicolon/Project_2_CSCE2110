#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "../include/FacilityRecords.h"

using namespace std;

void searchFacilityByName(const vector<Facility> facilities, const string& name){
    string target = name; //normalizeString(name);
    int count = 0;

    for (const auto& fac : facilities) {
      if (fac.getName() == target) { //(normalizeString(fac.getName()) == target) { 
          fac.display();
          count++;
            
        }
    }
    cout << "Matches: " << count << endl;
}


void searchFacilityByCategory(const vector<Facility> facilities, const string& category){
    string target = category; //normalizeString(category);
    int count = 0;

    for (const auto& fac : facilities) {
      if (fac.getCategory() == target) {//(normalizeString(fac.getCategory()) == target) { 
          fac.display();
          count++;
            
        }
    }
    cout << "Matches: " << count << endl;
}
