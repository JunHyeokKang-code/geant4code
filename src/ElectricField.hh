#ifndef ELECTRICFIELD_HH
#define ELECTRICFIELD_HH

#include "G4ElectricField.hh"
#include "G4ThreeVector.hh"

class ElectricField : public G4ElectricField {
public:
    ElectricField();
    virtual ~ElectricField();

    // Inherited from G4ElectricField
    virtual void GetFieldValue(const G4double Point[4], G4double *E) const;
};

#endif // ELECTRICFIELD_HH

