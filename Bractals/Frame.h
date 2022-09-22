#include <algorithm>
#include <cmath>
#include <vector>

namespace frame {
    void setPixel(std::vector<std::vector<std::vector<uint8_t>>>& frame, const uint16_t& x, const uint16_t& y, const uint32_t& color = 0);

    uint32_t HSVtoRGB(uint16_t hue, uint8_t saturation, uint8_t value, uint8_t alpha = 255);
}