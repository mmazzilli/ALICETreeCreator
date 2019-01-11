#include <iostream>
#include <vector>
#include <algorithm>
#include <TKey.h>
#include "tree_Ds.C"
#include "tree_Event.C"
#include "tree_Gen.C"

using namespace std;

//Commented sections is code for the additional information in the big TTree that might need to be saved to the skimmed ttree at a later point.

void skimTreeDsFromEvt(TString input="AnalysisResults.root",TString output="test.root",TString ttreeout="tree_Ds", Bool_t isMC = kFALSE, Bool_t ispp = kFALSE, Bool_t computedeltaMKK = kTRUE){

  TFile *f = TFile::Open(input.Data());
  TDirectory * dir = (TDirectory*)f->Get("PWGHF_TreeCreator");
  TTree* tree = (TTree*)dir->Get(ttreeout.Data());
  TTree* tree_ev = (TTree*)dir->Get("tree_event_char");
  TTree* tree_gen = 0;
  if(isMC){
    tree_gen = (TTree*)dir->Get(Form("%s_gen",ttreeout.Data()));
    if(!tree_gen) cout << "MC generated TTree was not enabled, skipping this." << endl;
  }

  tree_Ds t(tree);
  tree_Event t_ev(tree_ev, isMC);
  tree_Gen t_gen(tree_gen);

  int nevt = t.GetEntriesFast();
  cout << "\n\nRUNNING Ds: " << input.Data() << endl;
  TFile *fout = new TFile(output.Data(),"recreate");

  //TH1F* hEvent = 0;
  //TH2F* hNorm = 0;
  //for(auto k : *dir->GetListOfKeys()) {
  //  TKey *key = static_cast<TKey*>(k);
  //  TClass *cl = gROOT->GetClass(key->GetClassName());
  //  if (cl->InheritsFrom("TH1F")){
  //    TH1F* hEvent=(TH1F*)key->ReadObj();
  //    hEvent->Write();
  //  } else if (cl->InheritsFrom("TH2F")){
  //    TH2F* hNorm=(TH2F*)key->ReadObj();
  //    hNorm->Write();
  //  }
  //}

  TTree* fTreeEventCharML = new TTree("fTreeEventChar","fTreeEventChar");
  TTree* fTreeDsML = new TTree("fTreeDsFlagged","fTreeDsFlagged");
  TTree* fTreeDsGenML;
  if(isMC && tree_gen) fTreeDsGenML = new TTree("fTreeDsGenFlagged","fTreeDsGenFlagged");

  float centrality_ML, z_vtx_reco_ML, z_vtx_gen_ML;
  int n_vtx_contributors_ML, n_tracks_ML, is_ev_rej_ML, run_number_ML;

  if(!ispp) fTreeEventCharML->Branch("centrality_ML",&centrality_ML,"centrality_ML/F");
  fTreeEventCharML->Branch("z_vtx_reco_ML",&z_vtx_reco_ML,"z_vtx_reco_ML/F");
  //fTreeEventCharML->Branch("n_vtx_contributors_ML",&n_vtx_contributors_ML,"n_vtx_contributors_ML/I");
  //fTreeEventCharML->Branch("n_tracks_ML",&n_tracks_ML,"n_tracks_ML/I");
  fTreeEventCharML->Branch("is_ev_rej_ML",&is_ev_rej_ML,"is_ev_rej_ML/I");
  //fTreeEventCharML->Branch("run_number_ML",&run_number_ML,"run_number_ML/I");
  //if(isMC) fTreeEventCharML->Branch("z_vtx_gen_ML",&z_vtx_gen_ML,"z_vtx_gen_ML/F");

  float inv_mass_ML, pt_cand_ML, d_len_ML, d_len_xy_ML, norm_dl_xy_ML, cos_p_ML, cos_p_xy_ML, imp_par_xy_ML, sig_vert_ML, mass_KK_ML, cos_PiDs_ML, cos_PiKPhi_3_ML, max_norm_d0d0exp_ML;
  float cand_type_ML, y_cand_ML, eta_cand_ML, phi_cand_ML;
  float imp_par_prong0_ML, imp_par_prong1_ML, imp_par_prong2_ML, p_prong0_ML, p_prong1_ML, p_prong2_ML, pt_prong0_ML, pt_prong1_ML, pt_prong2_ML, eta_prong0_ML, eta_prong1_ML, eta_prong2_ML, phi_prong0_ML, phi_prong1_ML, phi_prong2_ML;
  float nTPCcls_prong0_ML, nTPCclspid_prong0_ML, nTPCcrossrow_prong0_ML, chi2perndf_prong0_ML, nITScls_prong0_ML, ITSclsmap_prong0_ML, nTPCcls_prong1_ML, nTPCclspid_prong1_ML, nTPCcrossrow_prong1_ML, chi2perndf_prong1_ML, nITScls_prong1_ML, ITSclsmap_prong1_ML, nTPCcls_prong2_ML, nTPCclspid_prong2_ML, nTPCcrossrow_prong2_ML, chi2perndf_prong2_ML, nITScls_prong2_ML, ITSclsmap_prong2_ML;
  float nsigTPC_Pi_0_ML, nsigTPC_K_0_ML, nsigTOF_Pi_0_ML, nsigTOF_K_0_ML, dEdxTPC_0_ML, ToF_0_ML, pTPC_prong0_ML, pTOF_prong0_ML, trlen_prong0_ML, start_time_res_prong0_ML, nsigTPC_Pi_1_ML, nsigTPC_K_1_ML, nsigTOF_Pi_1_ML, nsigTOF_K_1_ML, dEdxTPC_1_ML, ToF_1_ML, pTPC_prong1_ML, pTOF_prong1_ML, trlen_prong1_ML, start_time_res_prong1_ML, nsigTPC_Pi_2_ML, nsigTPC_K_2_ML, nsigTOF_Pi_2_ML, nsigTOF_K_2_ML, dEdxTPC_2_ML, ToF_2_ML, pTPC_prong2_ML, pTOF_prong2_ML, trlen_prong2_ML, start_time_res_prong2_ML;

  fTreeDsML->Branch("inv_mass_ML",&inv_mass_ML,"inv_mass_ML/F");
  fTreeDsML->Branch("pt_cand_ML",&pt_cand_ML,"pt_cand_ML/F");
  fTreeDsML->Branch("d_len_ML",&d_len_ML,"d_len_ML/F");
  fTreeDsML->Branch("d_len_xy_ML",&d_len_xy_ML,"d_len_xy_ML/F");
  fTreeDsML->Branch("norm_dl_xy_ML",&norm_dl_xy_ML,"norm_dl_xy_ML/F");
  fTreeDsML->Branch("cos_p_ML",&cos_p_ML,"cos_p_ML/F");
  fTreeDsML->Branch("cos_p_xy_ML",&cos_p_xy_ML,"cos_p_xy_ML/F");
  fTreeDsML->Branch("imp_par_xy_ML",&imp_par_xy_ML,"imp_par_xy_ML/F");
  fTreeDsML->Branch("pt_prong0_ML",&pt_prong0_ML,"pt_prong0_ML/F");
  fTreeDsML->Branch("pt_prong1_ML",&pt_prong1_ML,"pt_prong1_ML/F");
  fTreeDsML->Branch("pt_prong2_ML",&pt_prong2_ML,"pt_prong2_ML/F");
  fTreeDsML->Branch("sig_vert_ML",&sig_vert_ML,"sig_vert_ML/F");
  fTreeDsML->Branch("mass_KK_ML",&mass_KK_ML,"mass_KK_ML/F");
  fTreeDsML->Branch("cos_PiDs_ML",&cos_PiDs_ML,"cos_PiDs_ML/F");
  fTreeDsML->Branch("cos_PiKPhi_3_ML",&cos_PiKPhi_3_ML,"cos_PiKPhi_3_ML/F");
  fTreeDsML->Branch("max_norm_d0d0exp_ML",&max_norm_d0d0exp_ML,"max_norm_d0d0exp_ML/F");

  fTreeDsML->Branch("cand_type_ML",&cand_type_ML,"cand_type_ML/F");
  fTreeDsML->Branch("y_cand_ML",&y_cand_ML,"y_cand_ML/F");
  fTreeDsML->Branch("eta_cand_ML",&eta_cand_ML,"eta_cand_ML/F");
  fTreeDsML->Branch("phi_cand_ML",&phi_cand_ML,"phi_cand_ML/F");

  fTreeDsML->Branch("imp_par_prong0_ML",&imp_par_prong0_ML,"imp_par_prong0_ML/F");
  fTreeDsML->Branch("imp_par_prong1_ML",&imp_par_prong1_ML,"imp_par_prong1_ML/F");
  fTreeDsML->Branch("imp_par_prong2_ML",&imp_par_prong2_ML,"imp_par_prong2_ML/F");
  fTreeDsML->Branch("pt_prong0_ML",&pt_prong0_ML,"pt_prong0_ML/F");
  fTreeDsML->Branch("pt_prong1_ML",&pt_prong1_ML,"pt_prong1_ML/F");
  fTreeDsML->Branch("pt_prong2_ML",&pt_prong2_ML,"pt_prong2_ML/F");
  fTreeDsML->Branch("p_prong0_ML",&p_prong0_ML,"p_prong0_ML/F");
  fTreeDsML->Branch("p_prong1_ML",&p_prong1_ML,"p_prong1_ML/F");
  fTreeDsML->Branch("p_prong2_ML",&p_prong2_ML,"p_prong2_ML/F");
  fTreeDsML->Branch("eta_prong0_ML",&eta_prong0_ML,"eta_prong0_ML/F");
  fTreeDsML->Branch("eta_prong1_ML",&eta_prong1_ML,"eta_prong1_ML/F");
  fTreeDsML->Branch("eta_prong2_ML",&eta_prong2_ML,"eta_prong2_ML/F");
  fTreeDsML->Branch("phi_prong0_ML",&phi_prong0_ML,"phi_prong0_ML/F");
  fTreeDsML->Branch("phi_prong1_ML",&phi_prong1_ML,"phi_prong1_ML/F");
  fTreeDsML->Branch("phi_prong2_ML",&phi_prong2_ML,"phi_prong2_ML/F");
    
  fTreeDsML->Branch("nTPCcls_prong0_ML",&nTPCcls_prong0_ML,"nTPCcls_prong0_ML/F");
  fTreeDsML->Branch("nTPCclspid_prong0_ML",&nTPCclspid_prong0_ML,"nTPCclspid_prong0_ML/F");
  fTreeDsML->Branch("nTPCcrossrow_prong0_ML",&nTPCcrossrow_prong0_ML,"nTPCcrossrow_prong0_ML/F");
  fTreeDsML->Branch("chi2perndf_prong0_ML",&chi2perndf_prong0_ML,"chi2perndf_prong0_ML/F");
  fTreeDsML->Branch("nITScls_prong0_ML",&nITScls_prong0_ML,"nITScls_prong0_ML/F");
  fTreeDsML->Branch("ITSclsmap_prong0_ML",&ITSclsmap_prong0_ML,"ITSclsmap_prong0_ML/F");
  fTreeDsML->Branch("nTPCcls_prong1_ML",&nTPCcls_prong1_ML,"nTPCcls_prong1_ML/F");
  fTreeDsML->Branch("nTPCclspid_prong1_ML",&nTPCclspid_prong1_ML,"nTPCclspid_prong1_ML/F");
  fTreeDsML->Branch("nTPCcrossrow_prong1_ML",&nTPCcrossrow_prong1_ML,"nTPCcrossrow_prong1_ML/F");
  fTreeDsML->Branch("chi2perndf_prong1_ML",&chi2perndf_prong1_ML,"chi2perndf_prong1_ML/F");
  fTreeDsML->Branch("nITScls_prong1_ML",&nITScls_prong1_ML,"nITScls_prong1_ML/F");
  fTreeDsML->Branch("ITSclsmap_prong1_ML",&ITSclsmap_prong1_ML,"ITSclsmap_prong1_ML/F");
  fTreeDsML->Branch("nTPCcls_prong2_ML",&nTPCcls_prong2_ML,"nTPCcls_prong2_ML/F");
  fTreeDsML->Branch("nTPCclspid_prong2_ML",&nTPCclspid_prong2_ML,"nTPCclspid_prong2_ML/F");
  fTreeDsML->Branch("nTPCcrossrow_prong2_ML",&nTPCcrossrow_prong2_ML,"nTPCcrossrow_prong2_ML/F");
  fTreeDsML->Branch("chi2perndf_prong2_ML",&chi2perndf_prong2_ML,"chi2perndf_prong2_ML/F");
  fTreeDsML->Branch("nITScls_prong2_ML",&nITScls_prong2_ML,"nITScls_prong2_ML/F");
  fTreeDsML->Branch("ITSclsmap_prong2_ML",&ITSclsmap_prong2_ML,"ITSclsmap_prong2_ML/F");

  fTreeDsML->Branch("nsigTPC_Pi_0_ML",&nsigTPC_Pi_0_ML,"nsigTPC_Pi_0_ML/F");
  fTreeDsML->Branch("nsigTPC_K_0_ML",&nsigTPC_K_0_ML,"nsigTPC_K_0_ML/F");
  fTreeDsML->Branch("nsigTOF_Pi_0_ML",&nsigTOF_Pi_0_ML,"nsigTOF_Pi_0_ML/F");
  fTreeDsML->Branch("nsigTOF_K_0_ML",&nsigTOF_K_0_ML,"nsigTOF_K_0_ML/F");
  fTreeDsML->Branch("dEdxTPC_0_ML",&dEdxTPC_0_ML,"dEdxTPC_0_ML/F");
  fTreeDsML->Branch("ToF_0_ML",&ToF_0_ML,"ToF_0_ML/F");
  fTreeDsML->Branch("pTPC_prong0_ML",&pTPC_prong0_ML,"pTPC_prong0_ML/F");
  fTreeDsML->Branch("pTOF_prong0_ML",&pTOF_prong0_ML,"pTOF_prong0_ML/F");
  fTreeDsML->Branch("trlen_prong0_ML",&trlen_prong0_ML,"trlen_prong0_ML/F");
  fTreeDsML->Branch("start_time_res_prong0_ML",&start_time_res_prong0_ML,"start_time_res_prong0_ML/F");
  fTreeDsML->Branch("nsigTPC_Pi_1_ML",&nsigTPC_Pi_1_ML,"nsigTPC_Pi_1_ML/F");
  fTreeDsML->Branch("nsigTPC_K_1_ML",&nsigTPC_K_1_ML,"nsigTPC_K_1_ML/F");
  fTreeDsML->Branch("nsigTOF_Pi_1_ML",&nsigTOF_Pi_1_ML,"nsigTOF_Pi_1_ML/F");
  fTreeDsML->Branch("nsigTOF_K_1_ML",&nsigTOF_K_1_ML,"nsigTOF_K_1_ML/F");
  fTreeDsML->Branch("dEdxTPC_1_ML",&dEdxTPC_1_ML,"dEdxTPC_1_ML/F");
  fTreeDsML->Branch("ToF_1_ML",&ToF_1_ML,"ToF_1_ML/F");
  fTreeDsML->Branch("pTPC_prong1_ML",&pTPC_prong1_ML,"pTPC_prong1_ML/F");
  fTreeDsML->Branch("pTOF_prong1_ML",&pTOF_prong1_ML,"pTOF_prong1_ML/F");
  fTreeDsML->Branch("trlen_prong1_ML",&trlen_prong1_ML,"trlen_prong1_ML/F");
  fTreeDsML->Branch("start_time_res_prong1_ML",&start_time_res_prong1_ML,"start_time_res_prong1_ML/F");
  fTreeDsML->Branch("nsigTPC_Pi_2_ML",&nsigTPC_Pi_2_ML,"nsigTPC_Pi_2_ML/F");
  fTreeDsML->Branch("nsigTPC_K_2_ML",&nsigTPC_K_2_ML,"nsigTPC_K_2_ML/F");
  fTreeDsML->Branch("nsigTOF_Pi_2_ML",&nsigTOF_Pi_2_ML,"nsigTOF_Pi_2_ML/F");
  fTreeDsML->Branch("nsigTOF_K_2_ML",&nsigTOF_K_2_ML,"nsigTOF_K_2_ML/F");
  fTreeDsML->Branch("dEdxTPC_2_ML",&dEdxTPC_2_ML,"dEdxTPC_2_ML/F");
  fTreeDsML->Branch("ToF_2_ML",&ToF_2_ML,"ToF_2_ML/F");
  fTreeDsML->Branch("pTPC_prong2_ML",&pTPC_prong2_ML,"pTPC_prong2_ML/F");
  fTreeDsML->Branch("pTOF_prong2_ML",&pTOF_prong2_ML,"pTOF_prong2_ML/F");
  fTreeDsML->Branch("trlen_prong2_ML",&trlen_prong2_ML,"trlen_prong2_ML/F");
  fTreeDsML->Branch("start_time_res_prong2_ML",&start_time_res_prong2_ML,"start_time_res_prong2_ML/F");
  
  float cand_type_gen_ML, pt_cand_gen_ML, y_cand_gen_ML, eta_cand_gen_ML, phi_cand_gen_ML, forCand_z_vtx_gen_ML;
  bool dau_in_acc_gen_ML;

  if(isMC && tree_gen){
    fTreeDsGenML->Branch("cand_type_gen_ML",&cand_type_gen_ML,"cand_type_gen_ML/F");
    fTreeDsGenML->Branch("pt_cand_gen_ML",&pt_cand_gen_ML,"pt_cand_gen_ML/F");
    fTreeDsGenML->Branch("y_cand_gen_ML",&y_cand_gen_ML,"y_cand_gen_ML/F");
    //fTreeDsGenML->Branch("eta_cand_gen_ML",&eta_cand_gen_ML,"eta_cand_gen_ML/F");
    //fTreeDsGenML->Branch("phi_cand_gen_ML",&phi_cand_gen_ML,"phi_cand_gen_ML/F");
    fTreeDsGenML->Branch("dau_in_acc_gen_ML",&dau_in_acc_gen_ML,"dau_in_acc_gen_ML/O");
    fTreeDsGenML->Branch("z_vtx_gen_ML",&forCand_z_vtx_gen_ML,"z_vtx_gen_ML/F");
  }
  
  std::cout<<"nevents (Ds) "<<nevt<<std::endl;
  for(Long64_t jentry=0; jentry<nevt;jentry++){
    t.GetEntry(jentry);
    t_ev.GetEntry(jentry);
    t_gen.GetEntry(jentry);
    if(jentry%25000==0) cout<<jentry<<endl;
      
    if(!ispp) centrality_ML = t_ev.centrality;
    z_vtx_reco_ML = t_ev.z_vtx_reco;
    //n_vtx_contributors_ML = t_ev.n_vtx_contributors;
    //n_tracks_ML = t_ev.n_tracks;
    is_ev_rej_ML = t_ev.is_ev_rej;
    //run_number_ML = t_ev.run_number;
    //if(isMC) z_vtx_gen_ML = t_ev.z_vtx_gen;
    fTreeEventCharML->Fill();
    
    if(is_ev_rej_ML!=0) continue;

    for(int icand = 0; icand < t.n_cand; icand++){ 
      inv_mass_ML=t.inv_mass -> at(icand);
      pt_cand_ML=t.pt_cand -> at(icand);
      d_len_ML=t.d_len -> at(icand);
      d_len_xy_ML=t.d_len_xy -> at(icand);
      norm_dl_xy_ML=t.norm_dl_xy -> at(icand);
      cos_p_ML=t.cos_p -> at(icand);
      cos_p_xy_ML=t.cos_p_xy -> at(icand);
      imp_par_xy_ML=t.imp_par_xy -> at(icand);
      sig_vert_ML=t.sig_vert -> at(icand);
      if(computedeltaMKK) mass_KK_ML=TMath::Abs(1.019455-t.mass_KK -> at(icand));
      else mass_KK_ML=t.mass_KK -> at(icand);
      cos_PiDs_ML=t.cos_PiDs -> at(icand);
      cos_PiKPhi_3_ML=t.cos_PiKPhi_3 -> at(icand);
      max_norm_d0d0exp_ML=t.max_norm_d0d0exp -> at(icand);
        
      cand_type_ML=t.cand_type -> at(icand);
      y_cand_ML=t.y_cand -> at(icand);
      eta_cand_ML=t.eta_cand -> at(icand);
      phi_cand_ML=t.phi_cand -> at(icand);

      pt_prong0_ML=t.pt_prong0 -> at(icand);
      pt_prong1_ML=t.pt_prong1 -> at(icand);
      pt_prong2_ML=t.pt_prong2 -> at(icand);
      imp_par_prong0_ML=t.imp_par_prong0 -> at(icand);
      imp_par_prong1_ML=t.imp_par_prong1 -> at(icand);
      imp_par_prong2_ML=t.imp_par_prong2 -> at(icand);
      p_prong0_ML=t.p_prong0 -> at(icand);
      p_prong1_ML=t.p_prong1 -> at(icand);
      p_prong2_ML=t.p_prong2 -> at(icand);
      eta_prong0_ML=t.eta_prong0 -> at(icand);
      eta_prong1_ML=t.eta_prong1 -> at(icand);
      eta_prong2_ML=t.eta_prong2 -> at(icand);
      phi_prong0_ML=t.phi_prong0 -> at(icand);
      phi_prong1_ML=t.phi_prong1 -> at(icand);
      phi_prong2_ML=t.phi_prong2 -> at(icand);

      nTPCcls_prong0_ML=t.nTPCcls_prong0 -> at(icand);
      nTPCclspid_prong0_ML=t.nTPCclspid_prong0 -> at(icand);
      nTPCcrossrow_prong0_ML=t.nTPCcrossrow_prong0 -> at(icand);
      chi2perndf_prong0_ML=t.chi2perndf_prong0 -> at(icand);
      nITScls_prong0_ML=t.nITScls_prong0 -> at(icand);
      ITSclsmap_prong0_ML=t.ITSclsmap_prong0 -> at(icand);
      nTPCcls_prong1_ML=t.nTPCcls_prong1 -> at(icand);
      nTPCclspid_prong1_ML=t.nTPCclspid_prong1 -> at(icand);
      nTPCcrossrow_prong1_ML=t.nTPCcrossrow_prong1 -> at(icand);
      chi2perndf_prong1_ML=t.chi2perndf_prong1 -> at(icand);
      nITScls_prong1_ML=t.nITScls_prong1 -> at(icand);
      ITSclsmap_prong1_ML=t.ITSclsmap_prong1 -> at(icand);
      nTPCcls_prong2_ML=t.nTPCcls_prong2 -> at(icand);
      nTPCclspid_prong2_ML=t.nTPCclspid_prong2 -> at(icand);
      nTPCcrossrow_prong2_ML=t.nTPCcrossrow_prong2 -> at(icand);
      chi2perndf_prong2_ML=t.chi2perndf_prong2 -> at(icand);
      nITScls_prong2_ML=t.nITScls_prong2 -> at(icand);
      ITSclsmap_prong2_ML=t.ITSclsmap_prong2 -> at(icand);

      nsigTPC_Pi_0_ML=t.nsigTPC_Pi_0 -> at(icand);
      nsigTPC_K_0_ML=t.nsigTPC_K_0 -> at(icand);
      nsigTOF_Pi_0_ML=t.nsigTOF_Pi_0 -> at(icand);
      nsigTOF_K_0_ML=t.nsigTOF_K_0 -> at(icand);
      dEdxTPC_0_ML=t.dEdxTPC_0 -> at(icand);
      ToF_0_ML=t.ToF_0 -> at(icand);
      pTPC_prong0_ML=t.pTPC_prong0 -> at(icand);
      pTOF_prong0_ML=t.pTOF_prong0 -> at(icand);
      trlen_prong0_ML=t.trlen_prong0 -> at(icand);
      start_time_res_prong0_ML=t.start_time_res_prong0 -> at(icand);
      nsigTPC_Pi_1_ML=t.nsigTPC_Pi_1 -> at(icand);
      nsigTPC_K_1_ML=t.nsigTPC_K_1 -> at(icand);
      nsigTOF_Pi_1_ML=t.nsigTOF_Pi_1 -> at(icand);
      nsigTOF_K_1_ML=t.nsigTOF_K_1 -> at(icand);
      dEdxTPC_1_ML=t.dEdxTPC_1 -> at(icand);
      ToF_1_ML=t.ToF_1 -> at(icand);
      pTPC_prong1_ML=t.pTPC_prong1 -> at(icand);
      pTOF_prong1_ML=t.pTOF_prong1 -> at(icand);
      trlen_prong1_ML=t.trlen_prong1 -> at(icand);
      start_time_res_prong1_ML=t.start_time_res_prong1 -> at(icand);
      nsigTPC_Pi_2_ML=t.nsigTPC_Pi_2 -> at(icand);
      nsigTPC_K_2_ML=t.nsigTPC_K_2 -> at(icand);
      nsigTOF_Pi_2_ML=t.nsigTOF_Pi_2 -> at(icand);
      nsigTOF_K_2_ML=t.nsigTOF_K_2 -> at(icand);
      dEdxTPC_2_ML=t.dEdxTPC_2 -> at(icand);
      ToF_2_ML=t.ToF_2 -> at(icand);
      pTPC_prong2_ML=t.pTPC_prong2 -> at(icand);
      pTOF_prong2_ML=t.pTOF_prong2 -> at(icand);
      trlen_prong2_ML=t.trlen_prong2 -> at(icand);
      start_time_res_prong2_ML=t.start_time_res_prong2 -> at(icand);

      fTreeDsML->Fill();
    }

    int ncandgen = 0;
    if(isMC && tree_gen){
      ncandgen = t_gen.n_cand;
      forCand_z_vtx_gen_ML = t_ev.z_vtx_gen;
    }
    for(int icand = 0; icand < ncandgen; icand++){
      cand_type_gen_ML=t_gen.cand_type -> at(icand);
      pt_cand_gen_ML=t_gen.pt_cand -> at(icand);
      y_cand_gen_ML=t_gen.y_cand -> at(icand);
      //eta_cand_gen_ML=t_gen.eta_cand -> at(icand);
      //phi_cand_gen_ML=t_gen.phi_cand -> at(icand);
      dau_in_acc_gen_ML=t_gen.dau_in_acc -> at(icand);

      fTreeDsGenML->Fill();
    }
  
  }
  fout->Write();
  fout->Close();
}


int main(int argc, char *argv[])
{
  if((argc != 6))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 6)
    skimTreeDsFromEvt(argv[1],argv[2],argv[3],atoi(argv[4]),atoi(argv[5]));
  return 0;
}