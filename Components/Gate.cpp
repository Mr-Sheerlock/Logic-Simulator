#include "Gate.h"
#include "Connection.h"
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin

int Gate::GATE_ID = 0;

Gate::Gate(int r_Inputs, int r_FanOut) :m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate

	//Associate the output pin to this gate
	m_OutputPin.setComponent(this);
	
	//Associate all input pins to this gate
	for (int i = 0; i < m_Inputs; i++) {
		m_InputPins[i].setComponent(this);
		m_InputPins[i].setNumber(i + 1);
	}
	GATE_ID += 10;
	gateID = GATE_ID;
}

bool Gate::Checkaround(int Cx, int Cy) {
	GraphicsInfo G = m_GfxInfo;
	int COGx = (G.x2 + G.x1) / 2;  //COG=Center of Gate
	int COGy = (G.y2 + G.y1) / 2; //COG= Center of Gate	
//Draw an imaginary circle around each gate, and this is how you validate, (1.5*r)^2 was chosen because it's suitable
	if ((pow((Cx - COGx), 2) + pow((Cy - COGy), 2)) <= pow(1.5 * 50, 2))
	{
		return true;
	}
	else return false;


}

bool Gate::Checkinside(int x, int y) {
	GraphicsInfo G = m_GfxInfo;
	if ((G.x1 <= x && G.x2 >= x) && (G.y1 <= y && G.y2 >= y)) {
		return true;
	}
	else return false;


}

//IF ALL connected return true, else return false
bool Gate::CheckinputPins() {
	//trivial case: case of switch
	if (m_InputPins == 0) { return true; }
	for (int i = 0; i < m_Inputs; i++) {
		if (!m_InputPins[i].isConnected())
			return false;

	}return true;


}

bool Gate::CheckOutputPin()
{
	return m_OutputPin.ConnectionsCount() != 0;
}

void Gate::DeleteGate()
{
	for (int i = 0; i < m_OutputPin.ConnectionsCount(); i++)
	{
		m_OutputPin.getConnectionByIndex(i)->setSourcePin(NULL);
	}

	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].isConnected())
		{
			m_InputPins[i].GetConnection()->setDestPin(NULL);
		}
	}
}

InputPin* Gate::GetInputPin(int n) {
	return &(m_InputPins[n - 1]);

}
OutputPin* Gate::GetOutputPin() {
	return &m_OutputPin;
}

int Gate::GetNinputs() {
	return m_Inputs;
}

int Gate::GetID() { return gateID; }

void Gate::SetID(int n) { gateID = n; }

bool Gate::isPointPin(int Cx, int Cy, bool& a, int& b)  // Led& Switch are exception
{
	int x = m_GfxInfo.x1;
	int y = m_GfxInfo.y1;

	// Case1 : Input Count = 2 
	if (m_Inputs == 2)
	{
		if (Cx >= x && Cx <= x + 10)
		{
			if (Cy <= y + 17 && Cy >= y + 7)
			{
				a = false; // input pin
				b = 1;
				return true;
			}
			else if (Cy <= y + 40 && Cy >= y + 30)
			{
				a = false; // input pin 
				b = 2;
				return true;
			}
		}
	}
	// Case2: Input Count = 3
	else if (m_Inputs == 3)
	{
		if (Cx >= x && Cx <= x + 10)
		{
			if (Cy < y + 20 && Cy >= y + 10)
			{
				a = false; // input pin
				b = 1;
				return true;
			}
			else if (Cy < y + 30 && Cy >= y + 20)
			{
				a = false; // input pin 
				b = 2;
				return true;
			}
			else if (Cy <= y + 40 && Cy >= y + 30)
			{
				a = false; // input pin 
				b = 3;
				return true;
			}
		}
	}
	else if (m_Inputs == 1 && Cy >= y + 20 && Cy <= y + 30 && Cx >= x && Cx <= x + 10)
	{
		a = false;
		b = 1;
		return true;
	}

	x = m_GfxInfo.x2;
	y = m_GfxInfo.y2;

	// Check for output pin 
	if (Cx >= x - 10 && Cx <= x && Cy >= y - 30 && Cy <= y - 20)
	{
		a = true;
		return true;
	}

	return false;
}
