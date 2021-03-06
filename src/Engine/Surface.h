/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_SURFACE_H
#define FALLTERGEIST_SURFACE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/ResourceManager.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
class FrmFileType;
class RixFileType;
class AnimatedPalette;

class Surface
{
protected:
    SDL_Surface* _sdl_surface = 0;
    void* _owner = 0;

    int _x = 0; // x position
    int _y = 0; // y position
    int _xOffset = 0;
    int _yOffset = 0;
    bool _needRedraw = false; // surface changed? draw function will be called
    bool _visible = true; // if false - do not render
    std::vector<unsigned int>* _animatedPixels = 0;

    unsigned int _borderColor = 0; // for debugging. @TODO must be removed in future
    unsigned int _backgroundColor = 0; // for debugging @TODO must be removed in future
    void _drawBorder();
    void _copyAnimatedPixelsFrom(Surface* surface);
    void _copyAnimatedPixelsTo(Surface* surface);

public:
    static AnimatedPalette* animatedPalette;

    Surface(int width = 0, int height = 0, int x = 0, int y = 0);
    Surface(libfalltergeist::FrmFileType* frm, unsigned int direction = 0, unsigned int frame = 0);
    Surface(libfalltergeist::RixFileType* rix);
    Surface(Surface* other);
    virtual ~Surface();

    virtual void setOwner(void* owner);
    virtual void* owner();

    virtual void setX(int x);
    virtual int x();

    virtual void setXOffset(int offset);
    virtual int xOffset();

    virtual void setY(int y);
    virtual int y();

    virtual void setYOffset(int offset);
    virtual int yOffset();

    virtual void setNeedRedraw(bool needRedraw);
    virtual bool needRedraw();

    virtual void setVisible(bool visible);
    virtual bool visible();

    virtual int width();
    virtual int height();

    virtual void setPixel(int x, int y, unsigned int color);
    virtual unsigned int pixel(int x, int y);
    virtual void drawLine(int x1, int y1, int x2, int y2, unsigned int color);

    virtual SDL_Surface* sdl_surface();

    virtual void copyTo(Surface* surface);

    virtual void loadFromSurface(Surface* surface);
    virtual void loadFromBmpFile(std::string path);

    virtual void setBorderColor(unsigned int color);
    virtual unsigned int borderColor();

    virtual void setBackgroundColor(unsigned int color);
    virtual unsigned int backgroundColor();

    virtual void fill(unsigned int color);
    virtual void clear();
    virtual Surface* crop(int x = 0, int y = 0, int width = 0, int height = 0);
    virtual void think();
    virtual void draw();
    virtual void blit(Surface * surface);


};

}
#endif // FALLTERGEIST_SURFACE_H
