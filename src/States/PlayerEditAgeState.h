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

#ifndef FALLTERGEIST_PLAYEREDITAGESTATE_H
#define FALLTERGEIST_PLAYEREDITAGESTATE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class BigCounter;

class PlayerEditAgeState : public State
{
protected:
    std::shared_ptr<BigCounter> _counter;
public:
    PlayerEditAgeState();
    void init();
    ~PlayerEditAgeState();
    void onIncButtonClick(std::shared_ptr<MouseEvent> event);
    void onDecButtonClick(std::shared_ptr<MouseEvent> event);
    void onDoneButtonClick(std::shared_ptr<MouseEvent> event);
};
}

#endif // FALLTERGEIST_PLAYEREDITAGESTATE_H
