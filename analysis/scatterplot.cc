#include <TGraph.h>

void scatterplot() {
    TFile *file = new TFile("your_data_file_address"); // 본인 데이터파일 절대경로로 바꿀것!!!

    if (!file || file->IsZombie()) {
        cout << "Error opening the file." << endl;
        return;
    }

    double_t init_E,x,xmin,stoppingPower,xmax,ymin,ymax, y, z, dx, dy, dz, dr, delta_E, kin_E, ptot, prepx, prepy, prepz, stepLength, xp, yp, zp, track_total;
    int pdgcode, trackid, stepnum,  eventID, stepNumber, parentid;
    int sum, dEdx, mean, trackmax, posteventid;
    double steptot = 0;
    ofstream fout;
    xmin = 0.1;
    xmax = 100000.0;
    ymin = 8.;
    ymax = 32.;
    fout.open("data_of_pdglimit.txt");
    TChain *chain = new TChain("step");
    chain->Add("your_data_file_address"); // 본인 데이터파일 절대경로로 바꿀것!!!
    chain->SetBranchAddress("eventID", &eventID);
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
    chain->SetBranchAddress("track_total", &track_total);
    chain->SetBranchAddress("eventID", &eventID);
    chain->SetBranchAddress("stepnumber", &stepNumber);
    chain->SetBranchAddress("parentid", &parentid);
    chain->SetBranchAddress("stoppingPower", &stoppingPower);
    
    stepnum = 0;
    TGraph *graph = new TGraph();
    graph->SetName("momentum - dEdx scatter plot 40000event ~40GeV");
    graph->SetTitle("Scatter Plot;Momentum (MeV/c);-dE/dl (MeV/cm)");

    for (Long64_t i = 0; i < chain->GetEntries(); ++i) {
        chain->GetEntry(i);
        
        if (parentid == 0) {
            
           
            if (stepnum == 1) {
                ptot = sqrt(prepx * prepx + prepy * prepy + prepz * prepz);
                //std::cout<<delta_E<<std::endl;
                graph->SetPoint(graph->GetN(), kin_E/1000,stoppingPower/1000);
                //std::cout<<kin_E/1000<<'\t'<<-delta_E/1000<<std::endl;
                //std::cout<<kin_E/1000<<std::endl;
            }
            //graph->SetPoint(graph->GetN(), ptot, -(delta_E / stepLength)*1000);
            
            stepnum++;
            if(kin_E == 0){
                stepnum =0 ;
            }
           
        }
    }

    fout << endl;
    fout.close();

    TCanvas *canvas = new TCanvas("canvas", "TGraph Canvas");
    canvas->SetLogx();
    //canvas->SetLogy();
    graph->SetStats(1);
    graph->SetMarkerStyle(1); // 마커 스타일 설정
    graph->SetMarkerSize(0.5); // 마커 크기 설정
    graph->GetXaxis()->SetRangeUser(xmin, xmax);  // x축 범위 설정
    graph->GetYaxis()->SetRangeUser(ymin, ymax);  // x축 범위 설정
    graph->Draw("AP"); // "AP" 옵션을 사용하여 점과 선(또는 마커)을 함께 표시

    canvas->Print("scatter_Plot.png");
}
