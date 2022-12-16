#pragma once
#include "SoundPlex.h"

namespace cdc {

class SoundPlexSequence : public SoundPlex {
public:
	SoundPlexSequence(
		void *data,
		Controls *controls,
		Controls3d *controls3d,
		SoundOwner *owner)
	:
		SoundPlex(controls, controls3d, owner)
	{
		// TODO
	}
};

}
