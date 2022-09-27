#pragma once
#include <algorithm>
#include <cmath>
#include <vector>

namespace frame {
    void setPixel(std::vector<std::vector<std::vector<uint8_t>>>& frame, const uint16_t& x, const uint16_t& y, const uint32_t& color = 0);

    std::vector<std::vector<std::vector<uint8_t>>> resize(const std::vector<std::vector<std::vector<uint8_t>>>& frame, const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2);

    uint32_t HSVtoRGB(uint16_t hue, uint8_t saturation, uint8_t value, uint8_t alpha = 255);
}