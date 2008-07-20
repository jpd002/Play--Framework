#include "win32/AcceleratorTableGenerator.h"

using namespace Framework::Win32;

CAcceleratorTableGenerator::CAcceleratorTableGenerator()
{

}

CAcceleratorTableGenerator::~CAcceleratorTableGenerator()
{

}

void CAcceleratorTableGenerator::Insert(unsigned int cmd, unsigned int key, unsigned int virt)
{
	ACCEL accel;
    memset(&accel, 0, sizeof(ACCEL));
	accel.cmd	= cmd;
	accel.key	= key;
	accel.fVirt	= virt;
    m_table.push_back(accel);
}

HACCEL CAcceleratorTableGenerator::Create()
{
    return CreateAcceleratorTable(&m_table[0], m_table.size());
}
