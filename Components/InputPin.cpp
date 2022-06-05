#include "InputPin.h"

InputPin::InputPin()
{
	m_Connection = NULL;
}

Component* InputPin::getComponent()
{
	return pComp;
}
void InputPin::setComponent(Component* pCmp)
{
	this->pComp = pCmp;
}
void InputPin::setConnection(Connection* c) {

	m_Connection = c;

}

void InputPin::Disconnect() {

	m_Connection = NULL;

}

bool InputPin::isConnected() {

	if (m_Connection != NULL) { return true; }
	return false;
}

Connection* InputPin::GetConnection() {

	return m_Connection;
}

void InputPin::setNumber(int n) {

	IPn = n;
}

int InputPin::getNumber()
{
	return IPn;
}
