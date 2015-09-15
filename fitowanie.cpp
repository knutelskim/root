
/**
 * @author     Paweł Knutelski
 * @date       13.09.2015
 */

Double_t func2(Double_t *x, Double_t *par){
	return par[0]*exp(-x[0]*par[1])+TMath::Gaus(x[0], par[2], par[3]);
}

/// makro fitujące funkcję do histogramu
void fitowanie(){

	/// otwarcie pliku .root
	TFile *f = new TFile("histogram.root");

	/// otwarcie histogramu z pliku
	TH1F *hist = f->Get("histogram");

 	/// definicja funkcji fitującej
	TF1 *fitfun = new TF1("fitfun", func2, 0, 10, 4);
	// TF1 *fitfun = new TF1("fitfun", "[0]*exp(-[1]*x)+exp(-(x-[2])**2/(4*[3]))/([3]*sqrt(2*TMath::Pi()))");

	/// nazwanie parametrów
	fitfun->SetParNames("Norm", "B", "X0", "Sigma");

	/// ustalenie wielkości parametrów
	Double_t norm = hist->GetMaximum();
	fitfun->SetParameters(norm, 1, 5, 2);
 
	/// fitowanie funkcji do histogramu
	hist->Fit("fitfun");

	/// deklaracja legendy
	TLegend* leg = new TLegend(.7, .8, .9, .9);

	/// dodawanie wpisów do legendy
	leg->AddEntry(histogram, "Histogram", "l");
	leg->AddEntry(fitfun, "Fit", "l");

	/// rysowanie legendy
	leg->Draw();

	/// ustalenie opisów osi
	hist->GetXaxis()->SetTitle("M [GeV]");
	hist->GetYaxis()->SetTitle("Events");
	hist->GetXaxis()->CenterTitle();
	hist->GetYaxis()->CenterTitle();

	/// zapis histogramu do .pdf (c1 jest nazwą domyślną tworzonej kanwy)
	c1->SaveAs("fitowanie.pdf");

	fstream plik("fit.txt", std::fstream::out);

	/// zapis parametrów do pliku .txt
	plik << "NO." << "\t" << "NAME" << "\t" << "VALUE" << "\t" << "ERROR" << std::endl;
	for(int i=0; i<fitfun->GetNpar(); i++){
		plik << i << "\t" << fitfun->GetParName(i) << "\t" << fitfun->GetParameter(i) << "\t" << fitfun->GetParError(i) << std::endl;
	}
}
