#include "MObject.h"

int MObject::m_numOfObj = 0;

MObject::MObject()
{
	++m_numOfObj;
}


MObject::~MObject()
{
	--m_numOfObj;
}