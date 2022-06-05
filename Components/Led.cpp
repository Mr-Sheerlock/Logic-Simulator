#include "Led.h"

Led::Led(const GraphicsInfo& r_GfxInfo, int r_FanOut):Gate(1,r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_OutputPin = NULL;
	On = 0;
}

Led::Led(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(1, r_FanOut) //load version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	m_OutputPin = NULL;
	SetLabel(label);
	On = 0;
	gateID = ID;
}


COPY_ITEMS Led::getType()
{
	return I_LED;
}


void Led::Operate()
{
	if (m_InputPins[0].getStatus() == HIGH)
		On = 1;
	else On = 0;
	return;
}

void Led::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	pOut->DrawLED(m_GfxInfo, isSelected,On);
}

int Led::GetOutPinStatus()
{
	return -1;
}

int Led::GetInputPinStatus(int n)
{
	return m_InputPins[0].getStatus();
}
void Led::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[0].setStatus(s);
}

	bool Led::Checkaround(int Cx, int Cy)
	{
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


void Led::SaveComponent(ofstream& outfile)
{
	if (size(GetLabel()) == 0) { SetLabel("Led"); }
	outfile << "LED" << " " << gateID << " " << GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

bool Led::CheckOutputPin()
{
	return true;
}