#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Complex.h"
#include "Config.h"
#include "Fractal.h"
#include "Frame.h"

struct Shape {
public:
    Shape(const std::vector<sf::Vector2<double>>& vertexes, const uint32_t& color) {
        this->vertexes = vertexes;
        this->color = color;
    }

    std::vector<sf::Vector2<double>> vertexes;
    uint32_t color;
};

uint8_t frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
std::vector<Shape> shapeBuffer;

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

int8_t getSign(const int64_t& num) {
    if (num == 0) return 0;
    return std::abs(num) / num;
}

void setFrame(const std::vector<std::vector<std::vector<uint8_t>>>& frame) {
    for (uint16_t i = 0; i < WINDOW_HEIGHT; ++i) {
        for (uint16_t j = 0; j < WINDOW_WIDTH; ++j) {
            frameBuffer[i][j][0] = frame[i][j][0];
            frameBuffer[i][j][1] = frame[i][j][1];
            frameBuffer[i][j][2] = frame[i][j][2];
        }
    }
    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
    return;
}

void drawShape(const Shape& shape) {
    glBegin(GL_LINE_LOOP);
    glColor4ub(shape.color >> 24, shape.color >> 16, shape.color >> 8, shape.color);
    for (uint16_t i = 0; i < shape.vertexes.size(); ++i) {
        glVertex2f(shape.vertexes[i].x / WINDOW_WIDTH * 2 - 1, shape.vertexes[i].y / WINDOW_HEIGHT * 2 - 1);
    }
    glEnd();
    glFlush();
    return;
}

void drawShapeBuffer() {
    for (uint8_t i = 0; i < shapeBuffer.size(); ++i) {
        drawShape(shapeBuffer[i]);
    }
    return;
}

void eventProcessing(sf::Window& window, const bool& limited);

void fractalRecalc(sf::Window& window, const int16_t& x1, const int16_t& y1, const int16_t& x2, const int16_t& y2) {
    window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + "] - counting");
    if (x1 > 0 && y1 > 0 && x2 > 0 && y2 > 0 && x1 < WINDOW_WIDTH && y1 < WINDOW_HEIGHT && x2 < WINDOW_WIDTH && y2 < WINDOW_HEIGHT) {
        fractals[curFractal].setFrame(frame::resize(fractals[curFractal].getFrame(), std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)));
    }
    setFrame(fractals[curFractal].getFrame());
    window.display();

    sf::Vector2<double> center(x1 + (x2 - x1) / 2.0, y1 + (y2 - y1) / 2.0);
    sf::Vector2<double> pos = fractals[curFractal].getPos();
    pos.x -= (center.x - WINDOW_WIDTH / 2.0) / fractals[curFractal].getZoom();
    pos.y -= (center.y - WINDOW_HEIGHT / 2.0) / fractals[curFractal].getZoom();
    fractals[curFractal].setPos(pos);
    fractals[curFractal].setZoom(fractals[curFractal].getZoom() * std::min((double)WINDOW_WIDTH / std::abs(x2 - x1), (double)WINDOW_HEIGHT / std::abs(y2 - y1)));
    fractals[curFractal].recalc(ITERATIONS_LIMIT, [&]() -> void {
        eventProcessing(window, true);
        setFrame(fractals[curFractal].getFrame());
        window.display();
        }, WINDOW_HEIGHT / 20);
    setFrame(fractals[curFractal].getFrame());
    window.setTitle(PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + ']');
    window.requestFocus();
    return;
}

void eventProcessing(sf::Window& window, const bool& limited = false) {
    static std::string mouseButton = "none";
    static sf::Vector2i startMousePos = { -1, -1 };
    static sf::Vector2i curMousePos = { -1, -1 };
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if (limited == true) {
            break;
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
    }
    if (limited == true) {
        return;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mouseButton == "none" || mouseButton == "left") {
            curMousePos = sf::Mouse::getPosition(window);

            if (curMousePos != sf::Vector2i(-1, -1)) {
                if (startMousePos == sf::Vector2i(-1, -1)) {
                    startMousePos = curMousePos;
                }

                sf::Vector2i shift(std::abs(startMousePos.x - curMousePos.x), std::abs(startMousePos.y - curMousePos.y));
                if ((double)shift.x / WINDOW_WIDTH < (double)shift.y / WINDOW_HEIGHT) {
                    shift.y = (double)shift.x / WINDOW_WIDTH * WINDOW_HEIGHT;
                }
                else {
                    shift.x = (double)shift.y / WINDOW_HEIGHT * WINDOW_WIDTH;
                }
                shapeBuffer.push_back(Shape({ sf::Vector2<double>(startMousePos.x - shift.x, WINDOW_HEIGHT - startMousePos.y - shift.y), sf::Vector2<double>(startMousePos.x + shift.x, WINDOW_HEIGHT - startMousePos.y - shift.y), sf::Vector2<double>(startMousePos.x + shift.x, WINDOW_HEIGHT - startMousePos.y + shift.y), sf::Vector2<double>(startMousePos.x - shift.x, WINDOW_HEIGHT - startMousePos.y + shift.y) },
                    0xFFFFFFFF));
            }
        }
        mouseButton = "left";
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (mouseButton == "none") {
            curMousePos = sf::Mouse::getPosition(window);
            if (curMousePos.x >= 0 && curMousePos.x < WINDOW_WIDTH && curMousePos.y >= 0 && curMousePos.y <= WINDOW_HEIGHT) {
                fractalRecalc(window, curMousePos.x - WINDOW_WIDTH * 2, curMousePos.y - WINDOW_HEIGHT * 2, curMousePos.x + WINDOW_WIDTH * 2, curMousePos.y + WINDOW_HEIGHT * 2);
            }
            mouseButton = "right";
        }
    }
    else if (sf::Event::MouseButtonReleased) {
        if (curMousePos.x >= 0 && curMousePos.x < WINDOW_WIDTH && curMousePos.y >= 0 && curMousePos.y <= WINDOW_HEIGHT) {
            if (mouseButton == "left") {
                sf::Vector2i shift(std::abs(startMousePos.x - curMousePos.x), std::abs(startMousePos.y - curMousePos.y));
                if (shift.x > 0 && shift.y > 0) {
                    if ((double)shift.x / WINDOW_WIDTH < (double)shift.y / WINDOW_HEIGHT) {
                        shift.y = (double)shift.x / WINDOW_WIDTH * WINDOW_HEIGHT;
                    }
                    else {
                        shift.x = (double)shift.y / WINDOW_HEIGHT * WINDOW_WIDTH;
                    }
                    fractalRecalc(window, startMousePos.x - shift.x, WINDOW_HEIGHT - startMousePos.y - shift.y, startMousePos.x + shift.x, WINDOW_HEIGHT - startMousePos.y + shift.y);
                }
            }
        }
        mouseButton = "none";
        curMousePos = sf::Vector2i(-1, -1);
        startMousePos = sf::Vector2i(-1, -1);
    }
    return;
}

int main() {
    try {
        std::cout << "Precalculating fractals, please wait..." << std::endl;
        for (uint8_t i = 0; i < sizeof(fractals) / sizeof(Fractal); ++i) {
            std::cout << "Precalculating fractal #" << (uint16_t)i + 1 << "...";
            fractals[i].recalc(ITERATIONS_LIMIT);
            std::cout << " Done!" << std::endl;
        }

#if !_DEBUG
        ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !DEBUG

        sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), PROGRAM_NAME + std::string(" [") + PROGRAM_VERSION + ']', sf::Style::Close);
        window.setActive(true);

        glEnable(GL_TEXTURE_2D);
        setFrame(fractals[curFractal].getFrame());
        window.requestFocus();

        while (window.isOpen()) {
            shapeBuffer.clear();
            eventProcessing(window);

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, &frameBuffer);
            drawShapeBuffer();
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