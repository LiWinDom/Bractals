#include "Frame.h"

void frame::setPixel(std::vector<std::vector<std::vector<uint8_t>>>& frame, const uint16_t& x, const uint16_t& y, const uint32_t& color) {
    frame[y][x][0] = color >> 24;
    frame[y][x][1] = color >> 16;
    frame[y][x][2] = color >> 8;
    return;
}

uint32_t frame::HSVtoRGB(uint16_t hue, uint8_t saturation, uint8_t value, uint8_t alpha) {
    hue %= 360;
    saturation = std::min(std::max(saturation, (uint8_t)0), (uint8_t)100);
    value = std::min(std::max(value, (uint8_t)0), (uint8_t)100);
    alpha = std::min(std::max(alpha, (uint8_t)0), (uint8_t)100);

    double s = saturation / 100.0;
    double v = value / 100.0;

    double C = s * v;
    double X = C * (1 - abs(std::fmod(hue / 60.0, 2) - 1));
    double m = v - C;

    if (hue < 60) {
        uint8_t r = (C + m) * 255;
        uint8_t g = (X + m) * 255;
        uint8_t b = m * 255;
        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
    if (hue < 120) {
        uint8_t r = (X + m) * 255;
        uint8_t g = (C + m) * 255;
        uint8_t b = m * 255;
        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
    if (hue < 180) {
        uint8_t r = m * 255;
        uint8_t g = (C + m) * 255;
        uint8_t b = (X + m) * 255;
        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
    if (hue < 240) {
        uint8_t r = m * 255;
        uint8_t g = (X + m) * 255;
        uint8_t b = (C + m) * 255;
        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
    if (hue < 300) {
        uint8_t r = (X + m) * 255;
        uint8_t g = m * 255;
        uint8_t b = (C + m) * 255;
        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
    uint8_t r = (C + m) * 255;
    uint8_t g = m * 255;
    uint8_t b = (X + m) * 255;
    return (r << 24) | (g << 16) | (b << 8) | alpha;
}