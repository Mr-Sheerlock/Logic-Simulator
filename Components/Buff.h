#ifndef _BUFF_H
#define _BUFF_H

/*
  Class BUFF
  -----------
  represent the 1-input BUFF gate
*/

#include "Gate.h"

class BUFF :public Gate
{
public:
	BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	BUFF(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//Calculates the output of the BUFF gate
	 void Draw(Output* pOut);	//Draws 1-input gate

	 int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);
};

#endif