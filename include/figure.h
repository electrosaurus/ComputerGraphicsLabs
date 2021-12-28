#pragma once

#include "gif_painter.h"

class Figure
{
public:
	virtual void draw(GIFPainter& gif_painter) const = 0;
};
