#include "Save.h"

Save::Save(ApplicationManager* pAppMan):Action(pAppMan)
{
}

void Save::ReadActionParameters()
{

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	filename = pIn->GetSrting(pOut, "Write the name of the file in .txt format you want to save into ");


}

void Save::Execute()
{

	ReadActionParameters();

		outwrite.open(filename);
		outwrite.clear(); //Clears txt file for new circuit (demo)
		pManager->SaveCircuit(outwrite);
		outwrite << "-1\n";
		pManager->GetOutput()->PrintMsg("Circuit Saved Successfully");
}

void Save::Undo()
{
}

void Save::Redo()
{
}

Save::~Save()
{
	outwrite.close();
}
