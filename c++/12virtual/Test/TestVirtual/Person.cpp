#include "stdafx.h"
#include "Person.h"


PFN_VIRTUAL CPerson::m_VirTable[2] = { &CPerson::Speak, &CPerson::Eat};


CPerson::~CPerson()
{
}
