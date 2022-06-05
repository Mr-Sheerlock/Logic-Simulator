#include "ApplicationManager.h"
#include "Actions\Actionheaders.h"
#include <fstream>
ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	nGates = 0;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();

	CutItem = NULL;
	CutElement = { NUMP , -1 };
	CopyType = NUMP;

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	if (dynamic_cast<Gate*>(pComp)) { nGates++; };
	CompList[CompCount++] = pComp;		
	
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::InitializeGateList() {
	int k = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Gate*>(CompList[i])) {
			
			GateList[k] = dynamic_cast<Gate*>(CompList[i]);
			k++;
		}
		

	}


}




///////////////////////////create TT area/////////////////////////////////////////

void ApplicationManager::CreateTruth(ofstream& tt)
{
	int r = 0;
	GetNofSwitches();
	GetNofLeds();
	IntializeSwitchList();
	IntializeLedList();
	int c = nS;
	int** comb = new int* [pow(2, nS)]; //no. of rows

	for (int i = 0; i < pow(2, nS); i++) {
		comb[i] = new int[nS + nL];  //no. of columns
	}
	while (c > 0 && r < pow(2, nS)) {               //Generating Input combinations 
		for (int i = 0; i < pow(2, nS - c); i++) {
			comb[r][c - 1] = 0;
			r++;
		}
		for (int j = 0; j < pow(2, nS - c); j++) {
			comb[r][c - 1] = 1;
			r++;
		}
		if (r == pow(2, nS)) { c--; r = 0; }
	}                                                       
	//Generating Output 

	for (int i = 0; i < pow(2, nS); i++) { //jumps from row to another
		for (int j = 0; j < nS; j++) {

			STATUS s=LOW;
			if (comb[i][j] == 0)
				SwitchList[j]->setInputPinStatus(1, s);
			else {
				s = HIGH;
				SwitchList[j]->setInputPinStatus(1, s);
			}
		}

		Simulate(this).Execute();

		for (int k = 0; k < nL; k++) {
			comb[i][k + nS] = (LedList[k]->GetInputPinStatus(1) == HIGH) ? 1 : 0;
		}
	}
	for (int a = 0; a < pow(2, nS); a++) {
		tt << endl;
		for (int b = 0; b < nS + nL; b++) {
			tt << comb[a][b] << "   ";
		}
	}

	for (int i = 0; i < pow(2, nS); i++) {
		delete [] comb[i];
	}
	delete[]comb;
}

void ApplicationManager::SortSwitchesVertically()
{
	IntializeSwitchList();
	int y1, y2;
	Switch* S1;
	Switch* S2;
	for (int i = 0; i < nS; i++) {
		for (int j = 0; j < nS - 1; j++) {
			S1 = SwitchList[j];
			y1 = S1->GetGraphicsInfo().y1;
			S2 = SwitchList[j + 1];
			y2 = S2->GetGraphicsInfo().y1;
			if (y2 > y1) {
				SwitchList[j] = S2;
				SwitchList[j + 1] = S1;
			}
		}
	}
}

void ApplicationManager::SortLedsVertically()
{
	IntializeLedList();
	int y1, y2;
	Switch* L1;
	Switch* L2;
	for (int i = 0; i < nS; i++) {
		for (int j = 0; j < nS - 1; j++) {
			L1 = SwitchList[j];
			y1 = L1->GetGraphicsInfo().y1;
			L2 = SwitchList[j + 1];
			y2 = L2->GetGraphicsInfo().y1;
			if (y2 > y1) {
				SwitchList[j] = L2;
				SwitchList[j + 1] = L1;
			}
		}
	}
}

int ApplicationManager::GetNofSwitches()
{
	nS = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Switch*>(CompList[i])) {
			nS++;
		}
	}
	return nS;
}

int ApplicationManager::GetNofLeds()
{
	nL = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Led*>(CompList[i])) {
			nL++;
		}
	}
	return nL;
}

void ApplicationManager::IntializeSwitchList()
{
	int k = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Switch*>(CompList[i])) {

			SwitchList[k] = dynamic_cast<Switch*>(CompList[i]);
			k++;
		}


	}
}

void ApplicationManager::IntializeLedList()
{
	int k = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Led*>(CompList[i])) {

			LedList[k] = dynamic_cast<Led*>(CompList[i]);
			k++;
		}


	}
}













////////////////////////////////////////////////////////////////////

void ApplicationManager::DeleteEverthing() {

	GraphicsInfo G;
	int i = 0;
	while (CompCount>0) {
		if (CompList[i] == NULL) { i = 0; }
		G=CompList[i]->GetGraphicsInfo();
		DeleteComponent(G.x1 + 2, G.y1 +3);
		i++;
		if (i == CompCount) { i = 0; }
	}


}

////////////////////////////////////////////////////////////////////

void ApplicationManager::Sortelementsgraphically() {
	
	InitializeGateList();
	int x1, x2;
	Gate* G1;
	Gate* G2;
	for (int i = 0; i < nGates; i++) {
		for (int j = 0; j < nGates-1; j++) {
			G1 = GateList[j];
			x1 = G1->GetGraphicsInfo().x1;

			G2 = GateList[j+1];

			x2 = G2->GetGraphicsInfo().x1;
			if (x1 > x2) {
				GateList[j] = G2;
				GateList[j+1] = G1;
			}
		}

	}

}


////////////////////////////////////////////////////////////////////

void ApplicationManager::OperateAll() {

	for (int i = 0; i < nGates; i++) {

		GateList[i]->Operate();
	}


}
////////////////////////////////////////////////////////////////////
void  ApplicationManager::DeleteGate(Component* comp)
{
	if (!comp) return;
	Gate* g = (Gate*)(comp);
	g->DeleteGate();
	nGates -= 1;
	FindAndReplace(g);

	// Update Interface
	OutputInterface->ClearDrawingArea();
	UpdateInterface();
}


////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponent(int Cx, int Cy)
{

	int i = FindComp(Cx, Cy);
	Component* comp = CompList[i];
	if (dynamic_cast<Gate*> (comp)) // if it is a gate 
	{
		DeleteGate(comp);
		OutputInterface->PrintMsg("Gate is Deleted Successfully!");
	}
	else if (dynamic_cast<Connection*>(comp))
	{
		Connection* c = (Connection*)(comp);
		DeleteConnection(c);
		OutputInterface->PrintMsg("Connection is  Deleted  Successfully! ");
	}
}
////////////////////////////////////////////////////////////////////
int ApplicationManager::FindComp(Component* c)
{
	if (!c)
		return -1;
	for (int i = 0; i < CompCount; i++)
	{
		if (c == CompList[i])
		{
			return i;
		}
	}
}

////////////////////////////////////////////////////////////////////
int ApplicationManager::FindComp(int Cx, int Cy)
{
	for (int i = 0; i < CompCount; i++)
	{
		Component* comp = CompList[i];
		if (comp->Checkinside(Cx, Cy))
		{
			return i;
		}

	}
	return -1;

}

////////////////////////////////////////////////////////////////////
void ApplicationManager::FindAndReplace(Component* c)
{
	int index = FindComp(c);
	if (!c || index == -1) return;
	CompCount -= 1;
	/*delete CompList[index];*/
	CompList[index] = CompList[CompCount];
	CompList[CompCount] = NULL;
}




////////////////////////////////////////////////////////////////////

void ApplicationManager::DeleteConnection(Connection* c)
{
	if (!c) return;
	c->DeleteConnection();
	FindAndReplace(c);

	// Update the interface 
	OutputInterface->ClearDrawingArea();
	UpdateInterface();
}



////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user

	return InputInterface->GetUserAction(a,b); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case EDIT_Label:
		if (CompCount > 0)
			Edit(this).Execute();
		else { OutputInterface->PrintMsg("There isn't enough gates"); }
		break;
		case ADD_Label:
		if (CompCount > 0)
			Label(this).Execute();
		else { OutputInterface->PrintMsg("There isn't enough gates"); }
		break;
		case ADD_GATE:
			OutputInterface->PrintMsg("Action: Add a gate , Click anywhere");
			OutputInterface->CreateGATESToolBar();
			break;
		case ADD_Buff:
			AddBUFFgate(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked Buffer Gate , Click anywhere");
			break;
		case ADD_INV:
			AddINVgate(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked Inverter , Click anywhere");
			break;
		case ADD_AND_GATE_2:
			AddANDgate2 (this).Execute();
			OutputInterface->PrintMsg("Action: Clicked AND GATE with 2 inputs , Click anywhere");
			break;
		case ADD_OR_GATE_2:
			AddORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked OR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_NAND_GATE_2:
			AddNANDgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked NAND gate with 2 inputs  , Click anywhere");
			break;
		case ADD_NOR_GATE_2:
			AddNORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked NOR GATE with 2 inputs, Click anywhere");
			break;
		case ADD_XOR_GATE_2:
			AddXORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XOR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_XNOR_GATE_2:
			AddXNORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XNOR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_AND_GATE_3:
			AddANDgate3(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked AND GATE with 3 inputs , Click anywhere");
			break;
		case ADD_XOR_GATE_3:
			AddXORgate3(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XOR GATE with 3 inputs, Click anywhere");
			break;
		case ADD_NOR_GATE_3:
			AddNORgate3(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked NOR GATE with 3 inputs, Click anywhere");
			break;
		case ADD_TOOL:
			OutputInterface->PrintMsg("Action: Add a tool , Click anywhere");
			OutputInterface->CreateTOOLStoolbar();
			break;
		case ADD_CONNECTION:
			if (CompCount >= 2)
				CONNECT(this).Execute();
			else {
				OutputInterface->PrintMsg("There isn't Enough Gates");
			}

			break;
		case ADD_Switch:
			AddSwitch(this).Execute();
			OutputInterface->PrintMsg("Action: Add a switch , Click anywhere");
			break;
		case ADD_LED:
			AddLED(this).Execute();
			OutputInterface->PrintMsg("Action : Add an LED , Click anywhere");
			break;
		case DEL:
			if (!CompCount)
			{
				OutputInterface->PrintMsg("Not enough elments to delete. ");
			}
			else
			{
				OutputInterface->PrintMsg("Choose an element to delete .");
				Delete(this).Execute();
			}
			break;
		case MOVE:
			OutputInterface->PrintMsg("Action: clicked MOVE , Click anywhere");
			break;
		case COPY:
			if (!nGates)
			{
				OutputInterface->PrintMsg("There is no any gate to copy. ");
			}
			else
			{
				OutputInterface->PrintMsg("Choose an Element to Copy");
				Copy(this).Execute();
				OutputInterface->PrintMsg("Elmenet is added to the Clipboard! ");

			}
			//OutputInterface->PrintMsg("Action: clicked Copy  , choose a gate to copy it ");
			break;
		case CUT:
			if (!nGates)
			{
				OutputInterface->PrintMsg("Choose an Element to Cut");
				OutputInterface->PrintMsg("There is no any gate to Cut. ");
			}
			else
			{
				CutA(this).Execute();
				OutputInterface->PrintMsg("Elmenet is added to the Clipboard! ");

			}
			//OutputInterface->PrintMsg("Action: clicked Copy  , choose a gate to copy it ");
			break;
		case PASTE:
			if (CopyType == ITM_NGATES && CutElement.CutType == ITM_NGATES)
			{
				OutputInterface->PrintMsg("No elments in the Clipboard. ");
			}
			else
			{
				OutputInterface->PrintMsg("Choose somewhere to paste");
				Paste(this).Execute();
			}
			break;
		case LOAD:
			if (CompCount == 0)
				Load(this).Execute();
			else
			{
				int d = stoi(InputInterface->GetSrting(OutputInterface, "Do you want to delete everything? 0 for no and 1 for yes."));
				if (d == 1) {
					DeleteEverthing();
					Load(this).Execute();
				}else {OutputInterface->PrintMsg("Action cancelled.");}
			}
			break;
		case SAVE:
			if (!CompCount) {
				OutputInterface->PrintMsg("No Items to Save ");
			}
			else {
				Save(this).Execute();
			}
			break;
		case SELECT:
			if (Checkinside(a, b)) {
				SelectComponent(a, b);
			}
			else
				OutputInterface->PrintMsg("A click on the design Area, Click on any Comp to highlight it.");
			break;
		case STATUS_BAR:
			OutputInterface->PrintMsg("Action: a click on the Status Bar, Click anywhere");
			break;
		case DSN_TOOL:
			OutputInterface->PrintMsg("Action: a click on empty area in the Tool Bar, Click anywhere");
			break;
		case SIM_MODE:
			//SIMULATE HERE
			OutputInterface->CreateSimulationToolBar();
			if(ValidateCircuit())
			Simulate(this).Execute();
			break;
		case Create_TruthTable:
			OutputInterface->PrintMsg("Action : clicked Create Truth Table , Click anywhere");
			CreateTT(this).Execute();
			break;
		case VALIDATE:
			OutputInterface->PrintMsg("Validating..");
			if (ValidateCircuit())
				OutputInterface->PrintMsg("Circuit is Valid!");
			else
				OutputInterface->PrintMsg("Circuit is Invalid!");
			break;
		case PROBE:
			OutputInterface->PrintMsg("Pls, choose a pin or a connection. ");
			Probe(this).Execute();
			break;
		case DSN_MODE:
			OutputInterface->PrintMsg("Action: Return to Design Mode, creating Design tool bar");
			OutputInterface->CreateDesignToolBar();
			break;
		case EXIT:
			break;
		
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			Connection* c = (Connection*)(CompList[i]);
			if (!c->getDestPin() || !c->getSourcePin())
			{
				DeleteConnection(c);
				continue;
			}
		}
		CompList[i]->Draw(OutputInterface);
	}

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}
////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::SelectComponent(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			CompList[i]->Select();
		}
		if (UI.AppMode == SIMULATION) {
			Switch* S=dynamic_cast<Switch*>(CompList[i]);
			if (CompList[i]->Checkinside(Cx, Cy) && dynamic_cast<Switch*>(CompList[i])) {
				S->SwitchOn();
				if(ValidateCircuit())
				Simulate(this).Execute();
			}
		}
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::LabelComponent(string x, int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			if (CompList[i]->SetLabel(x)) {
				OutputInterface->PrintMsg("Component Labeled");
			}
			else { OutputInterface->PrintMsg("Component Already Named"); };

			break;
		}

	}
	
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::EditComponent(string x, int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			CompList[i]->EditLabel(x); break;
		}
	}

}
////////////////////////////////////////////////////////////////////
bool ApplicationManager::ChecksameComponent(int Cx1, int Cy1, int Cx2, int Cy2)
{
	if (CompCount == 0) { return false; }
	int i;
	for (i = 0; i < CompCount; i++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[i])) {
			if (CompList[i]->Checkinside(Cx1, Cy1)) { break; }
		}
	}int k;
	for (k = 0; k < CompCount; k++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[k])) {
			if (CompList[k]->Checkinside(Cx2, Cy2)) { break; }
		}
	}
	return i == k;
}
////////////////////////////////////////////////////////////////////

InputPin* ApplicationManager::GetInputPin(int Cx, int Cy, int n) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) { return CompList[i]->GetInputPin(n); }
	}
}



////////////////////////////////////////////////////////////////////

bool ApplicationManager::Checkinside(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) { return true; }
	}
	return false;
}

////////////////////////////////////////////////////////////////////

bool ApplicationManager::Checkaround(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkaround(Cx, Cy)) { return true; }
	}
	return false;



}

////////////////////////////////////////////////////////////////////
//1 for gate, 0 for connection
bool ApplicationManager::ConnorGate(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			if (dynamic_cast<Gate*>(CompList[i])) {
				return true;    //1 for gate 
			}
			else { return false; }
		}
	}
}
////////////////////////////////////////////////////////////////////

OutputPin* ApplicationManager::GetOutputPin(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			return CompList[i]->GetOutputPin();
		}

	}

}
////////////////////////////////////////////////////////////////////

int ApplicationManager::GetNofGate(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			return dynamic_cast<Gate*>(CompList[i])->GetNinputs();
		}
	}


}

////////////////////////////////////////////////////////////////////

Connection* ApplicationManager::GetConnection(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {

		if (CompList[i]->Checkinside(Cx, Cy))
		{
			return dynamic_cast<Connection*>(CompList[i]);
		}

	}


}
////////////////////////////////////////////////////////////////////


GraphicsInfo ApplicationManager::getGraphicsInfo(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[i])) {
			if (CompList[i]->Checkinside(Cx, Cy)) { return CompList[i]->GetGraphicsInfo(); }
		}

	}

}
////////////////////////////////////////////////////////////////////

bool ApplicationManager::isCompfull(int Cx, int Cy) {

	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			return CompList[i]->CheckinputPins();
		}

	}
	//if it's not a gate assume it's true
	return true;

}


////////////////////////////////////////////////////////////////////


void ApplicationManager::Copy2(int Cx, int Cy)
{
	int i = FindComp(Cx, Cy);
	if (dynamic_cast<Gate*>(CompList[i]))
	{
		Gate* item = (Gate*)(CompList[i]);
		CopyType = item->getType();
	}
}



////////////////////////////////////////////////////////////////////

void ApplicationManager::Cut2(int Cx, int Cy)
{
	int i = FindComp(Cx, Cy);
	if (dynamic_cast<Gate*>(CompList[i]))
	{
		Gate* item = (Gate*)(CompList[i]);
		CutElement.CutType = item->getType();
		CutElement.ind = i;
		CutItem = CompList[i];
		// Remove the copied element from the clipboard 
		CopyType = NUMP;
	}
}


////////////////////////////////////////////////////////////////////





void ApplicationManager::Paste2(int Cx, int Cy)
{
	// Check for CopyType 


	if (CopyType != NUMP)
	{
		switch (CopyType)
		{
		case I_AND2:
			AddANDgate2(this).Execute();
			OutputInterface->PrintMsg("2-AND Gate is Pasted!");
			break;
		case I_BUFF:
			AddBUFFgate(this).Execute();
			OutputInterface->PrintMsg("Buff Gate is Pasted!");
			break;
		case I_INV:
			AddINVgate(this).Execute();
			OutputInterface->PrintMsg("INVERTER Gate is Pasted!");
			break;
		case I_OR2:
			AddORgate2(this).Execute();
			OutputInterface->PrintMsg("2-OR Gate is Pasted!");
			break;
		case I_NAND2:
			AddNANDgate2(this).Execute();
			OutputInterface->PrintMsg("2-NAND Gate is Pasted!");
			break;
			case I_NOR2:
				AddNORgate2(this).Execute();
				OutputInterface->PrintMsg("2-AND Gate is Pasted!");
				break;
		case I_XOR2:
			AddXORgate2(this).Execute();
			OutputInterface->PrintMsg("2-XOR Gate is Pasted!");
			break;
		case I_XNOR2:
			AddXNORgate2(this).Execute();
			OutputInterface->PrintMsg("2-XNOR Gate is Pasted!");
			break;
		case I_AND3:
			AddANDgate3(this).Execute();
			OutputInterface->PrintMsg("3-AND Gate is Pasted!");
			break;
		case I_XOR3:
			AddXORgate3(this).Execute();
			OutputInterface->PrintMsg("3-XOR Gate is Pasted!");
			break;
		case I_NOR3:
			AddNORgate3(this).Execute();
			OutputInterface->PrintMsg("3-NOR Gate is Pasted!");
			break;
		case I_SWITCH:
			AddSwitch(this).Execute();
			OutputInterface->PrintMsg("SWITCH Gate is Pasted!");
			break;
		case I_LED:
			AddLED(this).Execute();
			OutputInterface->PrintMsg("LED Gate is Pasted!");
			break;
		default:
			CopyType = NUMP;

		}
	}

	// Check for CutType 
	if (CutElement.CutType != NUMP && CompList[CutElement.ind] == CutItem)
	{
		switch (CutElement.CutType)
		{
		case I_AND2:
			AddANDgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-AND Gate is Pasted!");
			break;
		case I_BUFF:
			AddBUFFgate(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("Buff Gate is Pasted!");
			break;
		case I_INV:
			AddINVgate(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("INVERTER Gate is Pasted!");
			break;
		case I_OR2:
			AddORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-OR Gate is Pasted!");
			break;
		case I_NAND2:
			AddNANDgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-NAND Gate is Pasted!");
			break;
			case I_NOR2:
				AddNORgate2(this).Execute();
				OutputInterface->PrintMsg("2-AND Gate is Pasted!");
				break;
		case I_XOR2:
			AddXORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-XOR Gate is Pasted!");
			break;
		case I_XNOR2:
			AddXNORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-XNOR Gate is Pasted!");
			break;
		case I_AND3:
			AddANDgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-AND Gate is Pasted!");
			break;
		case I_XOR3:
			AddXORgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-XOR Gate is Pasted!");
			break;
		case I_NOR3:
			AddNORgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-NOR Gate is Pasted!");
			break;
		case I_SWITCH:
			AddSwitch(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("SWITCH Gate is Pasted!");
			break;
		case I_LED:
			AddLED(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("LED Gate is Pasted!");
			break;
		default:

			CutElement.CutType = NUMP;
			CutItem = NULL;
			CutElement.ind = -1;
			break;
		}
	}
}





////////////////////////////////////////////////////////////////////
void ApplicationManager::SaveCircuit(ofstream& outfile)
{
	outfile << nGates << endl;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Gate*>(CompList[i])) {
			CompList[i]->SaveComponent(outfile);
		}
	}

	outfile << "Connections" << endl;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Connection*>(CompList[i])) {
			CompList[i]->SaveComponent(outfile);
		}
	}
}




////////////////////////////////////////////////////////////////////
void ApplicationManager::LoadCircuit(ifstream& infile)
{
	bool flag=true;        //used to start the for loop 1 time only, then it's set to false at the end.
	string ctype, clabel;
	int cID, cID2, noOfgates, noOfpin;
	GraphicsInfo gfxload;
	infile >> noOfgates;
	while (!infile.eof()) {
		if(flag)
		for (int i = 0; i < noOfgates; i++) {
			infile>>ctype >> cID >> clabel >> gfxload.x1 >> gfxload.y1;
			gfxload.x2 = gfxload.x1 + UI.AND2_Width;
			gfxload.y2 = gfxload.y1 + UI.AND2_Height;
			if (ctype == "AND2") {
				AND2* pAND2 = new AND2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pAND2;
				nGates++;
			}
			else if (ctype == "OR2") {
				OR2* pOR2 = new OR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pOR2;
				nGates++;
			}
			else if (ctype == "BUFF") {
				BUFF* pBUFF = new BUFF(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pBUFF;
				nGates++;
			}
			else if (ctype == "INV") {
				INV* pINV = new INV(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pINV;
				nGates++;
			}
			else if (ctype == "NAND2") {
				NAND2* pNAND2 = new NAND2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNAND2;
				nGates++;
			}
			else if (ctype == "NOR2") {
				NOR2* pNOR2 = new NOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNOR2;
				nGates++;
			}
			else if (ctype == "XOR2") {
				XOR2* pXOR2 = new XOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXOR2;
				nGates++;
			}
			else if (ctype == "XNOR2") {
				XNOR2* pXNOR2 = new XNOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXNOR2;
				nGates++;
			}
			else if (ctype == "XOR3") {
				XOR3* pXOR3 = new XOR3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXOR3;
				nGates++;
			}
			else if (ctype == "AND3") {
				AND3* pAND3 = new AND3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pAND3;
				nGates++;
			}
			else if (ctype == "NOR3") {
				NOR3* pNOR3 = new NOR3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNOR3;
				nGates++;
			}
			else if (ctype == "LED") {
				Led* pLED = new Led(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pLED;
				nGates++;
			}
			else if (ctype == "SWTCH") {
				Switch* pSWITCH = new Switch(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pSWITCH;
				nGates++;
			}
			if(i== noOfgates-1){
				flag = false;
				infile >> clabel;             //used to trivially bypass the word "Connections" and get past it without affecting the order of inputs
			}
		}
			
			infile >> cID >> cID2 >> noOfpin;
			Component* C1 = getCompbyID(cID);
			Component* C2 = getCompbyID(cID2);

			OutputPin* SrcPin = GetOutputPin((C1->GetGraphicsInfo().x1), (C1->GetGraphicsInfo().y1));
			InputPin* DstPin = GetInputPin((C2->GetGraphicsInfo().x1), (C2->GetGraphicsInfo().y1), noOfpin);
			gfxload.x1 = C1->GetGraphicsInfo().x2;
			gfxload.y1 = C1->GetGraphicsInfo().y1 + 23;
			gfxload.x2 = C2->GetGraphicsInfo().x1;
			if (noOfpin == 1 || noOfpin < 1) {
				gfxload.y2 = C2->GetGraphicsInfo().y1 + 13;
			}
			else if (noOfpin == 2) { gfxload.y2 = C2->GetGraphicsInfo().y2 - 13; }
			else if (noOfpin == 3 || noOfpin > 3) { gfxload.y2 = C2->GetGraphicsInfo().y2; }
			if (cID != -1) {     //because CID is set to -1 at the end 
				Connection* wire = new Connection(gfxload, SrcPin, DstPin,1);
				CompList[CompCount++] = wire;
			}
		}
}


////////////////////////////////////////////////////////////////////
Component* ApplicationManager::getCompbyID(int compID)
{
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->GetID() == compID) {
			return CompList[i];
		}
	}
}


////////////////////////////////////////////////////////////////////

bool ApplicationManager::ValidateCircuit()
{
	for (int i = 0; i < CompCount; i++)
	{
		Component* comp = CompList[i];
		if (dynamic_cast<Gate*>(comp))
		{
			if (!comp->CheckinputPins() || !comp->CheckOutputPin())
			{
				OutputInterface->PrintMsg("Circuit is not Valid!"); 
				return false;
			}
		}
	}
	OutputInterface->PrintMsg("Circuit is Valid"); 
	return true;
}







////////////////////////////////////////////////////////////////////
void ApplicationManager::ProbeCircuit(int Cx, int Cy)
{
	int index = FindComp(Cx, Cy);

	if (index == -1)return; // Break, if not a valid point 

	Component* comp = CompList[index];
	if (dynamic_cast<Connection*>(comp)) // if Connection
	{
		Connection* con = (Connection*)(comp);
		OutputInterface->PrintMsg("Connection Status: " + to_string(con->GetOutPinStatus()));
	}
	else // if Gate 
	{
		bool a;
		int b = -1;

		Gate* gate = (Gate*)(comp);
		if (gate->getType() == I_LED)
		{
			OutputInterface->PrintMsg("Led Status : " + to_string(gate->GetInputPinStatus(1)));
		}
		else if (gate->getType() == I_SWITCH)
		{
			OutputInterface->PrintMsg("Switch Status : " + to_string(gate->GetOutPinStatus()));
		}
		else if (gate->isPointPin(Cx, Cy, a, b)) // Point clicked is a pin
		{
			if (a) // a true if output pin, otherwise it is false
			{
				OutputInterface->PrintMsg("OutPin Status : " + to_string(gate->GetOutPinStatus()));
			}
			else // if it is an input pin
			{
				OutputInterface->PrintMsg("InPin Status: " + to_string(gate->GetInputPinStatus(b)));
			}
		}

	}

}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}






//////////////////////////////////////////////////////////////////////

















