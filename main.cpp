#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace sf;

int main()
{
    int width = 800;
    int height = 600;

    RenderWindow window(VideoMode(width, height), "Mandelbrot");

    ComplexPlane complexPlane(width, height);

    Font font;
    font.loadFromFile("arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(Mouse::getPosition(window));
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(Mouse::getPosition(window));
                }
            }

            if (event.type == Event::MouseMoved)
            {
                complexPlane.setMouseLocation(Mouse::getPosition(window));
            }
        }

        complexPlane.updateRender();
        complexPlane.loadText(text);

        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}