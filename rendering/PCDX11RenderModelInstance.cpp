#include "PCDX11RenderModelInstance.h"
#include "PCDX11ModelDrawable.h"
#include "PCDX11RenderDevice.h"
// #include <cstdio>

namespace cdc {

void PCDX11RenderModelInstance::recordDrawables() {
	// TODO
	uint32_t baseMask = this->baseMask;
	if (baseMask == 0)
		return;
	bool addToNextScene = false;
	Mesh *mesh = getRenderModel()->getMesh();
	uint32_t tab0index = 0;
	for (uint32_t i=0; i<mesh->meshCount; i++) {
		MeshSub *sub = &mesh->meshTable[i];
		for (uint32_t j=0; j<mesh->table0Count; j++, tab0index++) {
			// printf("PCDX11RenderModelInstance::recordDrawables %d %d %d\n", i, j, tab0index);
			MeshTab0 *tab0 = &mesh->table0[tab0index];
			// MeshTab0Ext16 *tab0ext16 = this->tab0Ext16[tab0index];

			uint32_t mask = baseMask; // & tab0ext16->mask8;
			auto drawable = new PCDX11ModelDrawable(
				getRenderModel(),
				sub,
				tab0);
			renderDevice->recordDrawable(drawable, mask, addToNextScene);
		}
	}
}

}