#ifndef _INV_H
#define _INV_H

/*
  Class INV
  -----------
  represent the 1-input INV gate
*/

#include "Gate.h"

class INV :public Gate
{
public:
	INV(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	INV(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//Calculates the output of the INV gate
	 void Draw(Output* pOut);	//Draws 1-input gate

	int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);
};

#endif
