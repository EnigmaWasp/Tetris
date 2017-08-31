//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int PoleW,PoleH;
Graphics::TBitmap*Buffer;
Graphics::TBitmap*Block;
TPoint BlockPos;
int BlockType;
int NextBlock;
int Pole[10][18];
int Score;
int FiguraData[7][16]=
        {
        0,0,0,0,
        1,1,1,0,
        1,0,0,0,
        0,0,0,0,

        0,0,0,0,
        0,1,1,1,
        0,0,0,1,
        0,0,0,0,

        0,0,0,0,
        0,1,1,0,
        1,1,0,0,
        0,0,0,0,

        0,0,0,0,
        1,1,0,0,
        0,1,1,0,
        0,0,0,0,

        0,0,0,0,
        0,1,0,0,
        1,1,1,0,
        0,0,0,0,

        0,0,0,0,
        0,0,0,0,
        1,1,1,1,
        0,0,0,0,

        0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0,
        };
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Score=0;
randomize();
PoleW=300;PoleH=540;
for(int j=0;j<18;j++)
        for(int i=0;i<10;i++)
        Pole[i][j]=0;
        NextBlock=random(7);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Buffer=new Graphics::TBitmap();
Buffer->Width =PoleW;
Buffer->Height=PoleH;
Block=new Graphics::TBitmap();
Block->Width=30;Block->Height=30;
Block->LoadFromFile("Block.bmp");
CreateFigura();
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------


void TForm1::CopyToScreen()
{
  Canvas->Draw(0,0,Buffer);      
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
ClrScr();
DrawPole();
DrawFigura(BlockPos.x,BlockPos.y,BlockType);
CopyToScreen();
int Tx=BlockPos.x,Ty=BlockPos.y;
Ty++;
if(HitTest(Tx,Ty,BlockType))
        {
        AddFiguraToPole(BlockPos.x,BlockPos.y,BlockType);

        if(!CreateFigura())
                {
                Timer1->Enabled=false;
                ShowMessage("Игра окончена");
                }
        }
        else
        {
        BlockPos=Point(Tx,Ty);
        }
TestCompliteLine();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawFigura(int x,int y,int tip)
{
   for(int j=0;j<4;j++)
        for(int i=0;i<4;i++)
        {
        if(FiguraData[tip][j*4+i]!=0)Buffer->Canvas->Draw(x*30+i*30,y*30+j*30,Block);
        }


}

void __fastcall TForm1::RotateFigura(int Tip)
{
int PosX=3;
int PosY=0;
        int Temp[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int j=0;j<4;j++,PosX--,PosY=0)
                for(int i=0;i<4;i++,PosY++)
                {
                Temp[PosY*4+PosX]=FiguraData[Tip][j*4+i];
                }
        for(int i=0;i<16;i++)
        FiguraData[Tip][i]=Temp[i];

}

void __fastcall TForm1::ClrScr()
{
        Buffer->Canvas->FillRect(Rect(0,0,PoleW,PoleH));
}

int __fastcall TForm1::HitTest(int X, int Y, int Tip)
{
        for(int j=0;j<4;j++)
                for(int i=0;i<4;i++)
                        {
                        if((FiguraData[Tip][j*4+i]!=0)&&(Pole[X+i][Y+j]!=0))
                        return 1;

                        if(FiguraData[Tip][j*4+i]!=0)
                                if((Y+j)>=18)
                                return 2;
                        }
return 0;
}

void __fastcall TForm1::DrawPole()
{
        for(int j=0;j<18;j++)
                for(int i=0;i<10;i++)
                        if(Pole[i][j]!=0)Buffer->Canvas->Draw(30*i,30*j,Block);

Canvas->FillRect(Rect(320,20,320+(4*30),20+(4*30)));
for(int j=0;j<4;j++)
        for(int i=0;i<4;i++)
        {
        if(FiguraData[NextBlock][j*4+i]!=0)Canvas->Draw(320+i*30,20+j*30,Block);
        }
}

void __fastcall TForm1::AddFiguraToPole(int X, int Y, int Tip)
{
        for(int j=0;j<4;j++)
                for(int i=0;i<4;i++)
                        if(FiguraData[Tip][j*4+i]!=0)
                                Pole[X+i][Y+j]=FiguraData[Tip][j*4+i];
}

bool __fastcall TForm1::CreateFigura()
{
      BlockPos=Point(3,0);
      BlockType=NextBlock;
      NextBlock=random(7);
      if(HitTest(BlockPos.x,BlockPos.y,BlockType)==1)return false;
      else
      return true;
}

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_DOWN)Timer1->Interval=50;
if(Key==VK_UP)TurnFiguraNaPole(BlockPos.x,BlockPos.y,BlockType);
if((Key==VK_RIGHT)||Key==VK_LEFT)MoveFigura(Key);
ClrScr();
DrawPole();
DrawFigura(BlockPos.x,BlockPos.y,BlockType);
CopyToScreen();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_DOWN)Timer1->Interval=500;
}
//---------------------------------------------------------------------------


TForm1::TurnFiguraNaPole(int X, int Y, int Tip)
{
        RotateFigura(Tip);

  int LeftLimit=0,RightLimit=0;
  int err=0;
  for(int i=0;i<4;i++,err=0)
  {
        for(int j=0;j<4;j++)
                {
                 if(FiguraData[BlockType][j*4+i]!=0)err=1;
                }
  if(err!=1)LeftLimit++;else break;
  }
  err=0;
  for(int i=3;i>=0;i--,err=0)
  {
        for(int j=0;j<4;j++)
                {
                 if(FiguraData[BlockType][j*4+i]!=0)err=1;
                }
  if(err!=1)RightLimit++;else break;
  }
  if(!HitTest(X,Y,Tip))
  {
  if((BlockPos.x-RightLimit+4)>9)BlockPos.x-=(BlockPos.x-RightLimit+4)-10;
  if((BlockPos.x+LeftLimit)<0)BlockPos.x+=0-(BlockPos.x+LeftLimit);
  }


        if(HitTest(X,Y,Tip))
                {
                RotateFigura(Tip);
                RotateFigura(Tip);
                RotateFigura(Tip);
                }
}

void __fastcall TForm1::MoveFigura(int Key)
{
  int LeftLimit=0,RightLimit=0;
  int err=0;
  for(int i=0;i<4;i++,err=0)
  {
        for(int j=0;j<4;j++)
                {
                 if(FiguraData[BlockType][j*4+i]!=0)err=1;
                }
  if(err!=1)LeftLimit++;else break;
  }
  err=0;
  for(int i=3;i>=0;i--,err=0)
  {
        for(int j=0;j<4;j++)
                {
                 if(FiguraData[BlockType][j*4+i]!=0)err=1;
                }
  if(err!=1)RightLimit++;else break;
  }
if(Key==VK_LEFT)
        {
         int x=BlockPos.x;
         x--;
         if(x+LeftLimit>=0)
         if(!HitTest(x,BlockPos.y,BlockType))BlockPos.x=x;
        }
if(Key==VK_RIGHT)
        {
         int x=BlockPos.x;
         x++;
         if(x-RightLimit<7)
         if(!HitTest(x,BlockPos.y,BlockType))BlockPos.x=x;
        }
}

TForm1::TestCompliteLine()
{
TList*ComplitedLine=new TList();
bool err=false;
        for(int j=17;j>=0;j--,err=false)
                {
                for(int i=0;i<10;i++)
                        if(Pole[i][j]==0)err=true;
                if(err==false)ComplitedLine->Add((void*)j);
                }
for(int i=0;i<ComplitedLine->Count;i++)
        {
        CollapseDown((int)ComplitedLine->Items[i]);
        }
        Score+=ComplitedLine->Count*ComplitedLine->Count;
        Label1->Caption="Очки:"+IntToStr(Score);
delete ComplitedLine;
}

void __fastcall TForm1::CollapseDown(int row)
{
        for(int i=0;i<10;i++)
                Pole[i][row]=0;
        for(int i=0;i<10;i++)
                for(int j=row-1;j>=0;j--)
                        if(j>0)Pole[i][j+1]=Pole[i][j];
                        else   Pole[i][j+1]=0;
}


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
Score=0;
randomize();
PoleW=300;PoleH=540;
for(int j=0;j<18;j++)
        for(int i=0;i<10;i++)
        Pole[i][j]=0;
        NextBlock=random(7);
CreateFigura();
}
//---------------------------------------------------------------------------

