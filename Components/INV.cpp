#include "INV.h"

INV::INV(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

INV::INV(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(1, r_FanOut) //load version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	gateID = ID;
}



COPY_ITEMS INV::getType()
{
	return I_INV;
}

void INV::Operate()
{
	//caclulate the output status as the INVof the input pin

	//Add you code here
	if ((m_InputPins[0].getStatus() == 1))
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);

	m_OutputPin.propagate();
}


// Function Draw
// Draws 1-input INV gate
void INV::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawINV(m_GfxInfo, isSelected);
}

//returns status of outputpin
int INV::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int INV::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void INV::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void INV::SaveComponent(ofstream& outfile)
{
	if (size(GetLabel()) == 0) { SetLabel("Inv"); }
	outfile << "INV" << " " << gateID << " " << GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}