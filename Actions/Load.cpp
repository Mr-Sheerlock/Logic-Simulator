#include "Load.h"

Load::Load(ApplicationManager* pAppMan):Action(pAppMan)
{
}

void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	filename = pIn->GetSrting(pOut, "Write the name of the file in .txt format you want to load from ");
	
}

void Load::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	readout.open(filename);
	if (readout.peek() == EOF) {
		pManager->GetOutput()->PrintMsg("File is empty ");
	}
	else {
		pManager->LoadCircuit(readout);
		pManager->GetOutput()->PrintMsg("Circuit Loaded Successfully");
	}
	
}


void Load::Undo()
{
}

void Load::Redo()
{
}

Load::~Load()
{
	readout.close();
}
