#pragma once
#include"Gate.h"
class Switch : public Gate {
private:
	bool On;
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	Switch(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut);
	 void Operate();	//output of switch
	 void Draw(Output* pOut);	//Draws switch

	 int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	 int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	 bool Checkaround(int x, int y);
	 void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	COPY_ITEMS getType();
	 void SaveComponent(ofstream& outfile);


	void SwitchOn();
};

