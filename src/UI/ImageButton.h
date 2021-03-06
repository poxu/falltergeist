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

#ifndef FALLTERGEIST_IMAGEBUTTON_H
#define FALLTERGEIST_IMAGEBUTTON_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"

// Third party includes

namespace Falltergeist
{

class ImageButton : public InteractiveSurface
{
protected:
    Surface* _releasedSurface = 0;
    Surface* _pressedSurface = 0;
    bool _pressed = false;
    bool _switchMode = false;
    void _onLeftButtonClick(MouseEvent* event);
public:
    enum ButtonType {
        TYPE_SMALL_RED_CIRCLE = 1,
        TYPE_BIG_RED_CIRCLE,
        TYPE_SKILL_TOGGLE,
        TYPE_PLUS,
        TYPE_MINUS,
        TYPE_LEFT_ARROW,
        TYPE_RIGHT_ARROW,
        TYPE_CHECKBOX
    };
    ImageButton(std::string releasedImage = 0, std::string pressedImage = 0, int x = 0, int y = 0);
    ImageButton(unsigned int type, int x = 0, int y = 0);
    ~ImageButton();
    virtual SDL_Surface* sdl_surface();
    bool pressed();
    void setPressed(bool mode);
    bool switchMode();
    void setSwitchMode(bool mode);
    void setPressedImage(std::string image);
    void setReleasedImage(std::string image);

};

}
#endif // FALLTERGEIST_IMAGEBUTTON_H
