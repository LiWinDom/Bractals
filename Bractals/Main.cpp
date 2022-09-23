#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Complex.h"
#include "Config.h"
#include "Fractal.h"

uint8_t frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];

Fractal fractals[] = {
    Fractal(
        [](const Complex& c, const Complex& coord) -> Complex {
            return Complex(0, 0);
        },
        [](const Complex& z, const Complex& c, const Complex& coord) -> Complex {
            return z * z + coord;
        },
        Complex(0, 0), sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 256
    ),
    Fractal(
        [](const Complex& c, const Complex& coord) -> Complex {
            return coord;
        },
        [](const Complex& z, const Complex& c, const Complex& coord) -> Complex {
            return z * z + c;
        },
        Complex(-0.7269, 0.1889), sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 256
    ),
    Fractal(
        [](const Complex& c, const Complex& coord) -> Complex {
            return coord;
        },
        [](const Complex& z, const Complex& c, const Complex& coord) -> Complex {
            return z * z + c;
        },
        Complex(0.285, 0.01), sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 256
    ),
    Fractal(
        [](const Complex& c, const Complex& coord) -> Complex {
            return coord;
        },
        [](const Complex& z, const Complex& c, const Complex& coord) -> Complex {
            return z * z + c;
        },
        Complex(-0.1, 0.651), sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 256
    )
};
uint8_t curFractal = 0;

void setPixel(const uint16_t& x, const uint16_t& y, const uint32_t& color) {
    frameBuffer[x][y][0] = color >> 24;
    frameBuffer[x][y][1] = color >> 16;
    frameBuffer[x][y][2] = color >> 8;
    return;
}

void setFrame(const std::vector<std::vector<std::vector<uint8_t>>>& frame) {
    for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
        for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
            frameBuffer[i][j][0] = frame[i][j][0];
            frameBuffer[i][j][1] = frame[i][j][1];
            frameBuffer[i][j][2] = frame[i][j][2];
        }
    }
    return;
}

void eventProcess(sf::Window& window) {
    static std::pair<int16_t, int16_t> start_mouse_pos = { -1, -1 };
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        else if (event.type == sf::Event::KeyPressed) {
            int8_t selected = -1;
            if (event.key.code == sf::Keyboard::Num1) selected = 0;
            else if (event.key.code == sf::Keyboard::Num2) selected = 1;
            else if (event.key.code == sf::Keyboard::Num3) selected = 2;
            else if (event.key.code == sf::Keyboard::Num4) selected = 3;
            else if (event.key.code == sf::Keyboard::Num5) selected = 4;
            else if (event.key.code == sf::Keyboard::Num6) selected = 5;
            else if (event.key.code == sf::Keyboard::Num7) selected = 6;
            else if (event.key.code == sf::Keyboard::Num8) selected = 7;
            else if (event.key.code == sf::Keyboard::Num9) selected = 8;
            else if (event.key.code == sf::Keyboard::Num0) selected = 9;
            if (selected > -1 && selected < sizeof(fractals) / sizeof(Fractal)) {
                curFractal = selected;
                setFrame(fractals[curFractal].getFrame());
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < WINDOW_WIDTH && mousePos.y >= 0 && mousePos.y <= WINDOW_HEIGHT) {
                window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + "] - counting");

                sf::Vector2<double> pos = fractals[curFractal].getPos();
                pos.x -= (mousePos.x - WINDOW_WIDTH / 2.0) / fractals[curFractal].getZoom();
                pos.y += (mousePos.y - WINDOW_HEIGHT / 2.0) / fractals[curFractal].getZoom();
                fractals[curFractal].setPos(pos);
                fractals[curFractal].setZoom(fractals[curFractal].getZoom() * 4);
                fractals[curFractal].recalc(ITERATIONS_LIMIT, [&]() -> void {
                    setFrame(fractals[curFractal].getFrame());
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
                    window.display();
                }, 10);
                setFrame(fractals[curFractal].getFrame());

                window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + ']');
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
                window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + "] - counting");

                sf::Vector2<double> pos = fractals[curFractal].getPos();
                pos.x -= (mousePos.x - WINDOW_WIDTH / 2.0) / fractals[curFractal].getZoom();
                pos.y += (mousePos.y - WINDOW_HEIGHT / 2.0) / fractals[curFractal].getZoom();
                fractals[curFractal].setPos(pos);
                fractals[curFractal].setZoom(fractals[curFractal].getZoom() / 4);
                fractals[curFractal].recalc(ITERATIONS_LIMIT, [&]() -> void {
                    setFrame(fractals[curFractal].getFrame());
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
                    window.display();
                }, 10);
                setFrame(fractals[curFractal].getFrame());

                window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + ']');
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
    try {
        std::cout << "Precalcing fractals, please wait..." << std::endl;
        for (uint8_t i = 0; i < sizeof(fractals) / sizeof(Fractal); ++i) {
            std::cout << "Precalcing fractal #" << (uint16_t)i + 1 << "...";
            fractals[i].recalc(ITERATIONS_LIMIT);
            std::cout << " Done!" << std::endl;
        }

#if !_DEBUG
        ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !DEBUG

        sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + ']', sf::Style::Close);
        window.setActive(true);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        setFrame(fractals[curFractal].getFrame());

        window.requestFocus();

        //std::async(std::launch::async, drawJulia, window);

        while (window.isOpen()) {
            eventProcess(window);

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
            window.display();
        }
    }
    catch (...) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        std::cout << "Something went wrong... We are sorry about that";
        system("pause");
    }
    return 0;
}