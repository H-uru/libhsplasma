/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLASMA_DEFS_H
#define _PLASMA_DEFS_H

#include "PlasmaConfig.h"

#ifdef _WIN32
  #ifdef BUILD_PLASMA_DLL
    #define PLASMA_DLL __declspec(dllexport)
  #else
    #ifdef BUILD_PLASMANET_DLL
      #define PLASMA_DLL __declspec(dllimport)
      #define PLASMANET_DLL __declspec(dllexport)
    #else
      #define PLASMA_DLL __declspec(dllimport)
      #define PLASMANET_DLL __declspec(dllimport)
    #endif
  #endif
#else
  #define PLASMA_DLL
  #define PLASMANET_DLL
#endif

#include <cstdint>
#include <cstddef>

#define HS_OVERRIDE         override
#define HS_FINAL            final
#define HS_FINAL_OVERRIDE   override final  // Prefer both to satisfy -Wsuggest-override
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#   define HS_NOEXCEPT      throw()
#   define HS_CONSTEXPR     const
#else
#   define HS_NOEXCEPT      noexcept
#   define HS_CONSTEXPR     constexpr
#endif

enum CallbackEvent
{
    kStart, kStop, kReverse, kTime, kLoop, kBegin, kEnd, kEventEnd,
    kSingleFrameAdjust, kSingleFrameEval
};

enum ControlEventCode
{
    B_CONTROL_ACTION, B_CONTROL_ACTION_MOUSE, B_CONTROL_JUMP,
    B_CONTROL_MOVE_FORWARD, B_CONTROL_MOVE_BACKWARD, B_CONTROL_STRAFE_LEFT,
    B_CONTROL_STRAFE_RIGHT, B_CONTROL_MOVE_UP, B_CONTROL_MOVE_DOWN,
    B_CONTROL_ROTATE_LEFT, B_CONTROL_ROTATE_RIGHT, B_CONTROL_ROTATE_UP,
    B_CONTROL_ROTATE_DOWN, B_CONTROL_MODIFIER_FAST, B_CONTROL_ALWAYS_RUN,
    B_CONTROL_EQUIP, B_CONTROL_DROP, B_CONTROL_TURN_TO, B_TOGGLE_DRIVE_MODE,
    B_CAMERA_MOVE_FORWARD, B_CAMERA_MOVE_BACKWARD, B_CAMERA_MOVE_UP,
    B_CAMERA_MOVE_DOWN, B_CAMERA_MOVE_LEFT, B_CAMERA_MOVE_RIGHT,
    B_CAMERA_PAN_UP, B_CAMERA_PAN_DOWN, B_CAMERA_PAN_LEFT, B_CAMERA_PAN_RIGHT,
    B_CAMERA_MOVE_FAST, B_CAMERA_ROTATE_RIGHT, B_CAMERA_ROTATE_LEFT,
    B_CAMERA_ROTATE_UP, B_CAMERA_ROTATE_DOWN, B_CAMERA_RECENTER,
    B_CAMERA_DRIVE_SPEED_UP, B_CAMERA_DRIVE_SPEED_DOWN, B_CAMERA_ZOOM_IN,
    B_CAMERA_ZOOM_OUT, B_SET_CONSOLE_MODE, B_CONTROL_CONSOLE_COMMAND,
    B_CONTROL_TOGGLE_PHYSICAL, B_CONTROL_PICK, A_CONTROL_MOVE, A_CONTROL_TURN,
    A_CONTROL_MOUSE_X, A_CONTROL_MOUSE_Y, S_SET_CURSOR_UP, S_SET_CURSOR_DOWN,
    S_SET_CURSOR_RIGHT, S_SET_CURSOR_LEFT, S_SET_CURSOR_POISED,
    S_SET_CURSOR_HIDDEN, S_SET_CURSOR_UNHIDDEN, S_SET_CURSOR_ARROW,
    S_SEARCH_FOR_PICKABLE, S_INCREASE_MIC_VOL, S_DECREASE_MIC_VOL,
    S_PUSH_TO_TALK, S_SET_THIRD_PERSON_MODE, S_SET_FIRST_PERSON_MODE,
    S_SET_WALK_MODE, S_SET_FREELOOK, S_SET_CONSOLE_SINGLE, S_SET_CONSOLE_HIDDEN,
    B_CONTROL_SET_EQUIPED_STATE, B_CONTROL_SCROLL_UP_LIST,
    B_CONTROL_SCROLL_DOWN_LIST, B_CONTROL_SET_INVENTORY_ACTIVE,
    B_CONTROL_SET_INVENTORY_DISACTIVE, B_CONTROL_REMOVE_INV_OBJECT,
    B_CONTROL_ENABLE_OBJECT, B_CONTROL_EMOTE, B_CONTROL_EXIT_MODE,
    B_CONTROL_DIVE, B_CAMERA_PAN_TO_CURSOR, B_CONTROL_OPEN_KI,
    B_CONTROL_OPEN_BOOK, B_CONTROL_EXIT_GUI_MODE, B_CONTROL_MODIFIER_STRAFE,
    B_CONTROL_CAMERA_WALK_PAN, S_SET_BASIC_MODE, B_CONTROL_IGNORE_AVATARS,
    B_CONTROL_LADDER_INVERTED, B_CONTROL_CONSUMABLE_JUMP, S_SET_WALK_BACK_MODE,
    S_SET_WALK_BACK_LB_MODE, S_SET_CURSOR_UPWARD, S_SET_LADDER_CONTROL,
    S_CLEAR_LADDER_CONTROL, END_CONTROLS
};

template <typename T, size_t Size>
HS_CONSTEXPR size_t hsArraySize(T(&)[Size])
{
    return Size;
}

#endif
