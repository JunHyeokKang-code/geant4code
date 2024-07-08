#include <TH1D.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TFile.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void elect(){
    TFile *file = new TFile("/home/kjh92/solid/opentutorials_Geant4/build/data.root");

    if (!file || file->IsZombie()) {
            cout << "Error opening the file." << endl; //파일이 디렉토리인지 아닌지 검사
            return;
        }
        std::ofstream fout;
        double_t Globaltime,x, y, z ,dx,dy,dz,dr,delta_E,postpx,postpy,postpz,kin_E,ptot,prepx,dist,prepy,prepz,stepLength,xp,yp,zp,track_total,stoppingPower,initE; 
        int pdgcode, trackid, stepnum,eventID,stepNumber,stepping,parentid,numstep;
        int parenttrack,parentpdg,parentevent,stepNumber2;
        int sum, dEdx,mean, trackmax,posteventid;
        double_t energyloss;
        double xmin = 0.;
        double xmax = 60.;
        int xbins = 100;
        double ymin = 0.;
        double ymax = 1000.;
        int ybins = 100;
        double zmin = -10000.;
       double zmax = 10000.;
        int zbins = 500;
        double Emin = 0.;
        double Emax = 100.;
        int Ebins = 150;
        double steptot = 0;
        fout.open("data_of_pdg_parentpdg.txt");
        stepnum=0;
        float margin = 0.15 ;
        numstep = 0;
        
        TChain* chain = new TChain("step");
        chain->Add("/home/kjh92/solid/opentutorials_Geant4/build/data.root"); // Add the file to the chain
        chain->SetBranchAddress("x", &x);
        chain->SetBranchAddress("y", &y);
        chain->SetBranchAddress("z", &z);
        chain->SetBranchAddress("delta_E", &delta_E);
        chain->SetBranchAddress("pdgcode", &pdgcode);
        chain->SetBranchAddress("trackid", &trackid);
        chain->SetBranchAddress("kin_E", &kin_E);
        chain->SetBranchAddress("stepLength", &stepLength);
        chain->SetBranchAddress("prepx", &prepx);
        chain->SetBranchAddress("prepy", &prepy);
        chain->SetBranchAddress("prepz", &prepz);
        chain->SetBranchAddress("track_total",&track_total);
        chain->SetBranchAddress("eventID" ,&eventID);
        chain->SetBranchAddress("stepnumber" ,&stepNumber);
        chain->SetBranchAddress("parentid", &parentid);
        chain->SetBranchAddress("stoppingPower", &stoppingPower);
        chain->SetBranchAddress("Globaltime" ,&Globaltime); 
        chain->SetBranchAddress("energyloss" ,&energyloss); 
        cout<<"chain ok"<<endl;
        TH1D* hist1 = new TH1D("hist1", "Michel electorn energy distribution", xbins, xmin, xmax);
        TH1D* hist2 = new TH1D("hist2", "Globaltime", 100, 0., 15000.);
        TH1D* hist3 = new TH1D("hist3", "gamma generate z", xbins, xmin, xmax);
        TH1D* hist4 = new TH1D("hist4", "electron generate z", xbins, xmin, xmax);
        cout<<"if start"<<endl;
        for (Long64_t i = 0; i < chain->GetEntries(); ++i) {
            chain->GetEntry(i);
            // Assuming your data has x, y, and z coordinates, you can fill the histogram like this:
            

                
                        
                
                  
                if(stepnum == 0){
                    std::cout<<kin_E/1000<<std::endl;
                    hist1->Fill(kin_E/1000);
                    //hist2->Fill(Globaltime);
                }                
                        
                            
                        
                    


                 //std::cout<<stepnum<<std::endl;       
                stepnum++;
                if(kin_E == 0){
                    stepnum = 0;
                } 
                    //cout<<stepnum<<"\t"<<kin_E<<endl;

                    
                    //cout<<eventID<<"\t"<<stepNumber<<"\t"<<pdgcode<<endl;


                    
                    //cout<<ptot<<endl;
                     
            }
        

            
cout<<"electron ok"<<endl;

        
    //TPad* pad n = new TPad("pad n", "pad n", x1,y1,x2,y2);
    fout.close();
    TCanvas* canvas = new TCanvas("canvas", "TH1D Canvas",800,600);
    TPad* pad1 = new TPad("pad1", "pad1", 0.,0.,0.99,0.99);
    //TPad* pad2 = new TPad("pad2", "pad2", 0.,0.,0.99,0.99);
    pad1->Draw();
    //pad2->Draw();
    
    canvas->cd();
    pad1->cd();
    //gPad->SetLogy();
    pad1->SetLeftMargin(margin);
    pad1->SetRightMargin(margin);
    hist1->Draw("COLZ");
    hist1->SetLineWidth(2);
    hist1->GetXaxis()->SetTitle("energy [MeV]");
    hist1->GetYaxis()->SetTitle("# of events");
    hist1->GetXaxis()->CenterTitle();
    hist1->GetYaxis()->CenterTitle();
    
    /*
    pad2->cd();
    pad2->SetLeftMargin(margin);
    pad2->SetRightMargin(margin);
    hist2->Draw("COLZ");
    hist2->GetXaxis()->SetTitle("Globaltime [ns]");
    hist2->GetYaxis()->SetTitle("# of events");
    hist2->GetXaxis()->CenterTitle();
    hist2->GetYaxis()->CenterTitle();
    */
    // canvas->cd(3);
    // hist3->Draw("COLZ");
    // hist3->GetXaxis()->SetTitle("generate point of gamma [mm]");
    // hist3->GetYaxis()->SetTitle("# of events");
    // hist3->GetXaxis()->CenterTitle();
    // hist3->GetYaxis()->CenterTitle();
    // gPad->SetLogz();
    // canvas->cd(4);
    // hist4->Draw("COLZ");
    // hist4->GetXaxis()->SetTitle("generation point of e [mm]");
    // hist4->GetYaxis()->SetTitle("# of events");
    // hist4->GetXaxis()->CenterTitle();
    // hist4->GetYaxis()->CenterTitle();

    canvas -> Print("globaltime_100MeV_10000events.png");
}


