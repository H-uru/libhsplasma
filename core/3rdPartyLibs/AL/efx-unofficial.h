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

#ifndef _EFX_UNOFFICIAL_H
#define _EFX_UNOFFICIAL_H

/* Reverberation flags:
* Those appear to come from eax.h in the original EAX library by Creative Technology.
* They should be usable with EAXREVERBPROPERTIES::ulFlags, however, OpenAL EFX does NOT define those constants.
* It is unknown whether OpenAL EFX actually supports these flags. Use with caution.
*/

// These flags determine what properties are affected by environment size.

// Reverberation decay time
#define EAXLISTENERFLAGS_DECAYTIMESCALE        0x00000001
// Reflection level
#define EAXLISTENERFLAGS_REFLECTIONSSCALE      0x00000002
// Initial reflection delay time
#define EAXLISTENERFLAGS_REFLECTIONSDELAYSCALE 0x00000004
// Reflections level
#define EAXLISTENERFLAGS_REVERBSCALE           0x00000008
// Late reverberation delay time
#define EAXLISTENERFLAGS_REVERBDELAYSCALE      0x00000010
// Echo time
#define EAXLISTENERFLAGS_ECHOTIMESCALE         0x00000040
// Modulation time
#define EAXLISTENERFLAGS_MODULATIONTIMESCALE   0x00000080
// Limit unnaturally long decay times of high-frequency sounds by forcing a limit to the decay time to be calculated from the Air Absorption HF value
#define EAXLISTENERFLAGS_DECAYHFLIMIT          0x00000020

// Reserved future use
#define EAXLISTENERFLAGS_RESERVED              0xFFFFFF00

#define EAXLISTENER_DEFAULTFLAGS (EAXLISTENERFLAGS_DECAYTIMESCALE |        \
	                              EAXLISTENERFLAGS_REFLECTIONSSCALE |      \
	                              EAXLISTENERFLAGS_REFLECTIONSDELAYSCALE | \
	                              EAXLISTENERFLAGS_REVERBSCALE |           \
	                              EAXLISTENERFLAGS_REVERBDELAYSCALE |      \
	                              EAXLISTENERFLAGS_DECAYHFLIMIT)

#endif
