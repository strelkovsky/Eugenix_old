#pragma once

struct ImageData final
{
	ImageData(const std::vector<uint8_t>& data, int32_t width, int32_t height, int16_t comp);

	const std::vector<uint8_t>& Data() const;

	const int32_t Width() const;
	const int32_t Height() const;
	const int16_t Comp() const;

private:
	std::vector<uint8_t> _data;

	int32_t _width = 0;
	int32_t _height = 0;
	int16_t _comp = 0;
};
using ImagePtr = std::shared_ptr<ImageData>;

namespace ImageLoader
{
	ImagePtr LoadImage(const std::string& path);
} // namespace ImageLoader