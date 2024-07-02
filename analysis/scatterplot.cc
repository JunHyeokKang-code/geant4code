#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraph.h>

void scatterPlot() {
    TFile *file = new TFile(" input data file link ");

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
    double_t r;
    // 큰 TCanvas를 생성하여 그래프 크기를 키웁니다.
    TCanvas* canvas = new TCanvas("canvas", "Scatter Plot Canvas", 800, 600); // 캔버스 크기 설정

    TGraph* scatterPlot = new TGraph(chain->GetEntries()); // 각각의 포인트 표시
    stepnum = 0; // 초기화
    for (Long64_t i = 0; i < chain->GetEntries(); ++i) {   // for 문을 통한 엔트리 로드   
        chain->GetEntry(i);
        if(pdgcode = 13, trackid = 1){ // 조건 설정을 통한 데이터 필터링
        steptot = steptot + stepLength;
        r = sqrt(x*x + y*y+z*z);
        dx = x - xp;
        dy = y - yp;
        dz = z - zp;
        dr = sqrt(dx*dx + dy*dy + dz*dz);
        ptot = sqrt(prepx*prepx + prepy*prepy + prepz*prepz);
        //scatterPlot->SetPoint(i, ptot, -delta_E/stepLength);

        /*if(stepnum == 10){
        cout<<i<<'\t'<<eventID<<'\t'<<stepnum<<endl;
        
        }*/
        stepnum++;
        if(kin_E == 0 && stepnum>10){
            scatterPlot->SetPoint(i, ptot, -delta_E/stepLength); // 캔버스에 포인트 기록
            stepnum = 0; // stepnumber 초기화
            //cout<<z<<endl;
            }
        }
    }

    gPad->SetLogx(); // x 축 로그스케일
    gPad->SetLogy(); // y 축 로그스케일
    gStyle->SetOptStat(); // status window
    scatterPlot->SetTitle("Scatter Plot"); // 제목 설정
    scatterPlot->GetXaxis()->SetTitle("energy"); // x축 이름 설정
    scatterPlot->GetYaxis()->SetTitle("dE/dx"); // y축 이름 설정

    scatterPlot->SetMarkerStyle(1); // 마커 스타일
    scatterPlot->SetMarkerColor(kBlack); // 검은색으로 설정
    scatterPlot->SetMarkerSize(0.01); // 작은 크기
    scatterPlot->SetMarkerColorAlpha(kBlack,1.0);
    scatterPlot->Draw("AP"); // "AP"는 포인트 축을 모두 그림

    canvas->SaveAs("scatter_plot.png"); //이미지 파일로 저장
}
