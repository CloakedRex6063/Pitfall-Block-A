// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"

using namespace Tmpl8;

// constructor
Sprite::Sprite( Surface* surface, unsigned int frameCount ) :
	width(surface->width / static_cast<int>(frameCount)),
	height(surface->height),
	numFrames(frameCount),
	currentFrame(0),
	flags(0),
	start(new unsigned int* [frameCount]),
	surface(surface)
{
	InitializeStartData();
}

// destructor
Sprite::~Sprite()
{
	delete surface;
	for (unsigned int i = 0; i < numFrames; i++) delete start[i];
	delete[] start;
}

// draw sprite to target surface
void Sprite::Draw(const Surface* target, float2 pos)
{
	if (static_cast<int>(pos.x) < -width || static_cast<int>(pos.x) > ( target->width + width )) return;
	if (static_cast<int>(pos.y) < -height || pos.y > ( target->height + height )) return;
	int x1 = static_cast<int>(pos.x), x2 = static_cast<int>(pos.x) + width;
	int y1 = static_cast<int>(pos.y), y2 = static_cast<int>(pos.y) + height;
	uint* src = currentFrame * width + GetBuffer();
	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	if (x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * target->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - static_cast<int>(pos.y));
			const int lsx = static_cast<int>(pos.x) + static_cast<int>(start[currentFrame][line]);
			const int xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				const uint c1 = *(src + i);
				if (c1 & 0xffffff) *(dest + addr + i) = c1;
			}
			addr += target->width;
			src += width * numFrames;
		}
	}
}

// draw scaled sprite
void Sprite::DrawScaled(const Surface* target, float2 pos, float2 size)
{
	if (width == 0 || height == 0) return;
	for (int x = 0; x < size.x; x++) for (int y = 0; y < size.y; y++)
	{
		int u = (int)((float)x * ((float)width / (float)size.x));
		int v = (int)((float)y * ((float)height / (float)size.y));
		uint color = GetBuffer()[u + v * width * numFrames];
		if (color & 0xffffff) target->pixels[static_cast<int>(pos.x) + x + ((static_cast<int>(pos.y) + y) * target->width)] = color;
	}
}

// prepare sprite outline data for faster rendering
void Sprite::InitializeStartData()
{
	for (unsigned int f = 0; f < numFrames; ++f)
	{
		start[f] = new unsigned int[height];
		for (int y = 0; y < height; ++y)
		{
			start[f][y] = width;
			const uint* addr = GetBuffer() + f * width + y * width * numFrames;
			for (int x = 0; x < width; ++x) if (addr[x])
			{
				start[f][y] = x;
				break;
			}
		}
	}
}

bool Sprite::IsPixelTransparent(int2 pos)
{
	// Ensure x and y are within the bounds of the sprite.
	if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height)
	{
		uint* pixel = GetBuffer() + currentFrame * width + pos.x + pos.y * width * numFrames;
		return !(*pixel & 0xffffff); // Check if the pixel is transparent.
	}
	return true; // Treat out-of-bounds as transparent.
}