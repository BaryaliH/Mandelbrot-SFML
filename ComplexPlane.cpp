#include "ComplexPlane.h"
#include <sstream>
#include <cmath>

ComplexPlane::ComplexPlane(int width, int height)
{
    m_pixel_size = { width, height };
    m_aspectRatio = height / (float)width;

    m_plane_center = { 0.0f, 0.0f };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };

    m_zoomCount = 0;
    m_State = State::CALCULATING;

    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(width * height);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_State == State::CALCULATING)
    {
        int width = m_pixel_size.x;
        int height = m_pixel_size.y;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = x + y * width;

                m_vArray[index].position = Vector2f(x, y);

                Vector2f coord = mapPixelToCoords({ x, y });

                size_t count = countIterations(coord);

                Uint8 r, g, b;
                iterationsToRGB(count, r, g, b);

                m_vArray[index].color = Color(r, g, b);
            }
        }

        m_State = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;

    float scale = pow(BASE_ZOOM, m_zoomCount);

    m_plane_size.x = BASE_WIDTH * scale;
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio * scale;

    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;

    float scale = pow(BASE_ZOOM, m_zoomCount);

    m_plane_size.x = BASE_WIDTH * scale;
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio * scale;

    m_State = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i pixel)
{
    m_plane_center = mapPixelToCoords(pixel);
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i pixel)
{
    m_mouseLocation = mapPixelToCoords(pixel);
}

void ComplexPlane::loadText(Text& text)
{
    stringstream ss;

    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")";

    text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<double> z(0, 0);
    complex<double> c(coord.x, coord.y);

    size_t count = 0;

    while (abs(z) < 2.0 && count < MAX_ITER)
    {
        z = z * z + c;
        count++;
    }

    return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITER)
    {
        r = g = b = 0; // black (inside set)
    }
    else
    {
        float t = (float)count / MAX_ITER;

        r = (Uint8)(9 * (1 - t) * t * t * t * 255);
        g = (Uint8)(15 * (1 - t) * (1 - t) * t * t * 255);
        b = (Uint8)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i pixel)
{
    float x = ((pixel.x / (float)m_pixel_size.x) * m_plane_size.x)
        + (m_plane_center.x - m_plane_size.x / 2);

    float y = ((pixel.y / (float)m_pixel_size.y) * m_plane_size.y)
        + (m_plane_center.y - m_plane_size.y / 2);

    return { x, y };
}