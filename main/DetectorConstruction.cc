#include "DetectorConstruction.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4int nelements;
//detectorconstruction.cc 에서는 detector의 특성,모양,구성물질 등을 직접 설정
  // Silicon is defined from NIST material database
  G4NistManager * man = G4NistManager::Instance();
  G4Material * Si = man->FindOrBuildMaterial("G4_Si");
  G4Material * alcohol = man->FindOrBuildMaterial("G4_ETHYL_ALCOHOL"); //라이브러리에 에탄올 설정 되어있음
  G4Material * basket = man->FindOrBuildMaterial("G4_GLASS_PLATE"); //라이브러리에 판유리 설정되어있음
  G4Element *element_Cu = new G4Element("Copper", "Cu", 29, 64*g/mole);//각각의 원소 정의 (이름,원소기호,원자량,밀도(몰))
  G4Material * vaccum = man->FindOrBuildMaterial("G4_Galactic");//진공 정의
  G4Element *element_N  = new G4Element("Nitrogen",   "N",  7,  14.0067*g/mole);
  G4Element *element_O  = new G4Element("Oxygen", "O",  8,  15.9994*g/mole);
  G4Element *element_C  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  G4Element *element_H  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);
  
  G4Material *PPO = new G4Material("PPO", 1.06*g/cm3, 4, kStateLiquid); //정의하는 물질의 물리적 상태 (이름,밀도,상태), Material_ 태그는 분자를 의미
  PPO -> AddElement(element_C, 15);
  PPO -> AddElement(element_H, 11);  
  PPO -> AddElement(element_N, 1);
  PPO -> AddElement(element_H, 1);      //각각의 화학식의 원자 개수
  PPO ->SetChemicalFormula("FLUOR");
  
  G4double density_bis = 1.3*g/cm3;
  nelements =2;
  G4Material* BisMSB = new G4Material("Bis-MSB",density_bis,nelements);
  //화학속성
  BisMSB->SetChemicalFormula("WLS"); //wavelength shifter
  BisMSB->AddElement(element_C,24);
  BisMSB->AddElement(element_H,22);
  // PPO 3g/L bis-MSB 30mg/L 
  /*
  G4Material *LS_material = new G4Material("LS", 0.865*g/cm3 , 2, kStateLiquid);
  LS_material -> AddMaterial(LAB, 99.77*perCent);
  LS_material -> AddMaterial(PPO, 0.23*perCent);
  */
  G4double density = 1.05*g/cm3;
  G4Material *Polystyrene = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid); //정의하는 물질의 물리적 상태 (이름,밀도,상태)
  Polystyrene -> AddElement(element_C, 8); //구성 원소 및 개수 
  Polystyrene -> AddElement(element_H, 8);
  Polystyrene ->SetChemicalFormula("(C8H8)n"); //사슬구조
  G4Material* PS_material = new G4Material("PS",density,3,kStateSolid);
  G4double BisMSB_fraction=0.03*g/(1e3*cm3*density); //0.3 mg/l bis-MSB 비율
  G4double PPO_fraction=3*g/(1e3*cm3*density);
  PS_material->AddMaterial(Polystyrene, 1 / (1.0+PPO_fraction+BisMSB_fraction) );
  PS_material->AddMaterial(PPO, PPO_fraction / (1.0+PPO_fraction+BisMSB_fraction) );
  PS_material->AddMaterial(BisMSB, BisMSB_fraction / (1.0+PPO_fraction+BisMSB_fraction) );
  G4Material *copper = new G4Material("copper", 8.96*g/cm3, 1, kStateSolid );
  copper -> AddElement(element_Cu, 1);
  G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable(); //선언 및 정의한 물질의 특성표를 열어줌
  
  // Default materials in setup.
/*
// LAB
G4int num_C;
G4int num_H;
char Name[20];
G4double density_LAB = 0.86 *g/cm3;
G4int nelements;
// LAB 물질 객체를 저장할 배열 생성
G4Material* LAB[6];
for(int i = 0; i<6; i++){
  num_C = i + 15;
  num_H = 2*(i+9)+6;
  sprintf(Name, "LAB_n=%i",i+9);
  LAB[i]
    = new G4Material(Name,density_LAB,2);//G4Material(이름(string) , 밀도(double) , 원소개수(int))
  LAB[i]->AddElement(element_C, num_C);
  LAB[i]->AddElement(element_H, num_H);
  //화학식 속성
  LAB[i]->SetChemicalFormula("AROMATIC"); // 고리구조
  //몰변환
  G4double mol_LAB = element_C->GetA()*num_C+element_H->GetA()*num_H; //getA() 는 원자질량을 반환

  G4MaterialPropertiesTable* MPT_LAB = new G4MaterialPropertiesTable(); //물리적 특성 설정(광학,광전자,핵반응,상호작용,온도 및 압력 등등)
  MPT_LAB->AddConstProperty("MOLLAB", mol_LAB/g, true); //AddConstProperty(property 이름, property 내용, create New key 여부) // 새로운 속성을 추가하는 부분
  */
// non - constant property table

/* 
// Light yield 설정 (단위 포함)
G4double lightYield = 1000.0; // 입력 입자의 에너지 손실에 따른 광자 생성 개수
G4MaterialPropertyVector* lightYieldVector = new G4MaterialPropertyVector();
lightYieldVector->InsertValues(photonEnergy, &lightYield, 1);
MPT_LAB->AddProperty("LIGHTYIELD", photonEnergy, lightYieldVector)->SetUnit("photons/MeV");

// Scintillation time constant 설정 (단위 포함)
G4double timeConstant = 1.0; // 시간 상수
G4MaterialPropertyVector* timeConstantVector = new G4MaterialPropertyVector();
timeConstantVector->InsertValues(photonEnergy, &timeConstant, 1);
MPT_LAB->AddProperty("SCINTILLATIONTIMECONSTANT", photonEnergy, timeConstantVector)->SetUnit("ns");

// Scintillation spectrum 설정

G4double scintillationSpectrum[] = { 임의 값 }; // 스펙트럼 데이터
G4MaterialPropertyVector* scintillationVector = new G4MaterialPropertyVector();
for (int i = 0; i < numEntries; ++i) {
    scintillationVector->InsertValues(photonEnergy[i], &scintillationSpectrum[i], 1);
}
MPT_LAB->AddProperty("SCINTILLATION", photonEnergy, scintillationVector, numEntries);

// 원자 번호에 따른 전자 및 광자의 반응률 설정
G4double atomicNumber[] = { 임의 값 }; // 원자 번호 데이터
G4double reactionRates[] = { 임의 값 }; // 반응률 데이터
G4MaterialPropertyVector* reactionRatesVector = new G4MaterialPropertyVector();
for (int i = 0; i < numEntries; ++i) {
    reactionRatesVector->InsertValues(atomicNumber[i], &reactionRates[i], 1);
}
MPT_LAB->AddProperty("ELECTRICITY", atomicNumber, reactionRatesVector, numEntries);

// 중성자의 산란 및 흡수 효율 설정
G4double neutronEnergy[] = { 임의 값 }; // 중성자 에너지 데이터
G4double scatteringEfficiency[] = { 임의 값 }; // 산란 효율 데이터
G4double absorptionEfficiency[] = { 임의 값 }; // 흡수 효율 데이터
G4MaterialPropertyVector* scatteringEfficiencyVector = new G4MaterialPropertyVector();
G4MaterialPropertyVector* absorptionEfficiencyVector = new G4MaterialPropertyVector();
for (int i = 0; i < numEntries; ++i) {
    scatteringEfficiencyVector->InsertValues(neutronEnergy[i], &scatteringEfficiency[i], 1);
    absorptionEfficiencyVector->InsertValues(neutronEnergy[i], &absorptionEfficiency[i], 1);
}
MPT_LAB->AddProperty("NEUTRONSCATTERING", neutronEnergy, scatteringEfficiencyVector, numEntries);
MPT_LAB->AddProperty("NEUTRONABSORPTION", neutronEnergy, absorptionEfficiencyVector, numEntries);

// 전자 및 광자의 에너지 손실 함수 설정
G4double energy[] = { 임의 값 }; // 에너지 데이터
G4double energyLoss[] = { 임의 값 }; // 에너지 손실 함수 데이터
G4MaterialPropertyVector* energyLossVector = new G4MaterialPropertyVector();
for (int i = 0; i < numEntries; ++i) {
    energyLossVector->InsertValues(energy[i], &energyLoss[i], 1);
}
MPT_LAB->AddProperty("ELECTRONENERGYLOSS", energy, energyLossVector, numEntries);

// 흡수 효율 설정
G4double absorptionEfficiency[] = { 임의 값 }; // 흡수 효율 데이터
G4MaterialPropertyVector* absorptionEfficiencyVector = new G4MaterialPropertyVector();
for (int i = 0; i < numEntries; ++i) {
    absorptionEfficiencyVector->InsertValues(photonEnergy[i], &absorptionEfficiency[i], 1);
}
MPT_LAB->AddProperty("ABSORPTIONEFFICIENCY", photonEnergy, absorptionEfficiencyVector, numEntries);


*/



// constant property table 매질의 특성중 상수인 값 설정

// Optical Properties ( 광학적 특성 )

// Refractive index (굴절율)
G4double refractiveIndex = 1.5; // 예시값
MPT->AddConstProperty("RINDEX", refractiveIndex,true);  // createNewKey를 true로 설정 ()

// Reflectivity (반사율)
G4double reflectivity = 0.9; // 예시값
MPT->AddConstProperty("REFLECTIVITY", reflectivity,true);  

// Transmittance  (투과율)
G4double transmittance = 0.8; // 예시값
MPT->AddConstProperty("TRANSMITTANCE", transmittance,true);  

// Optical Absorption length  (광학적 흡수율) 일정 거리당 흡수 비율
G4double lightabsorptionLength = 10.0 / cm; // 예시값
MPT->AddConstProperty("LIGHTABSLENGTH", lightabsorptionLength,true);  

//scintillation properties ( 광전자적 특성 )

// bulk constant (확산거리) // 1/bulkconstant 가 광전자1cm 이동당 확산거리
G4double bulkConstant = 1.0 / cm; //예시값
MPT->AddConstProperty("BULKCONSTANT", bulkConstant,true);  

// Light yield (광 수율) 입사한 에너지의 일부가 광자로 변환되는 정도
G4double lightYield = 1000.0; //예시값
MPT->AddConstProperty("LIGHTYIELD", lightYield, "photons/MeV");

// Scintillation time constant (섬광 시간상수) 원점으로 돌아올때까지 걸리는 시간
G4double timeConstant = 2.0; //예시값
MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT", timeConstant, "ns"); 


// nuclear interaction properties ( 상호작용 특성 )
// absorption length (흡수거리) //광자의 강도가 초기 값의 1/e(e는 자연로그의 밑)로 감소하는 데 필요한 평균 거리
G4double absorptionLength = 10.0*cm; //광자가 물질내에서 흡수되는 거리
MPT->AddConstProperty("ABSLENGTH", absorptionLength,true);  
  
  /*
  LAB[i]->SetMaterialPropertiesTable(MPT_LAB);
}*/
// PPO
/*G4double density_PPO = 1.06 *g/cm3;

G4Material* PPO
  = new G4Material("PPO",density_PPO,nelements = 4);
//화학속성
PPO ->SetChemicalFormula("FLUOR"); //형광

PPO->AddElement(element_C, 15);
PPO->AddElement(element_H, 11);
PPO->AddElement(element_N, 1);
PPO->AddElement(element_O, 1);

G4double mol_PPO = element_C->GetA()*15+element_H->GetA()*11+element_N->GetA()*1 + element_O->GetA()*1;

G4MaterialPropertiesTable* MPT_PPO = new G4MaterialPropertiesTable();

MPT_PPO -> AddConstProperty("MOLPPO",mol_PPO/g , true);
PPO->SetMaterialPropertiesTable(MPT_PPO);

// Bis-MSB

G4double density_bis = 1.3*g/cm3;
nelements =2;
G4Material* BisMSB = new G4Material("Bis-MSB",density_bis,nelements);
//화학속성
BisMSB->SetChemicalFormula("WLS"); //wavelength shifter

BisMSB->AddElement(element_C,24);
BisMSB->AddElement(element_H,22);

//몰 반환
G4double mol_bis = element_C->GetA()*24 + element_H->GetA()*22;
//
G4MaterialPropertiesTable* MPT_bis = new G4MaterialPropertiesTable();
//몰추가
MPT_bis->AddConstProperty("MOLbis",mol_bis/g, true);
//mpt에 추가
BisMSB->SetMaterialPropertiesTable(MPT_bis);

//LS ( RENO liquid scintillator case ( 2008 - 02 - 26 ) )

G4double density = 0.86 *g/cm3;
G4Material* LS = new G4Material("LS",density,8);
G4double PPO_fraction=1.5*g/(1e3*cm3*density); //1.5 g/l PPO 비율
G4double BisMSB_fraction=0.0003*g/(1e3*cm3*density); //0.3 mg/l bis-MSB 비율

LS->AddMaterial(LAB[0], 0.0047 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(LAB[1], 0.097 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(LAB[2], 0.3385 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(LAB[3], 0.3472 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(LAB[4], 0.2083 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(LAB[5], 0.0043 / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(PPO, PPO_fraction / (1.0+PPO_fraction+BisMSB_fraction) );
LS->AddMaterial(BisMSB, BisMSB_fraction / (1.0+PPO_fraction+BisMSB_fraction) );
*/

PS_material->SetMaterialPropertiesTable(MPT);
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;
/*
  //------------------------------------------------------
  //World Magnetic
    G4ThreeVector magneticField(0.0, 0.01, 0.0);  // Magnetic field along -y direction
    G4UniformMagField* magField = new G4UniformMagField(magneticField);

    // Set the magnetic field for the world volume
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
  // -----------------------------------------------------
  // World
  // WORLD VOLUME*/

  //G4Material* world_mat = nist -> FindOrBuildMaterial("G4_Galactic");
  //현재 구획에서는 world. 즉 내가 만든 검출기의 외부 환경의 index들을 넣어주는 부분
  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_Galactic"); //진공
  G4double world_size = 10*m;   //단위 설정

  G4Box* World =                       //사이즈 설정
    new G4Box("World",                       // its name
              10*world_size,                // half x
              10*world_size,                // half y
              10*world_size);               // half z
      
  G4LogicalVolume* logicWorld =             //logicalvolume 정의
    new G4LogicalVolume(World,         //its solid
                        vaccum,             //its material
                        "World");           //its name
//Logical Volume은 검출기 구성 요소의 형상(geometry)과 물질(material)을 정의
//geometry , material, sensitive detector 포함                                   
  G4VPhysicalVolume* physWorld =            //physicalvolume 설정
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking
//Physical Volume은 Logical Volume을 실제 공간 내의 특정 위치에 배치하는 역할
//위치와 방향, 회전및 이동 변환, 계층구조 구성

// plastic scintillator array

  G4double PSSizeX = 30*cm;
  G4double PSSizeY = 5*cm;
  G4double PSSizeZ = 30*cm;

  G4Box* PS1Solid = new G4Box("PS_1", PSSizeX/2,PSSizeY/2,PSSizeZ/2); 
  G4Box* PS2Solid = new G4Box("PS_2", PSSizeX/2,PSSizeY/2,PSSizeZ/2);
  G4Box* PS3Solid = new G4Box("PS_3", PSSizeX/2,PSSizeY/2,PSSizeZ/2);
  G4Box* PS4Solid = new G4Box("PS_4", PSSizeX/2,PSSizeY/2,PSSizeZ/2);
  G4Box* PS5Solid = new G4Box("PS_5", PSSizeX/2,PSSizeY/2,PSSizeZ/2);
  G4Box* PS6Solid = new G4Box("PS_6", PSSizeX/2,PSSizeY/2,PSSizeZ/2);
//G4Box 에서 모든 길이는 중심 기준으로하는 거리이기 때문에 원하는 size의 반수를 적용시켜야 원하는 사이즈 적용
  
  
  G4LogicalVolume* logicPS1 = new G4LogicalVolume(PS1Solid,       //its solid
						     PS_material,	//its material
						     "1stPS");		//its name
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-2.5*cm,0),	                               //at (0,0,0)
		    "1stPS",		//its name
		    logicPS1,	//its logical volume
		    physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
  G4LogicalVolume* logicPS2 = new G4LogicalVolume(PS2Solid,       //its solid
						     PS_material,	//its material
						     "2ndPS");		//its name
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-7.5*cm,0),	                               //at (0,0,0)
		    "2ndPS",		//its name
		    logicPS2,	//its logical volume
		    physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number

G4LogicalVolume* logicPS3 = new G4LogicalVolume(PS3Solid,       //its solid
						     PS_material,	//its material
						     "3rdPS");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-12.5*cm,0),	                               //at (0,0,0)
		    "3rdPS",		//its name
		    logicPS3,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
G4LogicalVolume* logicPS4 = new G4LogicalVolume(PS4Solid,       //its solid
						     PS_material,	//its material
						     "4thPS");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-17.5*cm,0),	                               //at (0,0,0)
		    "4thPS",		//its name
		    logicPS4,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
G4LogicalVolume* logicPS5 = new G4LogicalVolume(PS5Solid,       //its solid
						     PS_material,	//its material
						     "5thPS");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-22.5*cm,0),	                               //at (0,0,0)
		    "5thPS",		//its name
		    logicPS5,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
G4LogicalVolume* logicPS6 = new G4LogicalVolume(PS6Solid,       //its solid
						     PS_material,	//its material
						     "6thPS");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0,-27.5*cm,0),	                               //at (0,0,0)
		    "6thPS",		//its name
		    logicPS6,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number

  // PMT geometry array
  /*
        G4Material* PMTmat = nist->FindOrBuildMaterial("G4_Al");
        
        
        G4double innerRadius = 0. * cm;
        G4double outerRadius = 2.5 * cm;  // 직경이 5cm이므로 반지름은 2.5cm
        G4double height = 20. * cm;       // 길이 25cm
        G4double startAngle = 0. * deg;
        G4double spanningAngle = 360. * deg;
        
        
        G4Tubs* PMT1shape = new G4Tubs("1st_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
        G4Tubs* PMT2shape = new G4Tubs("2nd_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
        G4Tubs* PMT3shape = new G4Tubs("3rd_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
        G4Tubs* PMT4shape = new G4Tubs("4th_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
        G4Tubs* PMT5shape = new G4Tubs("5th_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
        G4Tubs* PMT6shape = new G4Tubs("6th_PMT", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);

        
        
        G4LogicalVolume* logicPMT1 = new G4LogicalVolume(PMT1shape,
                         PMTmat,
                         "1st_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -2.5*cm, -25*cm),
          "1stPMT",  
          logicPMT1,
          physWorld, 
          false, 
          0);
        
        
        G4LogicalVolume* logicPMT2 = new G4LogicalVolume(PMT2shape,
                         PMTmat,
                         "2nd_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -7.5*cm, 25*cm),
          "2nd_PMT",  
          logicPMT2,
          physWorld, 
          false, 
          0);
                  
        G4LogicalVolume* logicPMT3 = new G4LogicalVolume(PMT3shape,
                         PMTmat,
                         "3rd_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -12.5*cm, -25*cm),
          "3rd_PMT",  
          logicPMT3,
          physWorld, 
          false, 
          0);
                  
        G4LogicalVolume* logicPMT4 = new G4LogicalVolume(PMT4shape,
                         PMTmat,
                         "4th_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -17.5*cm, 25*cm),
          "4thPMT",  
          logicPMT4,
          physWorld, 
          false, 
          0);
                  
        G4LogicalVolume* logicPMT5 = new G4LogicalVolume(PMT5shape,
                         PMTmat,
                         "5th_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -22.5*cm, -25*cm),
          "5th_PMT",  
          logicPMT5,
          physWorld, 
          false, 
          0);
                  
        G4LogicalVolume* logicPMT6 = new G4LogicalVolume(PMT6shape,
                         PMTmat,
                         "6th_PMT");
        
        
        new G4PVPlacement(0, 
          G4ThreeVector(0, -27.5*cm, 25*cm),
          "1stPMT",  
          logicPMT6,
          physWorld, 
          false, 
          0);
  */      


/*  //LS Chamber
  G4double TargetSizeX_basket =  750*cm;
  G4double TargetSizeY_basket =  600*cm; 
  G4double TargetSizeZ_basket =  6000*cm; 

  G4Box* basketSolid = new G4Box("Basket_solid",				     //its name
				 TargetSizeX_basket/2,TargetSizeY_basket/2,TargetSizeZ_basket/2);   //its size
         */
/*
//LS Liquid
  G4double TargetSizeX =  749*cm;
  G4double TargetSizeY =  599*cm; 
  G4double TargetSizeZ =  5999*cm; 

  G4Box* targetLiquid = new G4Box("Target",				     //its name
				 TargetSizeX/2,TargetSizeY/2,TargetSizeZ/2);   //its size
  
  //G4VSolid array_2 = new G4SubtractionSolid("LSarray",basketSolid,targetLiquid,0,G4ThreeVector(0.5*cm,0,0));

  G4LogicalVolume* logicBasket = new G4LogicalVolume(basketSolid,       //its solid
						     basket,	//its material
						     "LSchamber");		//its name
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0.,0.,3005.*cm),	                               //at (0,0,0)
		    "LSchamber",		//its name
		    logicBasket,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number

  G4LogicalVolume* logicTarget = new G4LogicalVolume(targetLiquid,       //its solid
						     LS_material ,	//its material
						     "LS");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0.,0.,3005.*cm),	                               //at (0,0,0)
		    "Target",		//its name
		    logicTarget,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
        */
      
  auto visat_world = new G4VisAttributes();
  visat_world -> SetColor(G4Colour(1.,1.,1.,0.4));//R,G,B,투명도 , logical volume 에 적용
  logicWorld -> SetVisAttributes(visat_world);     
  auto visat_PS1 = new G4VisAttributes();
  visat_PS1 -> SetColor(G4Colour(0.8,0.8,0.8,0.98));//R,G,B,투명도
  logicPS1 -> SetVisAttributes(visat_PS1);
  auto visat_PS2 = new G4VisAttributes();
  visat_PS2 -> SetColor(G4Colour(0.4,0.4,0.8,0.98));//R,G,B,투명도
  logicPS2 -> SetVisAttributes(visat_PS2);
  auto visat_PS3 = new G4VisAttributes();
  visat_PS3 -> SetColor(G4Colour(0.8,0.8,0.8,0.98));//R,G,B,투명도
  logicPS3 -> SetVisAttributes(visat_PS3);
  auto visat_PS4 = new G4VisAttributes();
  visat_PS4 -> SetColor(G4Colour(0.4,0.4,0.8,0.98));//R,G,B,투명도
  logicPS4 -> SetVisAttributes(visat_PS4);
  auto visat_PS5 = new G4VisAttributes();
  visat_PS5 -> SetColor(G4Colour(0.8,0.8,0.8,0.98));//R,G,B,투명도
  logicPS5 -> SetVisAttributes(visat_PS5);
  auto visat_PS6 = new G4VisAttributes();
  visat_PS6 -> SetColor(G4Colour(0.4,0.4,0.8,0.98));//R,G,B,투명도
  logicPS6 -> SetVisAttributes(visat_PS6);
  return physWorld;

  /*auto visat_PMT1 =new G4VisAttributes();
  visat_PMT1 -> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT1->SetVisAttributes(visat_PMT1);
  auto visat_PMT2 =new G4VisAttributes();
  visat_PMT2 -> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT2->SetVisAttributes(visat_PMT2);
  auto visat_PMT3 =new G4VisAttributes();
  visat_PMT3-> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT3->SetVisAttributes(visat_PMT3);
  auto visat_PMT4 =new G4VisAttributes();
  visat_PMT4 -> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT4->SetVisAttributes(visat_PMT4);
  auto visat_PMT5 =new G4VisAttributes();
  visat_PMT5 -> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT5->SetVisAttributes(visat_PMT5);
  auto visat_PMT6 =new G4VisAttributes();
  visat_PMT6 -> SetColour(G4Colour(1., 1., 0., 0.6));
  logicPMT6->SetVisAttributes(visat_PMT6);
  return physWorld;*/


  /*auto visat_Basket = new G4VisAttributes();
  visat_Basket -> SetColor(G4Colour(0.8,0.8,0.8,0.6));//R,G,B,투명도
  logicBasket-> SetVisAttributes(visat_Basket);
  
  auto visat_Target = new G4VisAttributes();
  visat_Target -> SetColor(G4Colour(0.8,0.8,0.8,0.6));//R,G,B,투명도
  logicTarget -> SetVisAttributes(visat_Target);
  */
  /*return physWorld;*/
 
 //copper
 /*G4double TargetSizeX =  750*cm;
  G4double TargetSizeY =  600*cm; 
  G4double TargetSizeZ =  6000*cm; 

  G4Box* targetSolid = new G4Box("Target",				     //its name
				 TargetSizeX/2,TargetSizeY/2,TargetSizeZ/2);   //its size
  
  //G4VSolid array_2 = new G4SubtractionSolid("LSarray",basketSolid,targetLiquid,0,G4ThreeVector(0.5*cm,0,0));

  G4LogicalVolume* logicTarget = new G4LogicalVolume(targetSolid,       //its solid
						     copper,	//its material
						     "copper");		//its name
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(0.,0.,3000.1*cm),	                               //at (0,0,0)
		    "Target",		//its name
		    logicTarget,	//its logical volume
		   physWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number
        
  auto visat_Target = new G4VisAttributes();
  visat_Target -> SetColor(G4Colour(0.8,0.8,0.8,0.6));//R,G,B,투명도
  logicTarget -> SetVisAttributes(visat_Target);
  return physWorld;*/
}
