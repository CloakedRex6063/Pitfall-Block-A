// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#pragma once

namespace Tmpl8
{

// basic sprite class
class Sprite
{
public:
	// structors
	Sprite( Surface* surface, unsigned int frameCount );
	~Sprite();
	// methods
	void Draw(const Surface* target, float2 pos);
	void DrawScaled(const Surface* target, float2 pos, float2 size);
	void SetFlags( unsigned int f ) { flags = f; }
	void SetFrame( unsigned int i ) { currentFrame = i; }
	unsigned int GetFlags() const { return flags; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	uint* GetBuffer() { return surface->pixels; }
	unsigned int Frames() { return numFrames; }
	Surface* GetSurface() { return surface; }
	void InitializeStartData();
	bool IsPixelTransparent(int2 pos);

private:
	// attributes
	int width, height;
	unsigned int numFrames;
	unsigned int currentFrame;
	unsigned int flags;
	unsigned int** start;
	Surface* surface;
};

}