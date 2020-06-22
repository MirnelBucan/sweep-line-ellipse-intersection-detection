//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH
#include <vector>
using namespace std;

struct Tacka {
	int x;
	int y;
	Tacka():x(0),y(0) {}
	Tacka(int X, int Y):x(X),y(Y) {}
    void Crtaj(TImage*) const;
};

bool operator==(Tacka,Tacka);
bool operator<(Tacka,Tacka);
double Udaljenost(Tacka,Tacka);

struct Elipsa {
	Tacka centar;
//  a duzina x poluose, b duzina y poluse , c udaljenost fokusa od centra po x
	double a,b,c;

	Elipsa(Tacka pocetna, Tacka krajnja){

		a = abs(pocetna.x-krajnja.x)/2.;
		b = abs(pocetna.y-krajnja.y)/2.;
		c = sqrt(abs(pow(a,2.)-pow(b,2.)));

		centar = Tacka();
		if(pocetna.x < krajnja.x){
			centar.x = pocetna.x+a;
		} else {
			centar.x = pocetna.x-a;
		}

		if(pocetna.y < krajnja.y){
			centar.y = pocetna.y+b;
		} else {
			centar.y = pocetna.y-b;
		}
	}
//  Vraca tacku elipse za proslijedjenu x koordinatu i obiljezje da li je gornja
//  tacka elipse ili donja
	double getYTackeElipse(int x, bool gornja = false){
		int y;
		double predznak = gornja ? -1.: 1.;

		double A = pow(x-centar.x,2.);
		double B = pow(a, 2.);
//      stavljeno preventivno da korijen nebi bivao negativan
//      kada uvrstimo neku tacku x , koja je van elipse
		if(A/B > 1.) return INT_MAX;
		return b * predznak*sqrt((1. - A/B)) + centar.y;
	}

	void Crtaj(TImage*) const;
};


class ManjePoXElipse{
	public:
	bool operator() (const pair<Tacka, pair<Elipsa*, bool>>& prva,
	 const pair<Tacka, pair<Elipsa*, bool>> &druga) {
		return druga.first < prva.first;
	}
};


class PoluelipseIspodIznad {
	public:
//  custom comparator za poredjenje unutar set-a
	bool operator()(const pair<Elipsa*, bool> &prvi,
	 const pair<Elipsa*, bool> &drugi) const {
		if(prvi.first == drugi.first) {
		   if(prvi.second != drugi.second)
			 return prvi.second;
		   else return false;
		}

		Tacka pocetna_prvog(prvi.first->centar.x - prvi.first->a, prvi.first->centar.y);
		Tacka pocetna_drugog(drugi.first->centar.x - drugi.first->a, drugi.first->centar.y);
//      Ako je pocetna prve elipse manja od pocetne druge
//      operator < za dvije tacke
		if(pocetna_prvog < pocetna_drugog) {
//      Ako gledamo gornju polovicu prve elipse
//      Vraca true ako je pocetna tacka druge elipse iznad centra elipse ili
//      ako je udaljenost pocetne tacke drug elipse unutar prve elipse
//      tj druga elipsa se nalazi ispod gornje krive prve elipse
//
		   if(prvi.second)
			   return pocetna_drugog.y > prvi.first->centar.y ||
				Udaljenost(pocetna_drugog,
				 Tacka(prvi.first->centar.x-prvi.first->c,prvi.first->centar.y))+
				Udaljenost(pocetna_drugog,
				 Tacka(prvi.first->centar.x+prvi.first->c,prvi.first->centar.y))
				< prvi.first->a*2;
//      Ako gledamo donju polovicu prve
//      Vraca true ako je pocetna tacka druge elipse iznad centra prve elipse i
//      ako se nalazi unutar elipse
			else
			   return  pocetna_drugog.y > prvi.first->centar.y &&
				Udaljenost(pocetna_drugog,
				 Tacka(prvi.first->centar.x-prvi.first->c,prvi.first->centar.y))+
				Udaljenost(pocetna_drugog,
				 Tacka(prvi.first->centar.x+prvi.first->c,prvi.first->centar.y))
				> prvi.first->a*2;
		}
//      ako je pocetna prva elipse manja od druge
//      gledamo invertovano od gornjeg uslova
		else {
		   if(drugi.second)
			   return !(pocetna_prvog.y > drugi.first->centar.y ||
				Udaljenost(pocetna_prvog,
				 Tacka(drugi.first->centar.x-drugi.first->c,drugi.first->centar.y))+
				Udaljenost(pocetna_prvog,
				 Tacka(drugi.first->centar.x+drugi.first->c,drugi.first->centar.y))
				 < drugi.first->a*2);
			else
			   return  !(pocetna_prvog.y > drugi.first->centar.y &&
				Udaljenost(pocetna_prvog,
				 Tacka(drugi.first->centar.x-drugi.first->c,drugi.first->centar.y))+
				Udaljenost(pocetna_prvog,
				 Tacka(drugi.first->centar.x+drugi.first->c,drugi.first->centar.y))
				  > drugi.first->a*2);

		}
	}
};


bool PresjekElipsi(Elipsa&, bool, Elipsa&);
int Orijentacija(Tacka,Tacka,Tacka);



//---------------------------------------------------------------------------
#endif
