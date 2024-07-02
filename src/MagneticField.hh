#ifndef MAGNETICFIELD_HH
#define MAGNETICFIELD_HH

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

class MagneticField : public G4MagneticField {
public:
    MagneticField();
    virtual ~MagneticField();

    // Inherited from G4MagneticField
    virtual void GetFieldValue(const G4double Point[4], G4double *B) const;
};

#endif // MAGNETICFIELD_HH
