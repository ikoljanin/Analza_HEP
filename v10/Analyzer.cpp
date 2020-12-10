#include "Analyzer.h"
using namespace std; 

//konstruktor klase
Analyzer::Analyzer ()
{
       
}

//funkcija za učitavanje i konvertiranje u root file
void Analyzer::Least_Squares()
{
	
	TCanvas *canvas;
	canvas= new TCanvas("","",1600,900);
	gStyle->SetOptFit(1111);
	// Set y-position (fraction of pad size)
	gStyle->SetStatY(0.9);                
	// Set x-position (fraction of pad size)
	gStyle->SetStatX(0.5);
	// Set width of stat-box (fraction of pad size)
	gStyle->SetStatW(0.2);                
	gStyle->SetStatH(0.2); 	
	canvas->Divide(2,1);

	canvas->GetFrame()->SetFillColor(21);
	canvas->GetFrame()->SetBorderSize(12);
	
	//a - F fit
	canvas->cd(1);
	//izmjereni podatci
	Double_t a[5]={9.8,21.2,34.5,39.9,48.5};
	Double_t a_error[5]={1.0,1.9,3.1,3.9,5.1 };
	Double_t F[5]={1.0,2.0,3.0,4.0,5.0};
	Double_t F_error[5]={0};
	
	TF1 *mass_fit;
	mass_fit=new TF1("","x/[0]",0,6);
	mass_fit->SetParameter(0,1);
	mass_fit->SetParName(0,"m");
	
	TGraphErrors *ls_graph;
	ls_graph=new TGraphErrors(5,F,a,F_error,a_error);
	ls_graph->SetTitle("");
	ls_graph->SetMarkerColor(4);
	ls_graph->SetMarkerStyle(21);
	ls_graph->Fit(mass_fit);
	ls_graph->SetTitle("a - F fit");
	ls_graph->GetXaxis()->SetTitle("F [N]");
	ls_graph->GetYaxis()->SetTitle("a [m/s^2]");
	ls_graph->Draw("AP");
	cout<<"Promatrana masa je "<<mass_fit->GetParameter(0)<<endl;
	
	//least square
	canvas->cd(2);
	double sigma_l,sigma_r;
	double y_theta_min,theta_min;//root minimumi
	double theta_min_analit;//analiticki minimum
	double suma_b=0,suma_n=0;//sume koje definiraju analitički theta_minimum
	
	TF1 *least_square;
	//m=1/theta; f(x,theta)=a=F/m; u kodu theta=x=?
	least_square=new TF1("Least_Squares","pow(([0]-[1]*x)/[2],2)+pow(([3]-[4]*x)/[5],2)+pow(([6]-[7]*x)/[8],2)+pow(([9]-[10]*x)/[11],2)+pow(([12]-[13]*x)/[14],2)",9.8,10.8);
	//definicija parametara 
	for(int i=0;i<15;i=i+3)
	{
		least_square->SetParameter(i,a[i/3]);
		least_square->SetParameter(i+1,F[i/3]);
		least_square->SetParameter(i+2,a_error[i/3]);	
	}
	least_square->SetTitle("Least square method");
	least_square->GetYaxis()->SetTitle("#chi^{2}");
	least_square->GetXaxis()->SetTitle("m^{-1} [kg^{-1}]");
	least_square->Draw();
	//minimum nacrtane funkcije određen u rootu
	theta_min=least_square->GetMinimumX();
	//y vrijednost minimuma
	y_theta_min=least_square->GetMinimum();
	//lijeva i desna greška za theta=1/m
	sigma_l=theta_min-least_square->GetX(y_theta_min+1,9,theta_min);
	sigma_r=least_square->GetX(y_theta_min+1,theta_min,11)-theta_min;
	cout<<"Po least square metodi je : \n"<<endl;
	cout<<"#Theta"<<" = "<<theta_min<<"- "<<sigma_l<<" + "<<sigma_r<<endl;
	//pogreška za masu dobije se kao greška izvedene veličine
	cout<<"m = "<<1/theta_min<<"-"<<sigma_l/pow(theta_min,2)<<" + "<<sigma_r/pow(theta_min,2)<<endl;
	
	//analiticki određen mnimum i pogreška za theta
	for(int i=0;i<5;i++)
	{
		suma_b=suma_b+F[i]*a[i]/pow(a_error[i],2);
		suma_n=suma_n+pow(F[i]/a_error[i],2);
	}
	theta_min_analit=suma_b/suma_n;
	cout<<"\n Analiticki je : \n"<<endl;
	cout<<"#Theta"<<" = "<<theta_min_analit<<" +- "<<1/sqrt(suma_n)<<endl;
	//pogreška za masu dobije se kao greška izvedene veličine
	cout<<"m = "<<1/theta_min_analit<<" +- "<<1/(sqrt(suma_n))/pow(theta_min_analit,2)<<"\n"<<endl;
	
	//linije koje označavaju theta, rheta-sgima i theta+sigma
	TLine *line1,*line2,*line3,*line4;
	//oznake postavljenih linija
	TLatex *t1,*t2,*t3 ;
	
	line1=new TLine(theta_min-sigma_l,2.1,theta_min-sigma_l,least_square->Eval(theta_min)+1);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(kDashed);
	//postavljanje oznake na prvu liniju
	t1=new TLatex(theta_min-sigma_l+0.05,2.4,"#hat{#theta}-#sigma");
	t1->SetTextAngle(90);
	t1->SetTextColor(1);
	t1->SetTextSize(0.03);
	t1->Draw();
	line1->Draw();
	
	line2=new TLine(theta_min-sigma_l,least_square->Eval(theta_min)+1,theta_min+sigma_r,least_square->Eval(theta_min)+1);
	line2->SetLineColor(kBlack);
	line2->SetLineStyle(kDashed);
	line2->Draw();
	
	line3=new TLine(theta_min+sigma_r,2.1,theta_min+sigma_r,least_square->Eval(theta_min)+1);
	line3->SetLineColor(kBlack);
	line3->SetLineStyle(kDashed);
	//postavljanje oznake na desnu liniju
	t2=new TLatex(theta_min+sigma_l-0.03,2.4,"#hat{#theta}+#sigma");
	t2->SetTextAngle(90);
	t2->SetTextColor(1);
	t2->SetTextSize(0.03);
	t2->Draw();
	line3->Draw();
	
	line4=new TLine(theta_min,2.1,theta_min,least_square->Eval(theta_min)+0.05);
	line4->SetLineColor(kBlack);
	line4->SetLineStyle(kDashed);
	//postavljanje oznake na srednju liniju
	t3=new TLatex(theta_min-0.01,2.2,"#hat{#theta}");
	t3->SetTextColor(1);
	t3->SetTextSize(0.03);
	t3->Draw();
	line4->Draw();
	
	canvas->SaveAs("Least_Squares.pdf");
}

