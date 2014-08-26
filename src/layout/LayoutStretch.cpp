#include "layout/LayoutStretch.h"

using namespace Framework;

CLayoutStretch::CLayoutStretch(unsigned int horzStretch, unsigned int vertStretch)
: CLayoutObject(horzStretch, vertStretch)
{

}

LayoutObjectPtr CLayoutStretch::Create(unsigned int horzStretch, unsigned int vertStretch)
{
	return std::make_shared<CLayoutStretch>(horzStretch, vertStretch);
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
