#include "layout/LayoutStretch.h"

using namespace Framework;

CLayoutStretch::CLayoutStretch(unsigned int nHorzStretch, unsigned int nVertStretch) : 
CLayoutObject(nHorzStretch, nVertStretch)
{

}

unsigned int CLayoutStretch::GetPreferredWidth()
{
	return 0;
}

unsigned int CLayoutStretch::GetPreferredHeight()
{
	return 0;
}

void CLayoutStretch::RefreshGeometry()
{

}
