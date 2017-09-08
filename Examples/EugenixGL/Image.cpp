#include "Includes.h"

#define STB_IMAGE_IMPLEMENTATION
#include <../3rdParty/stb_image.h>

#include "Image.h"

ImageData::ImageData(const std::vector<uint8_t>& data, int32_t width, int32_t height, int16_t comp) : _data(data), _width(width), _height(height), _comp(comp)
{
}

const std::vector<uint8_t>& ImageData::Data() const
{
	return _data;
}

const int32_t ImageData::Width() const
{
	return _width;
}

const int32_t ImageData::Height() const
{
	return _height;
}

const int16_t ImageData::Comp() const
{
	return _comp;
}

namespace ImageLoader
{
	ImagePtr LoadImage(const std::string& name)
	{
		int width, height, comp;
		uint8_t* rawData = stbi_load(name.c_str(), &width, &height, &comp, STBI_rgb);

		if (!rawData)
		{
			printf("Failed to open image file %s - %s\n", name.c_str(), stbi_failure_reason());
			// TODO : return default texture
			return ImagePtr();
		}

		std::vector<uint8_t> data;
		data.assign(rawData, rawData + (width * height * comp));
		stbi_image_free(rawData);

		return ImagePtr(new ImageData(data, width, height, comp));
	}
} // namespace ImageLoader