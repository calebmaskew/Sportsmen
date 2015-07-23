/*This function will be used by everything that requires having a long string displayed in
	a textbox of varying sizes.  If necessary, do more work later to make it more flexible*/

#pragma once

#include "globals.h"

std::vector<std::string> text_wrap(std::string original, int width/*box width*/);
