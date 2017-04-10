/*
DebugUtils.h - Simple debugging utilities.
Copyright (C) 2017 Marcio Ota <marcio dot ota at live dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef DEBUG
  #define DEBUG_PRINT(str)            \
  Serial.print("[DEBUG] ");           \
  Serial.print(millis());             \
  Serial.print(": ");                 \
  Serial.print(__PRETTY_FUNCTION__);  \
  Serial.print(' ');                  \
  Serial.print(__FILE__);             \
  Serial.print(':');                  \
  Serial.print(__LINE__);             \
  Serial.print(' ');                  \
  Serial.println(str);
#else
  #define DEBUG_PRINT(str)
#endif
