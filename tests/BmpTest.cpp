#include "bitmap/BMP.h"
#include "StdStream.h"

void FillBitmap(Framework::CBitmap& bitmap)
{
	for(int32 y = 0; y < bitmap.GetHeight(); y++)
	{
		uint8 colorY = (y * 255) / bitmap.GetHeight();
		for(int32 x = 0; x < bitmap.GetWidth(); x++)
		{
			uint8 colorX = (x * 255) / bitmap.GetWidth();
			bitmap.SetPixel(x, y, Framework::CColor(colorX, 0x00, colorY, 0x80));
		}
	}
}

void BmpTest_Execute()
{
	//Write 32-bpp BMP
	{
		auto bitmap = Framework::CBitmap(223, 257, 32);
		FillBitmap(bitmap);
		Framework::CStdStream outputStream("test32.bmp", "wb");
		Framework::CBMP::WriteBitmap(bitmap, outputStream);
	}
	//Write 24-bpp BMP
	{
		auto bitmap = Framework::CBitmap(223, 257, 24);
		FillBitmap(bitmap);
		Framework::CStdStream outputStream("test24.bmp", "wb");
		Framework::CBMP::WriteBitmap(bitmap, outputStream);
	}
	//Write 8-bpp BMP
	{
		auto bitmap = Framework::CBitmap(223, 257, 8);
		FillBitmap(bitmap);
		Framework::CStdStream outputStream("test8.bmp", "wb");
		Framework::CBMP::WriteBitmap(bitmap, outputStream);
	}
	//Read BMP
	{
		Framework::CStdStream inputStream("test8.bmp", "rb");
		auto bitmap = Framework::CBMP::ReadBitmap(inputStream);
	}
}
