#include <TGraph.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TF1.h>

#include <fstream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void conegraph() {
    bool logmode = true;
    std::ifstream infile("skipvals.txt");
    float num;
    unsigned daycount = 0;
    vector<float> prices;
    vector<float> days;
    while (infile >> num) {
        if (logmode) {
            if (num<0.00001)
                prices.push_back(0);
            else
                prices.push_back(TMath::Log10(num));
        } else
            prices.push_back(num);
        days.push_back(daycount++);
    }

    Float_t* xval = &days[0];
    Float_t* yval = &prices[1600];

    Float_t xmin = 10;
    Float_t xmax = days.back()+42;
    TGraph *tg = new TGraph(prices.size()-1600,xval,yval);

    // Logistic
    //TF1 *fit = new TF1("sigmoid",[&](double*x, double *p){ return p[0]/(1+TMath::Exp(-p[1]*(x[0]-p[2]))); },xmin,xmax,3);
    //fit->SetParLimits(0,5000,100000);
    //fit->SetParLimits(1,0.0001,0.01);
    //fit->SetParLimits(2,2000,4000);
    //fit->SetParameters(10000,0.1,3300);

    // Arctan
    char func[] = "A#left(#frac{2}{#pi}Arctan(k(x-x_{0}))+1#right)";
    //TF1 *fit;
    //if (!logmode) {
    //    fit = new TF1("sigmoid",[&](double*x, double *p){ return p[0]*(1+(2/TMath::Pi())*TMath::ATan(p[1]*(x[0]-p[2]))); },xmin,xmax,3);
    //    fit->SetParLimits(0,3000,20000);
    //    fit->SetParLimits(1,0.03,1);
    //    fit->SetParLimits(2,3000,5000);
    //    fit->SetParameters(10000,0.1,3300);
    //}

    // x/sqrt(1+x^2)
    TF1 *fit = new TF1("sigmoid",[&](double*x, double *p){ return p[0]*(p[1]*(x[0]-p[2])/pow(1+pow(p[1]*(x[0]-p[2]),2),0.5)+1); },xmin,xmax,3);
    fit->SetParLimits(0,5000,100000);
    fit->SetParLimits(1,0.005,0.1);
    fit->SetParLimits(2,2000,4000);
    fit->SetParameters(10000,0.1,3300);

    // x/(1+abs(x))
    //TF1 *fit = new TF1("sigmoid",[&](double*x, double *p){ return p[0]*(p[1]*(x[0]-p[2])/(1+abs(p[1]*(x[0]-p[2])))+1); },xmin,xmax,3);
    //fit->SetParLimits(0,5000,100000);
    //fit->SetParLimits(1,0.0000001,0.1);
    //fit->SetParLimits(2,2000,4000);
    //fit->SetParameters(10000,0.0001,2500);

    tg->GetYaxis()->SetTitleOffset(1.4);
    tg->SetTitle("Bitcoin value; days from launch; value (USD)");
    tg->SetLineWidth(4);
    tg->Draw();

    //if (!logmode) {
    //    tg->Fit(fit,"RL","SAME");
    //    auto A = fit->GetParameter(0);
    //    auto x0 = fit->GetParameter(2);
    //    auto k = fit->GetParameter(1);

    //    float x10 = days.back()+10;
    //    float a7days = A*(1+(2/TMath::Pi())*TMath::ATan(k*(x10-x0)));

    //    TLatex Tl;
    //    Tl.SetTextAlign(12);
    //    Tl.SetTextSize(0.04);
    //    Tl.DrawLatex(300,17500,Form("Function: %s",func));
    //    Tl.DrawLatex(300,16000,Form("Maxval (A): %.3e",fit->GetParameter(0)));
    //    Tl.DrawLatex(300,14500,Form("Transition (x_{0}): %.1f",fit->GetParameter(2)));
    //    Tl.DrawLatex(300,13000,Form("Coeff (k): %.3f",fit->GetParameter(1)));
    //    Tl.DrawLatex(300,11500,Form("chi^{2}: %.6e",fit->GetChisquare()));
    //    Tl.DrawLatex(300,10000,Form("Current day %.0f",days.back()));
    //    Tl.DrawLatex(300,8500,Form("After 7 days %.0f",a7days));
    //    cout << "Half day " << fit->GetParameter(2) << endl;
    //}
    cout << "Curr day " << days.back() << endl;

    gPad->Print("poneplot.pdf");
}
