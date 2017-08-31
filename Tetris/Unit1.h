//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TLabel *Label1;
        TSpeedButton *SpeedButton1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void CopyToScreen();
        void __fastcall DrawFigura(int x,int y,int tip);
        void __fastcall RotateFigura(int Tip);
        void __fastcall ClrScr();
        int __fastcall HitTest(int X, int Y, int Tip);
        void __fastcall DrawPole();
        void __fastcall AddFiguraToPole(int x, int y, int Tip);
        bool __fastcall CreateFigura();
        TurnFiguraNaPole(int X, int Y, int Tip);
        void __fastcall MoveFigura(int Key);
        TestCompliteLine();
        void __fastcall CollapseDown(int row);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
