#ifndef _XNOR2_H
#define _XNOR2_H

/*
  Class XNOR2
  -----------
  represent the 2-input XNOR gate
*/

#include "Gate.h"

class XNOR2 :public Gate
{
public:
	XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	XNOR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//Calculates the output of the XNOR gate
	 void Draw(Output* pOut);	//Draws 2-input gate

	 int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);
};

#endif