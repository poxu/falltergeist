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
 *
 */

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Engine/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameObject.h"
#include "../States/LocationState.h"
#include "../States/CursorDropdownState.h"
#include "../Engine/Mouse.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
}

LocationState::~LocationState()
{
    _game->setLocation(0);
}

void LocationState::init()
{
    if (initialized()) return;
    State::init();
    setScrollable(true);

    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));
    _game->setLocation(_location);
    _game->mouse()->setType(Mouse::ACTION);
    _background = new InteractiveSurface(_location->tilesBackground());
    _background->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onBackgroundClick);
    _background->addEventHandler("keyup", this, (EventRecieverMethod) &LocationState::onKeyUp);

    add(_background);
}

void LocationState::onMouseDown(MouseEvent* event)
{
    auto sender = dynamic_cast<InteractiveSurface*>(event->emitter());
    if (!sender) return;
    auto object = dynamic_cast<GameObject*>((GameObject*)sender->owner());
    if (!object) return;

    std::vector<int> icons;

    switch(object->type())
    {
        case GameObject::TYPE_DUDE:
            icons.push_back(Mouse::ICON_ROTATE);
            break;
        case GameObject::TYPE_SCENERY:
            icons.push_back(Mouse::ICON_LOOK);
            break;
        case GameObject::TYPE_CRITTER:
            icons.push_back(Mouse::ICON_TALK);
            break;
        default:
            return;
    }
    icons.push_back(Mouse::ICON_INVENTORY);
    icons.push_back(Mouse::ICON_SKILL);
    icons.push_back(Mouse::ICON_CANCEL);

    auto state = new CursorDropdownState(icons);
    state->setObject(object);
    _game->pushState(state);

}

void LocationState::onBackgroundClick(MouseEvent* event)
{
    int x = _location->camera()->x() + event->x();
    int y = _location->camera()->y() + event->y();
    unsigned int hexagon = _location->positionToHexagon(x, y);

    //std::cout << std::dec << x << " : " << y << " > " << hexagon << std::endl;
}

void LocationState::onObjectClick(MouseEvent* event)
{
    auto surface = dynamic_cast<InteractiveSurface*>(event->emitter());
    if (!surface) return;
    auto object = dynamic_cast<GameObject*>((GameObject*)surface->owner());
    if (!object) return;
        std::cout << "object: " << object->PID()
                  << "name: " << object->name()
                  << "description: " << object->description() << std::endl;
}

void LocationState::onKeyUp(KeyboardEvent * event)
{

    if (event->keyCode() == SDLK_g) // "g" button - enable\disable hex grid
    {
        if (_hexagonalGrid)
        {
            _hexagonalGrid = false;
        }
        else
        {
            _hexagonalGrid = true;
        }
    }

}

void LocationState::blit()
{

    _location->generateBackground();
    _background->loadFromSurface(_location->tilesBackground());
    State::blit();

    if (_location == 0) return;

    _drawHexagonalGrid();


    for (GameObject* object : *_location->objectsToRender())
    {        
        int x, y;
        if (Animation* animation = object->animationQueue()->animation())
        {
            x = Location::hexagonToX(object->position()) - animation->surfaces()->at(0)->width()/2 - _location->camera()->x();
            y = Location::hexagonToY(object->position()) - animation->surfaces()->at(0)->height() - _location->camera()->y();
            animation->setX(x);
            animation->setY(y);
            animation->blit(_game->screen()->surface());

        }
        else
        {
            auto surface = object->surface();
            x = Location::hexagonToX(object->position()) - surface->width()/2 - _location->camera()->x();
            y = Location::hexagonToY(object->position()) - surface->height() - _location->camera()->y();
            surface->setX(x);
            surface->setY(y);
            surface->blit(_game->screen()->surface());
        }
   }
}

void LocationState::_drawHexagonalGrid()
{
    if (!_hexagonalGrid) return;
    Surface * hexagon = ResourceManager::surface("art/intrface/msef000.frm");
    hexagon->setXOffset(0 - hexagon->width()/2);
    hexagon->setYOffset(0 - hexagon->height()/2);
    for (unsigned int i = 0; i != 200*200; ++i)
    {
        int x = _location->hexagonToX(i) - _location->camera()->x();
        int y = _location->hexagonToY(i) - _location->camera()->y();
        hexagon->setX(x);
        hexagon->setY(y);
        hexagon->blit(_game->screen()->surface());
    }
}

void LocationState::think()
{

    if (!_location) return;
    _location->think();

    for(GameObject* object : *_location->objectsToRender())
    {

        if (Animation* animation = object->animationQueue()->animation())
        {

            animation->removeEventHandlers("mouseleftdown");
            animation->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onMouseDown);
            animation->removeEventHandlers("mouseleftclick");
            animation->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onObjectClick);
            animation->setOwner(object);
        }
        else
        {
            object->surface()->removeEventHandlers("mouseleftdown");
            object->surface()->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onMouseDown);
            object->surface()->removeEventHandlers("mouseleftclick");
            object->surface()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onObjectClick);
            object->surface()->setOwner(object);
        }
    }
}

void LocationState::handle(Event* event)
{
    if (auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        // Handle objects
        for (auto object : *_location->objectsToRender())
        {            
            if (Animation* animation = object->animationQueue()->animation())
            {
                animation->handle(mouseEvent);
            }
            else
            {
                object->surface()->handle(mouseEvent);
            }
        }
        State::handle(mouseEvent);
    }
    else
    {
        State::handle(event);
    }
}

}
