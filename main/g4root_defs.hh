 #ifndef g4root_defs_h
 #define g4root_defs_h
 #include "tools/histo/h1d"
 #include "tools/histo/h2d"
 #include "tools/wroot/ntuple"
 #include "G4RootAnalysisManager.hh"
 
 namespace G4Root {
 
   typedef tools::histo::h1d  G4AnaH1;
   typedef tools::histo::h2d  G4AnaH2;    
   typedef tools::wroot::ntuple  G4Ntuple; 
   typedef G4RootAnalysisManager G4AnalysisManager; 
 } 
 
 #endif