#pragma once

#include "Rect.h"

namespace Framework
{
	namespace Win32
	{
		int		PointsToPixels(int pointsValue);
		CRect	PointsToPixels(const Framework::Win32::CRect& pointsRect);
	}
}
