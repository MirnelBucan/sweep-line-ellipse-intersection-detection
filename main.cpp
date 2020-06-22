//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForma *Forma;
//---------------------------------------------------------------------------
__fastcall TForma::TForma(TComponent* Owner)
	: TForm(Owner)
{
	srand(time(0));
	Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	odredjen_centar = false;

}

void __fastcall TForma::SlikaMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	EditKoordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
	if(odredjen_centar) {
	   Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	   for(int i=0;i<elipse.size();i++)
		 elipse[i].Crtaj(Slika);


	   Elipsa elipsaTmp(pocetnaElipse, Tacka(X,Y) );
	   elipsaTmp.Crtaj(Slika);
	}
}

void __fastcall TForma::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(!odredjen_centar) {
		pocetnaElipse = Tacka(X,Y);
		krajnjaElipse = Tacka(X,Y);
	}
	else {
		krajnjaElipse = Tacka(X,Y);
		Elipsa novaElipsa(pocetnaElipse, krajnjaElipse);

		elipse.push_back(novaElipsa);

		Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));

		for(int i=0;i<elipse.size();i++)
		  elipse[i].Crtaj(Slika);
	}
	odredjen_centar = !odredjen_centar;

}

void __fastcall TForma::ClearClick(TObject *Sender)
{
  Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
  elipse.clear();
  odredjen_centar = false;
}


void __fastcall TForma::presjekElipsiClick(TObject *Sender)
{
  priority_queue<pair<Tacka, pair<Elipsa*, bool>>,
   vector<pair<Tacka, pair<Elipsa*, bool>>>,
	ManjePoXElipse> eventi;

  set<pair<Elipsa*,bool>, PoluelipseIspodIznad> aktivni;

  for(int i=0;i<elipse.size();i++) {
	  Tacka pocetna(Tacka(elipse[i].centar.x - elipse[i].a,elipse[i].centar.y));

	  eventi.push({pocetna,{&elipse[i],true}}); //gornji
	  aktivni.insert({&elipse[i],true});

	  eventi.push({pocetna,{&elipse[i],false}}); //donji
	  aktivni.insert({&elipse[i],false});

	  Tacka krajnja(Tacka(elipse[i].centar.x + elipse[i].a,elipse[i].centar.y));

	  eventi.push({krajnja,{&elipse[i],true}}); //gornji
	  aktivni.insert({&elipse[i],true});

	  eventi.push({krajnja,{&elipse[i],false}}); //donji
	  aktivni.insert({&elipse[i],false});


  }


  while(!eventi.empty()) {
	  auto trenutni = eventi.top();
	  eventi.pop();
//    Ako smo naisli na pocetnu tacku elipse
	  if(trenutni.first < trenutni.second.first->centar) {
		  aktivni.insert(trenutni.second);
		  auto it = aktivni.find(trenutni.second);

		  if(it != aktivni.begin()) {
			auto prethodna = *((--it)->first);
			it++;
			if(PresjekElipsi(*(it->first),it->second, prethodna)) {
				ShowMessage("Ima presjeka");
				break;
			}
		  }
		  if(it != --aktivni.end()) {
			auto naredna = *((++it)->first);
			it--;
			if(PresjekElipsi(*(it->first),it->second, naredna))  {
				ShowMessage("Ima presjeka");
				break;
			}
		  }
//    Ako smo naisli na krajnju tacku elipse
	  } else {
		 auto it = aktivni.find(trenutni.second);
		 if(it != aktivni.begin() && it != --aktivni.end()) {
			 auto prethodna = it;
			 prethodna--;
			 auto naredna = it;
			 naredna++;
			 if(PresjekElipsi(*(prethodna->first),prethodna->second,
				*(naredna->first))
			 ) {
				 ShowMessage("Ima presjeka");
				 break;
			 }
		 }
		 aktivni.erase(it);
	  }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForma::genElipseClick(TObject *Sender)
{
	int brojElipsi = EditBrojElipsi->Text.ToInt();
	if (brojElipsi < 1) {
		ShowMessage("Ne mo�ete generisati manje od jedne elipse");
	} else {
		for(int i=0; i<brojElipsi;i++){
		  elipse.push_back(
			Elipsa(
				Tacka(
					rand()%Slika->Width,
					rand()%Slika->Height
				),
				Tacka(
					rand()%Slika->Width,
					rand()%Slika->Height
				)
			)
		  );
		  elipse.back().Crtaj(Slika);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForma::testPresjekElipsiClick(TObject *Sender)
{
	int brojTestova = EditBrojTestova->Text.ToInt();
	int brojElipsi;
	if(brojTestova>0){

		for( int j=0 ; j<brojTestova ; j++){

			brojElipsi = rand()%19+1;
			ShowMessage("Pocetak testa: "+IntToStr(j+1)+", za "+IntToStr(brojElipsi)+
			" elipsi random generisanih.");

			for(int i=0; i < brojElipsi ; i++){
			  elipse.push_back(
				Elipsa(
					Tacka(
						rand()%Slika->Width,
						rand()%Slika->Height
					),
					Tacka(
						rand()%Slika->Width,
						rand()%Slika->Height
					)
				)
			  );
			  elipse.back().Crtaj(Slika);
			}
		   presjekElipsi->Click();

		   Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
		   elipse.clear();
		   ShowMessage("Kraj testa: "+IntToStr(j+1)+", elipse obrisane."+
		   "\nBroj preostalih testova: "
		   +IntToStr(brojTestova-j-1)+" ." );
		}
	} else {
	  ShowMessage("Broj testova mora biti bar 1.");
	}
}
//---------------------------------------------------------------------------

