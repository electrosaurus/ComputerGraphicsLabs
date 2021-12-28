#include "gif_painter.h"
#include "gif.h"

Color Color::rgb(chan_t r, chan_t g, chan_t b)
{
	return Color { r, g, b, 255 };
}

GIFPainter::GIFPainter(size_t width, size_t height) : width(width), height(height)
{ }

void GIFPainter::add_frame(size_t duration)
{
	Frame frame;
	frame.duration = duration;
	frame.pixels = new Color[width * height];
	for (size_t i = 0; i < width * height; i++)
		frame.pixels[i] = color;
	frames.push_back(std::move(frame));
}

void GIFPainter::fill_pixel(size_t x, size_t y)
{
	if (inverse_x)
		x = width - x;
	if (inverse_y)
		y = height - y;
	frames.back().pixels[y * width + x] = color;
}

void GIFPainter::save(const std::string& filename) const
{
	GifWriter gif_writer;
	GifBegin(&gif_writer, filename.c_str(), width, height, 0);
	for (auto& frame : frames)
	{
		GifWriteFrame(
			&gif_writer,
			reinterpret_cast<Color::chan_t*>(frame.pixels),
			width,
			height,
			frame.duration);
	}
	GifEnd(&gif_writer);
}

void GIFPainter::clear()
{
	for (auto& frame : frames)
	{
		delete[] frame.pixels; 
	}
	frames.clear();
}

GIFPainter::~GIFPainter()
{
	clear();
}
