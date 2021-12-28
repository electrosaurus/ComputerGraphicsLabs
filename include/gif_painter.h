#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "point.h"

struct Color
{
	using chan_t = unsigned char;

	chan_t r, g, b, alpha;

	static Color rgb(chan_t r, chan_t g, chan_t b);
};

class GIFPainter
{
public:

private:
	struct Frame
	{
		Color *pixels;
		size_t duration;
	};

	std::vector<Frame> frames;

public:
	const size_t width, height;
	Color color = Color { 255, 255, 255, 255 };
	bool inverse_x = false, inverse_y = true;

	GIFPainter(size_t width, size_t height);
	void add_frame(size_t duration);
	void fill_pixel(size_t x, size_t y);
	void save(const std::string& filename) const;
	void clear();
	virtual ~GIFPainter();
};
