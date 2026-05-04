#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
#include <complex>

using namespace sf;
using namespace std;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State { CALCULATING, DISPLAYING };

class ComplexPlane : public Drawable
{
private:
    Vector2i m_pixel_size;
    float m_aspectRatio;

    Vector2f m_plane_center;
    Vector2f m_plane_size;

    int m_zoomCount;
    State m_State;

    VertexArray m_vArray;

    Vector2f m_mouseLocation;

    virtual void draw(RenderTarget& target, RenderStates states) const;

public:
    ComplexPlane(int width, int height);

    void updateRender();
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i pixel);
    void setMouseLocation(Vector2i pixel);

    void loadText(Text& text);

    size_t countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i pixel);
};

#endif
