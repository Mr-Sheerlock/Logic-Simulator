#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  -----------
  represent the 3-input XOR gate
*/

#include "Gate.h"

class XOR3 :public Gate
{
public:
	XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	XOR3(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//Calculates the output of the XOR gate
	 void Draw(Output* pOut);	//Draws 3-input gate

	 int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);
};

#endif
