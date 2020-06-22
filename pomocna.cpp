//---------------------------------------------------------------------------

#pragma hdrstop

#include "pomocna.h"


void Tacka::Crtaj(TImage *image) const {
	image->Canvas->Ellipse(x-3,y-3,x+3,y+3);
}

bool operator<(Tacka A, Tacka B) {
	if(A.x < B.x)
	  return true;
	if(A.x == B.x)
	  return A.y < B.y;
	return false;
}

bool operator==(Tacka A, Tacka B) {
  return A.x == B.x && A.y == B.y;
}

int Orijentacija(Tacka A, Tacka B, Tacka C) {

	int P = A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);
	if(P > 0)
	  return -1;
	if(P < 0)
	  return 1;
	return 0;

}


void Elipsa::Crtaj(TImage *slika) const {
	centar.Crtaj(slika);
	slika->Canvas->Brush->Style = bsClear;
	slika->Canvas->Ellipse(centar.x-a,centar.y-b,centar.x+a,centar.y+b);
	slika->Canvas->Brush->Style = bsSolid;
}

bool PresjekElipsi(Elipsa &e1, bool gornjaE1, Elipsa &e2) {

	double yPrve, tmp;
//  Provjerimo da li se prva elipsa nalazi unutar druge
	if(e1.centar.x+e1.a < e2.centar.x+e2.a &&
		e1.centar.x-e1.a > e2.centar.x-e2.a &&
		e1.centar.y+e1.b < e2.centar.y+e2.b &&
		e1.centar.y-e1.b > e2.centar.y-e2.b) return false;

//  Ako se ne nalazi unutar druge, tada provjeravamo tacke, da li se nalaze
//  unutar elipse, ako se nalazi tada su se elipse morale presjec.
//  Ako se ne nalazi, tada su sve tacke prve elipse van tacki druge elipse.
//  Posto smo u event que stavili "polovice elipsi", to gledamo tacke jedne polovice
//  i njene presjeke.
	for( int i = e1.centar.x-e1.a ; i <= e1.centar.x+e1.a;i++){
		yPrve = e1.getYTackeElipse(i, gornjaE1);

//      Pri pronalasku y tacke, ako je trazimo van granica elipse po x,
//      mogu se desiti negativni korijeni ili vrijednosti negativnog y
//      vracamo neku konstantu koja sigurno nije kao kontrolnu da preskace provjeru
//      date date.
		if(yPrve == INT_MAX) continue;

//      odredimo vrijednost za jednacinu druge elipse
		tmp =  round((pow(i-e2.centar.x,2)/pow(e2.a,2.) +
				 pow(yPrve-e2.centar.y,2)/pow(e2.b,2.))*100.
		)/100.;
//      ako je manja od 1 elipse se sijeku, tj data tacka pripada i drugoj elipsi
//      sto znaci da se presjek morao desit
		if(tmp < 1.){
			return true;
		}
	}
	return false;
}

double Udaljenost(Tacka A, Tacka B) {
  return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
