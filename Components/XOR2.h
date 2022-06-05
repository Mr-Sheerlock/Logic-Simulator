#ifndef _XOR2_H
#define _XOR2_H

/*
  Class XOR2
  -----------
  represent the 2-input XOR gate
*/

#include "Gate.h"

class XOR2 :public Gate
{
public:
	XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	XOR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//Calculates the output of the XOR gate
	 void Draw(Output* pOut);	//Draws 2-input gate

	 int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);
};

#endif#pragma once
