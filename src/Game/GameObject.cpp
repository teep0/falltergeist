/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// Falltergeist includes
#include "../Engine/Graphics/Animation.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameObject.h"
#include "../Game/GameDefines.h"
#include "../Engine/Exception.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

GameObject::GameObject() : EventReciever()
{
}

GameObject::~GameObject()
{
}

int GameObject::type()
{
    return _type;
}

int GameObject::subtype()
{
    return _subtype;
}

int GameObject::PID()
{
    return _PID;
}

void GameObject::setPID(int value)
{
    _PID = value;
}

int GameObject::FID()
{
    return _FID;
}

void GameObject::setFID(int value)
{
    _FID = value;
}

int GameObject::position()
{
    return _position;
}

void GameObject::setPosition(int value)
{
    _position = value;
}

int GameObject::elevation()
{
    return _elevation;
}

void GameObject::setElevation(int value)
{
    if (value < 0 || value > 3)
    {
        throw Exception("GameObject::setElevation() - value out of range: " + std::to_string(value));
    }
    _elevation = value;
}

int GameObject::orientation()
{    
    return _orientation;
}

void GameObject::setOrientation(int value)
{
    if (value < 0 || value > 5)
    {
        throw Exception("GameObject::setOrientation() - value out of range: " + std::to_string(value));
    }

    if (_orientation == value) return;

    _orientation = value;
}

std::string GameObject::name()
{
    return _name;
}

void GameObject::setName(std::string value)
{
    _name = value;
}

std::string GameObject::description()
{
    return _description;
}

void GameObject::setDescription(std::string value)
{
    _description = value;
}

std::vector<VM*>* GameObject::scripts()
{
    return &_scripts;
}

std::shared_ptr<Location> GameObject::location()
{
    return _location;
}

void GameObject::setLocation(std::shared_ptr<Location> value)
{
    _location = value;
}

std::shared_ptr<ActiveUI> GameObject::ui()
{
    if (_ui) return _ui;

    auto frm = ResourceManager::frmFileType(FID());
    if (frm)
    {
        if (frm->framesPerDirection() > 1)
        {
            _ui = std::shared_ptr<Animation>(new Animation(ResourceManager::FIDtoFrmName(FID()), this->orientation()));
        }
        else
        {
            _ui = std::shared_ptr<Image>(new Image(frm, orientation()));
        }
    }

    return _ui;
}

}
