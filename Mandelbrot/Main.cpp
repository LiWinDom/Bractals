#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Complex.h"
#include "Config.h"

uint8_t frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];

void setPixel(const uint16_t& x, const uint16_t& y, const uint32_t& color) {
    frameBuffer[x][y][0] = color >> 24;
    frameBuffer[x][y][1] = color >> 16;
    frameBuffer[x][y][2] = color >> 8;
    return;
}

void fillScreen(const uint32_t& color) {
    for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
        for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
            setPixel(i, j, color);
        }
    }
    return;
}

void eventProcess(sf::Window& window) {
    static std::pair<int16_t, int16_t> start_mouse_pos = { -1, -1 };
    sf::Event event;

    if (window.pollEvent(event)) {
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
            sf::Vector2i mouse_pos = sf::Mouse::getPosition();
            if (start_mouse_pos.first >= 0 && start_mouse_pos.second >= 0) {/*
                need_shift.first -= (mouse_pos.x - start_mouse_pos.first) / cur_size;
                need_shift.second += (mouse_pos.y - start_mouse_pos.second) / cur_size;*/
            }
            start_mouse_pos.first = mouse_pos.x;
            start_mouse_pos.second = mouse_pos.y;
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

        glClear(GL_COLOR_BUFFER_BIT);
        //fillScreen(background_color);

        eventProcess(window);
        //animationProcess();

        uint16_t x = 100, y = 1;
        for (uint16_t x = 0; x < WINDOW_WIDTH; ++x) {
            for (uint16_t y = 0; y < WINDOW_HEIGHT; ++y) {
                Complex coord(x / 100.0 - WINDOW_WIDTH / 200.0, y / 100.0 - WINDOW_HEIGHT / 200.0);
                Complex z = coord + Complex(-0.69, 0.2);
                Complex sq = z * z;
                if (sq > Complex(1, 0)) {
                    setPixel(x, y, 0xc00060FF);
                }
                else if (sq == Complex(1, 0)) {
                    setPixel(x, y, 0xc00000FF);
                }
                else {
                    setPixel(x, y, 0x000000FF);
                }
            }
        }

        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
        window.display();
    }
    return 0;
}