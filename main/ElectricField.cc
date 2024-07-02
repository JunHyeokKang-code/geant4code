#include "ElectricField.hh"

ElectricField::ElectricField() : G4ElectricField() {
    // Constructor, if needed
}

ElectricField::~ElectricField() {
    // Destructor, if needed
}

void ElectricField::GetFieldValue(const G4double Point[4], G4double *E) const {
    // Define your electric field here
    E[0] = 0.0; // Electric field along x-axis
    E[1] = 0.0; // Electric field along y-axis
    E[2] = 1.0; // Electric field along z-axis
}
