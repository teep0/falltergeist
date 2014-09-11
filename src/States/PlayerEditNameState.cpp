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
#include <ctype.h>
#include <iostream>

// Falltergeist includes
#include "../States/PlayerEditNameState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"
#include "../Game/GameDudeObject.h"
#include "../UI/Image.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

PlayerEditNameState::PlayerEditNameState() : State()
{
}

void PlayerEditNameState::init()
{
    State::init();
    setFullscreen(false);
    
    _keyCodes.insert(std::make_pair(SDLK_a, 'a'));
    _keyCodes.insert(std::make_pair(SDLK_b, 'b'));
    _keyCodes.insert(std::make_pair(SDLK_c, 'c'));
    _keyCodes.insert(std::make_pair(SDLK_d, 'd'));
    _keyCodes.insert(std::make_pair(SDLK_e, 'e'));
    _keyCodes.insert(std::make_pair(SDLK_f, 'f'));
    _keyCodes.insert(std::make_pair(SDLK_g, 'g'));
    _keyCodes.insert(std::make_pair(SDLK_h, 'h'));
    _keyCodes.insert(std::make_pair(SDLK_i, 'i'));
    _keyCodes.insert(std::make_pair(SDLK_j, 'j'));
    _keyCodes.insert(std::make_pair(SDLK_k, 'k'));
    _keyCodes.insert(std::make_pair(SDLK_l, 'l'));
    _keyCodes.insert(std::make_pair(SDLK_m, 'm'));
    _keyCodes.insert(std::make_pair(SDLK_n, 'n'));
    _keyCodes.insert(std::make_pair(SDLK_o, 'o'));
    _keyCodes.insert(std::make_pair(SDLK_p, 'p'));
    _keyCodes.insert(std::make_pair(SDLK_q, 'q'));
    _keyCodes.insert(std::make_pair(SDLK_r, 'r'));
    _keyCodes.insert(std::make_pair(SDLK_s, 's'));
    _keyCodes.insert(std::make_pair(SDLK_t, 't'));
    _keyCodes.insert(std::make_pair(SDLK_u, 'u'));
    _keyCodes.insert(std::make_pair(SDLK_v, 'v'));
    _keyCodes.insert(std::make_pair(SDLK_w, 'w'));
    _keyCodes.insert(std::make_pair(SDLK_x, 'x'));
    _keyCodes.insert(std::make_pair(SDLK_y, 'y'));
    _keyCodes.insert(std::make_pair(SDLK_z, 'z'));
    _keyCodes.insert(std::make_pair(SDLK_1, '1'));
    _keyCodes.insert(std::make_pair(SDLK_2, '2'));
    _keyCodes.insert(std::make_pair(SDLK_3, '3'));
    _keyCodes.insert(std::make_pair(SDLK_4, '4'));
    _keyCodes.insert(std::make_pair(SDLK_5, '5'));
    _keyCodes.insert(std::make_pair(SDLK_6, '6'));
    _keyCodes.insert(std::make_pair(SDLK_7, '7'));
    _keyCodes.insert(std::make_pair(SDLK_8, '8'));
    _keyCodes.insert(std::make_pair(SDLK_9, '9'));
    _keyCodes.insert(std::make_pair(SDLK_0, '0'));

    _timer = SDL_GetTicks();

    auto bg = std::shared_ptr<Image>(new Image("art/intrface/charwin.frm"));
    bg->setX(22);
    bg->setY(0);

    auto nameBox = std::shared_ptr<Image>(new Image("art/intrface/namebox.frm"));
    nameBox->setX(35);
    nameBox->setY(10);

    auto doneBox = std::shared_ptr<Image>(new Image("art/intrface/donebox.frm"));
    doneBox->setX(35);
    doneBox->setY(40);

    auto msg = ResourceManager::msgFileType("text/english/game/editor.msg");
    auto doneLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(100), 65, 43));
    auto font3_b89c28ff = ResourceManager::font("font3.aaf", 0xb89c28ff);
    doneLabel->setFont(font3_b89c28ff);

    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 45, 43));
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditNameState::onDoneButtonClick);

    _name = std::shared_ptr<TextArea>(new TextArea(_game->player()->name(), 43, 15));
    _name->addEventHandler("keyup", this, (EventRecieverMethod) &PlayerEditNameState::onKeyboardPress);

    _cursor = std::shared_ptr<Image>(new Image(5, 8));
    _cursor->setX(83);
    _cursor->setY(15);
    _cursor->texture()->fill(0x3FF800FF);

    add(bg);
    add(nameBox);
    add(doneBox);
    add(doneLabel);
    add(doneButton);
    add(_name);
    add(_cursor);
}

void PlayerEditNameState::onKeyboardPress(std::shared_ptr<KeyboardEvent> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto state = dynamic_cast<PlayerEditNameState*>(event->reciever());

    std::string text = sender->text();

    if (event->keyCode() == SDLK_BACKSPACE) //backspace
    {
        if (text.length() > 0)
        {
            text = text.substr(0, text.length() - 1);
            sender->setText(text.c_str());
            return;
        }
        return;
    }

    if (event->keyCode() == SDLK_RETURN) //enter
    {
        auto mouseEvent = std::shared_ptr<MouseEvent>(new MouseEvent());
        mouseEvent->setEmitter(event->emitter());
        mouseEvent->setReciever(event->reciever());
        return onDoneButtonClick(mouseEvent);
    }

    if (event->keyCode() == SDLK_LSHIFT || event->keyCode() == SDLK_RSHIFT) return;
    if (event->keyCode() == SDLK_LCTRL || event->keyCode() == SDLK_RCTRL) return;
    if (event->keyCode() == SDLK_LALT || event->keyCode() == SDLK_RALT) return;

    if (text.length() == 11) return;

    if (state->_keyCodes.find(event->keyCode()) != state->_keyCodes.end())
    {
        char chr = state->_keyCodes.at(event->keyCode());

        if (event->shiftPressed())
        {
            text += toupper(chr);
        }
        else
        {
            text += chr;
        }
        sender->setText(text.c_str());
    }
}

void PlayerEditNameState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{    
    auto state = dynamic_cast<PlayerEditNameState*>(event->reciever());
    std::string text(state->_name->text());
    if (text.length() > 0)
    {
        Game::getInstance()->player()->setName(text.c_str());
    }
    Game::getInstance()->popState();
}

PlayerEditNameState::~PlayerEditNameState()
{
}

void PlayerEditNameState::think()
{   
    State::think();
    if (SDL_GetTicks() - _timer > 300)
    {
        if (_cursor->visible())
        {
            _cursor->setVisible(false);
        }
        else
        {
            _cursor->setVisible(true);
        }
        _timer = SDL_GetTicks();
    }

    _cursor->setX(_name->width() + 45);
}

}
