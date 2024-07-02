#include "MagneticField.hh"

MagneticField::MagneticField() : G4MagneticField() {
    // Constructor, if needed
}

MagneticField::~MagneticField() {
    // Destructor, if needed
}

void MagneticField::GetFieldValue(const G4double Point[4], G4double *B) const {
    // Define your magnetic field here
    B[0] = 0.0; // Magnetic field along x-axis
    B[1] = 0.0; // Magnetic field along y-axis
    B[2] = 1.0; // Magnetic field along z-axis
}
