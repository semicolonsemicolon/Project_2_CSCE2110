#include "../include/FacilityRecords.h"

#include <iostream>

using namespace std;

Facility::Facility(string facilityId,string facilityName,string buildingName,string facilityCategory)
    : name(facilityName),
      id(facilityId),
      building(buildingName),
      category(facilityCategory) {}

string Facility::getID() const {
    return id;
}

string Facility::getName() const {
    return name;
}

string Facility::getBuilding() const {
    return building;
}

string Facility::getCategory() const {
    return category;
}

void Facility::display() const {
    cout << id << " | " << name << " | " << building << " | " << category
         << endl;
}

