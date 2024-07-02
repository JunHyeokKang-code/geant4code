#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1D.h>

void histogramPlot() {
    TFile *file = new TFile("input_data_file_link.root");

    if (!file || file->IsZombie()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    double_t x, y, z ,dx,dy,dz,dr,delta_E,kin_E,ptot,prepx,prepy,prepz,stepLength,xp,yp,zp,track_total; 
    int pdgcode, trackid, stepnum,eventID,stepNumber;
    int sum, dEdx,mean, trackmax,posteventid;
    double steptot = 0;
    TChain* chain = new TChain("step");
    chain->Add("< input data file link >"); // 데이터 파일에서 데이터 로드
    chain->SetBranchAddress("x", &x); // 원하는 데이터 불러오기
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
    chain->SetBranchAddress("xp", &xp);
    chain->SetBranchAddress("yp", &yp);
    chain->SetBranchAddress("zp", &zp);
    chain->SetBranchAddress("track_total",&track_total);
    chain->SetBranchAddress("eventID" ,&eventID);
    chain->SetBranchAddress("stepnumber" ,&stepNumber);
    double xmin, xmax;   
    int xbin;
    xbin = 100; //bin 수
    xmin = 0. ; // 최소값
    xmax = 10000. ; //최대값
    TH1D *hist = new TH1D("hist", "1D Histogram;Energy (GeV);Counts", xbin, xmin, xmax);

    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        if (pdgcode == 13 && trackid == 1) { // 조건 필터링
            hist->Fill(kin_E); // 히스토그램에 데이터를 추가
        }
    }

    // 큰 TCanvas를 생성하여 그래프 크기를 키웁니다.
    TCanvas *canvas = new TCanvas("canvas", "1D Histogram Canvas", 800, 600); // 캔버스 크기 설정
    hist->Draw(); // 히스토그램 그리기

    canvas->SaveAs("histogram_plot.png"); // 이미지 파일로 저장
}
