## Preview

![Mandelbrot Screenshot](screenshot.png)

\# Mandelbrot Fractal (SFML, C++)



\## Overview

This project renders the Mandelbrot set using C++ and SFML.  

It maps screen pixels to the complex plane and computes iteration counts to visualize the fractal.



\## Features

\- Real-time rendering using SFML

\- Zoom in/out using mouse clicks

\- Dynamic center repositioning

\- Iteration-based coloring



\## Controls

\- Left Click: Zoom in

\- Right Click: Zoom out

\- Move Mouse: Display coordinates



\## How It Works

Each pixel is mapped to a complex number.  

The function `z = z^2 + c` is iterated until it escapes or reaches a max iteration count.



\## Requirements

\- SFML installed

\- C++ compiler (Visual Studio recommended)



\## Notes

\- The project uses a VertexArray for efficient pixel rendering

\- Iteration count affects visual detail



