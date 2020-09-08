#include "win32/DpiUtils.h"
#include "win32/ClientDeviceContext.h"

using namespace Framework;
using namespace Framework::Win32;

int Framework::Win32::PointsToPixels(int pointsValue)
{
	CClientDeviceContext screenDc(NULL);
	int ydpi = GetDeviceCaps(screenDc, LOGPIXELSY);
	return MulDiv(pointsValue, ydpi, 96);
}

CRect Framework::Win32::PointsToPixels(const Framework::Win32::CRect& pointsRect)
{
	CClientDeviceContext screenDc(NULL);
	int ydpi = GetDeviceCaps(screenDc, LOGPIXELSY);
	Framework::Win32::CRect pixelsRect(0, 0, 0, 0);
	pixelsRect.SetLeft(MulDiv(pointsRect.Left(), ydpi, 96));
	pixelsRect.SetTop(MulDiv(pointsRect.Top(), ydpi, 96));
	pixelsRect.SetRight(MulDiv(pointsRect.Right(), ydpi, 96));
	pixelsRect.SetBottom(MulDiv(pointsRect.Bottom(), ydpi, 96));
	return pixelsRect;
}
