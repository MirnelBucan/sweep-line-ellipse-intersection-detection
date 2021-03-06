//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "pomocna.h"
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <set>

using namespace std;
//---------------------------------------------------------------------------
class TForma : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TLabel *LabelKoordinate;
	TEdit *EditKoordinate;
	TButton *Clear;
	TButton *presjekElipsi;
	TEdit *EditBrojElipsi;
	TLabel *labelBrojElipsi;
	TButton *genElipse;
	TButton *testPresjekElipsi;
	TEdit *EditBrojTestova;
	TLabel *LabelBrojTestova;
	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall presjekElipsiClick(TObject *Sender);
	void __fastcall genElipseClick(TObject *Sender);
	void __fastcall testPresjekElipsiClick(TObject *Sender);


private:
	vector<Elipsa> elipse;
	bool odredjen_centar;
	Tacka centar;
	Tacka pocetnaElipse,krajnjaElipse;
public:
	__fastcall TForma(TComponent* Owner);
};


//---------------------------------------------------------------------------
extern PACKAGE TForma *Forma;
//---------------------------------------------------------------------------
#endif
