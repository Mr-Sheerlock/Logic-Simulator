#include "NAND2.h"

NAND2::NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

NAND2::NAND2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(2, r_FanOut) //load version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	gateID = ID;
}



COPY_ITEMS NAND2::getType()
{
	return I_NAND2;
}

void NAND2::Operate()
{
	//caclulate the output status as the NANDing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() * m_InputPins[1].getStatus()) == 1)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);

	m_OutputPin.propagate();
}


// Function Draw
// Draws 2-input NAND gate
void NAND2::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawNAND2(m_GfxInfo, isSelected);
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void NAND2::SaveComponent(ofstream& outfile)
{
	if (size(GetLabel()) == 0) { SetLabel("NAND2"); }
	outfile << "NAND2" << " " << gateID << " " << GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}