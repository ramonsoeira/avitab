/*
 *   AviTab - Aviator's Virtual Tablet
 *   Copyright (C) 2018 Folke Will <folko@solhost.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "Window.h"
#include <stdexcept>

namespace avitab {

Window::Window(WidgetPtr parent, const std::string& title):
    Widget(parent)
{
    lv_obj_t *win = lv_win_create(parentObj(), nullptr);
    lv_win_set_title(win, title.c_str());
    lv_obj_set_free_ptr(win, this);

    setObj(win);
}

void avitab::Window::hideScrollbars() {
    lv_win_set_sb_mode(obj(), LV_SB_MODE_OFF);
}

int Window::getContentWidth() {
    return lv_win_get_width(obj());
}

void Window::setOnClose(WindowCallback cb) {
    addSymbol(Symbol::CLOSE, cb);
}

void Window::addSymbol(Symbol smb, WindowCallback cb) {
    callbacks[smb] = cb;

    const void *lvSymbol = symbolToLVSymbol(smb);
    if (!lvSymbol) {
        throw std::runtime_error("Invalid symbol passed to window");
    }

    lv_obj_t *btn = lv_win_add_btn(obj(), lvSymbol, [] (lv_obj_t *btn) -> lv_res_t {
        lv_obj_t *winObj = lv_win_get_from_btn(btn);
        Window *winCls = reinterpret_cast<Window *>(lv_obj_get_free_ptr(winObj));
        int smbInt = lv_obj_get_free_num(btn);

        if (winCls) {
            winCls->callbacks[static_cast<Symbol>(smbInt)]();
        }

        return LV_RES_OK;
    });
    lv_obj_set_free_num(btn, static_cast<size_t>(smb));
}

const void* Window::symbolToLVSymbol(Symbol symbol) {
    switch (symbol) {
    case Symbol::CLOSE:     return SYMBOL_CLOSE;
    case Symbol::LEFT:      return SYMBOL_LEFT;
    case Symbol::RIGHT:     return SYMBOL_RIGHT;
    case Symbol::UP:        return SYMBOL_UP;
    case Symbol::DOWN:      return SYMBOL_DOWN;
    case Symbol::PREV:      return SYMBOL_PREV;
    case Symbol::NEXT:      return SYMBOL_NEXT;
    case Symbol::PLUS:      return SYMBOL_PLUS;
    case Symbol::MINUS:     return SYMBOL_MINUS;
    default:                return nullptr;
    }
}

} /* namespace avitab */

void Window::clearContent() {
}