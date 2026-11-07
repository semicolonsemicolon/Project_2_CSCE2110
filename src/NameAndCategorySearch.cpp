#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Facility.h"

using namespace std;

void searchFacilityByName(const vector<Facility>, const string& name){
    string target = normalizeString(name);
    int count = 0;

    for (const auto& fac : facilities) {
      if (normalizeString(fac.getName()) == target) { 
          fac.display();
          count++;
            
        }
    }
    count << "Matches: " << count << endl;
}

