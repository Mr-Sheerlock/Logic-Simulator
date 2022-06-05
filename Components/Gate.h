#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate :public Component
{
protected:
	static int GATE_ID;  //Static counter
	int gateID; // a copy of each of his ID (To be accessed later)

	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);
	virtual bool Checkaround(int x, int y); //Checks around the gate
	virtual bool Checkinside(int x, int y); //Checks inside the gate
	
	
	virtual bool CheckinputPins();   //Checks if all input pins are connected returns true

	virtual bool CheckOutputPin();  // returns true when the outputPin is connected 


	virtual void DeleteGate();

	InputPin* GetInputPin(int n);
	OutputPin* GetOutputPin();
	int GetNinputs();
	virtual COPY_ITEMS getType() = 0;

	virtual int GetID();
	virtual void SetID(int n);
	virtual bool isPointPin(int Cx, int Cy, bool& a, int& b);

};

#endif
