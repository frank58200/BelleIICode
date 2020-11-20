#include <iostream>
#include "TROOT.h"
#include "TString.h"
#include "math.h"

using namespace std;

void draw_2f(TChain *chain, TString variables_1, TString variables_2, Int_t bins, Double_t v1_min, Double_t v1_max, Double_t v2_min, Double_t v2_max)
{
    TString outfilename(".png");
    TString underline("_");
    TString quote(":");
    TString outbackground("CS");

    TString CS_variables_draw = variables_2 + quote + variables_1;
    TH2F *hist2d = new TH2F("hist2d", CS_variables_draw, bins, v1_min, v1_max, bins, v2_min, v2_max);
    chain->Draw(CS_variables_draw.Append(" >> hist2d"));
    TCanvas *canvas = new TCanvas;
    hist2d->Draw();
    TString imagename = variables_1 + underline + variables_2 + underline + outbackground + outfilename;
    canvas->SaveAs(imagename);
    canvas->Clear();
    // free(hist2d);
}

void draw(TChain *chain_All, TString variables, Int_t bins, Double_t v_min, Double_t v_max, TString outbackground, const char *xtitle = "", const char *ytitle = "")
{
    TString outfilename(".png");
    TString underline("_");
    // TString outbackground("CS");

    TString variables_draw = variables;

    TH1F *hist1d = new TH1F("hist1d", variables_draw, bins, v_min, v_max);
    chain_All->Draw(variables_draw.Append(" >> hist1d"));

    TCanvas *canvas = new TCanvas;
    hist1d->SetXTitle(xtitle);
    hist1d->SetYTitle(ytitle);
    hist1d->Draw();

    canvas->Modified();
    canvas->Update();
    TString imagename = variables + underline + outbackground + outfilename;
    canvas->SaveAs(imagename);
    canvas->Clear();
    hist1d = NULL;
    // free(hist1d);
}
void draw_variables_data(const char *filename, const char *decayMode)
{
    Int_t bins = 100;
    TChain *files = new TChain("variables");
    files->Add(filename);

    TString decayString(decayMode);

    // TChain *files_True = new TChain("variables");
    // files_True->Add(file_True);

    // Double_t deltaE_min = -0.2;
    // Double_t deltaE_max = 0.2;
    // TString variables_draw_deltaE("deltaE");
    // draw(files, variables_draw_deltaE, bins, deltaE_min, deltaE_max, "#DeltaE [GeV]", "Entries / (0.004 GeV)");

    // Double_t Mbc_min = 5.2;
    // Double_t Mbc_max = 5.3;
    // TString variables_draw_Mbc("Mbc");
    // draw(files, variables_draw_Mbc, bins, Mbc_min, Mbc_max, "M_{bc} [GeV/c^{2}]", "Entries / (0.001 GeV/c^{2})");

    // Double_t Jpsi_M_min = 3.092;
    // Double_t Jpsi_M_max = 3.102;
    // TString variables_draw_Jpsi_M("Jpsi_M");
    // draw(files, variables_draw_Jpsi_M, bins, Jpsi_M_min, Jpsi_M_max, "M_{J/#psi} [GeV/c^{2}]", "Entries / (0.0001 GeV/c^{2})");

    // Double_t Jpsi_InvM_min = 2.9;
    // Double_t Jpsi_InvM_max = 3.2;
    // TString variables_draw_Jpsi_InvM("Jpsi_InvM");
    // draw(files, variables_draw_Jpsi_InvM, bins, Jpsi_InvM_min, Jpsi_InvM_max, "M_{J/#psi} [GeV/c^{2}]", "Entries / (0.003 GeV/c^{2})");

    // Double_t KST_M_min = 0.800;
    // Double_t KST_M_max = 1.000;
    // TString variables_draw_KST_M("KST_M");
    // draw(files, variables_draw_KST_M, bins, KST_M_min, KST_M_max, "M_{K_{s}^{*}} [GeV/c^{2}]", "Entries / (0.002 GeV/c^{2})");

    // Double_t KST_InvM_min = 0.800;
    // Double_t KST_InvM_max = 1.000;
    // TString variables_draw_KST_InvM("KST_InvM");
    // draw(files, variables_draw_KST_InvM, bins, KST_InvM_min, KST_InvM_max, "M_{K_{s}^{*}} [GeV/c^{2}]", "Entries / (0.002 GeV/c^{2})");

    // Double_t KST_pi0_M_min = 0.11;
    // Double_t KST_pi0_M_max = 0.15;
    // TString variables_draw_KST_pi0_M("KST_pi0_M");
    // draw(files, variables_draw_KST_pi0_M, bins, KST_pi0_M_min, KST_pi0_M_max, "M_{#pi0} [GeV/c^{2}]", "Entries / (0.0004 GeV/c^{2})");

    // Double_t KST_pi0_InvM_min = 0.11;
    // Double_t KST_pi0_InvM_max = 0.15;
    // TString variables_draw_KST_pi0_InvM("KST_pi0_InvM");
    // draw(files, variables_draw_KST_pi0_InvM, bins, KST_pi0_InvM_min, KST_pi0_InvM_max, "M_{#pi0} [GeV/c^{2}]", "Entries / (0.0004 GeV/c^{2})");
    // draw_2f(files_True, variables_draw_Mbc, variables_draw_deltaE, bins, Mbc_min, Mbc_max, deltaE_min, deltaE_max);

    auto bran = files->GetListOfBranches();
    for (int i = 0; i <= bran->GetLast(); i++)
    {

        auto branches_name = (TBranch *)bran->At(i);
        auto branches_title = branches_name->GetName();
        auto branches_max = files->GetMaximum(branches_title);
        auto branches_min = files->GetMinimum(branches_title);

        if (fabs(branches_max) > 1e+7)
        {
            branches_max = 10;
        }
        if (fabs(branches_min) > 1e+7)
        {
            branches_min = 10;
        }

        // Printf("%-35s  |Max:   %25.15f  |Min:  %25.15f", branches_title, branches_max, branches_min);
        TString variables_todraw(branches_title);
        draw(files, variables_todraw, bins, branches_min, branches_max, decayString);
    }
}
