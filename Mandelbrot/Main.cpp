#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <thread>

#include "Complex.h"
#include "Config.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

uint8_t frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];

JuliaSet juliaSet(Complex(-0.74543, 0.11301));
MandelbrotSet mandelbrotSet;

sf::Vector2f pos(0, 0);
double size = 256;

void setPixel(const uint16_t& x, const uint16_t& y, const uint32_t& color) {
    frameBuffer[x][y][0] = color >> 24;
    frameBuffer[x][y][1] = color >> 16;
    frameBuffer[x][y][2] = color >> 8;
    return;
}

uint32_t HSVtoRGB(uint16_t hue, uint8_t saturation, uint8_t value, uint8_t alpha = 255) {
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

void eventProcess(sf::Window& window) {
    static std::pair<int16_t, int16_t> start_mouse_pos = { -1, -1 };
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        else if (event.type == sf::Event::KeyPressed) {/*
            if (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add) {
                if (cur_size_index < 6) ++cur_size_index;
            }
            else if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract) {
                if (cur_size_index > 0) --cur_size_index;
            }
            else if (event.key.code == sf::Keyboard::Up) {
                if (cur_size_index >= 3) ++need_shift.second;
                else if (cur_size_index > 0) need_shift.second += 5;
                else need_shift.second += 10;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                if (cur_size_index >= 3) --need_shift.second;
                else if (cur_size_index > 0) need_shift.second -= 5;
                else need_shift.second -= 10;
            }
            else if (event.key.code == sf::Keyboard::Left) {
                if (cur_size_index >= 3) --need_shift.first;
                else if (cur_size_index > 0) need_shift.first -= 5;
                else need_shift.first -= 10;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                if (cur_size_index >= 3) ++need_shift.first;
                else if (cur_size_index > 0) need_shift.first += 5;
                else need_shift.first += 10;
            }
            else if (event.key.code == sf::Keyboard::A) animations = !animations;
            else if (event.key.code == sf::Keyboard::L) draw_lines = !draw_lines;*/
        }
        else if (event.type == sf::Event::MouseWheelMoved) {/*
            if (event.mouseWheel.delta > 0 && cur_size_index < 6) ++cur_size_index;
            else if (event.mouseWheel.delta < 0 && cur_size_index > 0) --cur_size_index;*/
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < WINDOW_WIDTH && mousePos.y >= 0 && mousePos.y <= WINDOW_HEIGHT) {
                window.setTitle("Mandelbrot [0.1] - counting");

                pos.x -= (mousePos.x - WINDOW_WIDTH / 2.0) / size;
                pos.y += (mousePos.y - WINDOW_HEIGHT / 2.0) / size;
                size *= 4;

                for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
                    eventProcess(window);
                    for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
                        double x = (j - WINDOW_WIDTH / 2.0) / size - pos.x;
                        double y = (i - WINDOW_HEIGHT / 2.0) / size - pos.y;
                        uint16_t iterations = juliaSet.countIterations(Complex(x, y), ITERATIONS_LIMIT);

                        if (iterations == ITERATIONS_LIMIT) {
                            setPixel(i, j, 0);
                        }
                        else {
                            setPixel(i, j, HSVtoRGB(iterations, 75, 75));
                        }
                    }
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
                    window.display();
                }
                window.setTitle("Mandelbrot [0.1]");
                window.requestFocus();
            }


            /*if (start_mouse_pos.first >= 0 && start_mouse_pos.second >= 0) {
                need_shift.first -= (mouse_pos.x - start_mouse_pos.first) / cur_size;
                need_shift.second += (mouse_pos.y - start_mouse_pos.second) / cur_size;
            }
            start_mouse_pos.first = mouse_pos.x;
            start_mouse_pos.second = mouse_pos.y;*/
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < WINDOW_WIDTH && mousePos.y >= 0 && mousePos.y <= WINDOW_HEIGHT) {
                window.setTitle("Mandelbrot [0.1] - counting");

                pos.x -= (mousePos.x - WINDOW_WIDTH / 2.0) / size;
                pos.y += (mousePos.y - WINDOW_HEIGHT / 2.0) / size;
                size /= 4;

                for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
                    eventProcess(window);
                    for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
                        double x = (j - WINDOW_WIDTH / 2.0) / size - pos.x;
                        double y = (i - WINDOW_HEIGHT / 2.0) / size - pos.y;
                        uint16_t iterations = juliaSet.countIterations(Complex(x, y), ITERATIONS_LIMIT);

                        if (iterations == ITERATIONS_LIMIT) {
                            setPixel(i, j, 0);
                        }
                        else {
                            setPixel(i, j, HSVtoRGB(iterations, 75, 75));
                        }
                    }
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
                    window.display();
                }
                window.setTitle("Mandelbrot [0.1]");
                window.requestFocus();
            }
        }
        else if (sf::Event::MouseButtonReleased) {
            start_mouse_pos.first = -1;
            start_mouse_pos.second = -1;/*
            need_shift.first = std::round(need_shift.first);
            need_shift.second = std::round(need_shift.second);*/
        }
    }
    return;
}

int main() {
    sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot [0.1]", sf::Style::Close);
    window.setActive(true);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
        eventProcess(window);
        for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
            double x = (j - WINDOW_WIDTH / 2.0) / size - pos.x;
            double y = (i - WINDOW_HEIGHT / 2.0) / size - pos.y;
            uint16_t iterations = juliaSet.countIterations(Complex(x, y), ITERATIONS_LIMIT);

            if (iterations == ITERATIONS_LIMIT) {
                setPixel(i, j, 0);
            }
            else {
                setPixel(i, j, HSVtoRGB(iterations, 75, 75));
            }
        }
        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
        window.display();
    }
    window.requestFocus();

    while (window.isOpen()) {
        /*
        std::chrono::duration<double> t = std::chrono::system_clock::now().time_since_epoch();
        if (time > 0) {
            double fps = 1 / (t.count() - time);
            animation_speed = std::abs(animation_coefficient * fps / 60);
            window.setTitle("Practical 1 (x: " + std::to_string((int)std::round(cur_shift.first)) +
                ", y: " + std::to_string((int)std::round(cur_shift.second)) +
                ", " + std::to_string((int)std::round(cur_size)) + " pixels per unit, " +
                std::to_string((int)fps) + " fps)");
        }
        time = t.count();
        */

        //glClear(GL_COLOR_BUFFER_BIT);

        eventProcess(window);

        /*
        for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
            for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
                double x = (j - WINDOW_WIDTH / 2.0) / size - pos.x;
                double y = (i - WINDOW_HEIGHT / 2.0) / size - pos.y;
                uint16_t iterations = juliaSet.countIterations(Complex(x, y), ITERATIONS_LIMIT);

                if (iterations == ITERATIONS_LIMIT) {
                    setPixel(i, j, 0);
                }
                else {
                    setPixel(i, j, HSVtoRGB(iterations, 75, 75));
                }
            }
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
            window.display();
        }
        */
    }
    return 0;
}