#include "Inspector.h"
#include "3rdParty/imgui/imgui.h"
#include "cdc/dtp/objectproperties/intro.h"
#include "game/DeferredRenderingObject.h"
#include "game/LensFlareAndCoronaID.h"
#include "rendering/CommonMaterial.h"
#include "rendering/MaterialData.h"
#include "cdcResource/ResolveSection.h"
#include "cdcSound/SoundPlex.h"
#include "cdcObjects/Object.h"
#include "cdcObjects/ObjectManager.h"
#include "cdcWorld/Instance.h"
#include "UIActions.h"

void buildUI(UIActions& uiact, DeferredRenderingExtraData *extra) {
	// material
	if (extra->material)
		if (ImGui::SmallButton("show override material"))
			uiact.select(extra->material);

	// scale
	ImGui::Text("scale mode %d",
		extra->scaleModeE1);
	if (extra->scaleModeE1 == 1)
		ImGui::SliderFloat("Scale", extra->scale, 0, 10000.f);
	else
		ImGui::SliderFloat3("Scale", extra->scale, 0, 10000.f);

	// packed[...]
	const char *labels_packed[] = {"packed[0]", "packed[1]", "packed[2]", "packed[3]"};
	uint8_t v[4]; uint8_t minmax[] = {0, 255};
	for (uint32_t i=0; i<4; i++) {
		memcpy(v, &extra->packedVectors[i].bytes, 4);
		ImGui::SliderScalarN(labels_packed[i], ImGuiDataType_U8, v, 4, minmax+0, minmax+1, "%u");
		memcpy(&extra->packedVectors[i].bytes, v, 4);
	}

	// plain[...]
	const char *labels_plain[] = {"plain[0]", "plain[1]", "plain[2]", "plain[3]"};
	for (uint32_t i=0; i<4; i++) {
		ImGui::SliderFloat4(labels_plain[i], extra->plainVectors[i].vec128, 0.f, 10.f);
	}

	// params
	const char *modes[] = {
		"packed[0]",
		"packed[1]",
		"packed[2]",
		"packed[3]",
		"plain[0]",
		"plain[1]",
		"plain[2]",
		"plain[3]",
		"scale", // 8
		"inverse scale", // 9
		"object to world (row 0)", // 10
		"object to world (row 1)",
		"object to world (row 2)",
		"object to world (row 3)",
		"world to camera (row 0)",
		"world to camera (row 1)",
		"world to camera (row 2)",
		"world to camera (row 3)",
		"camera to view (row 0)",
		"camera to view (row 1)",
		"camera to view (row 2)",
		"camera to view (row 3)",
		"world to object (row 0)", // 22
		"world to object (row 1)",
		"world to object (row 2)",
		"world to object (row 3)",
		"camera to world (row 0)",
		"camera to world (row 1)",
		"camera to world (row 2)",
		"camera to world (row 3)",
		"view to camera (row 0)",
		"view to camera (row 1)",
		"view to camera (row 2)",
		"view to camera (row 3)",
		"not implemented 34",
		"not implemented 35",
		"unused" // 36
	};
	const char *spaces[] = {
		"object",
		"world",
		"camera", // maybe call this view space
		"view"    // and this clip space
	};
	const char *transformMode[] = {
		"pos (mat4x4)",
		"dir (mat3x3)",
		"[not implemented]"
	};
	for (uint32_t i=0; i<8; i++) {
		auto& param = extra->params[i];
		ImGui::Text("param %d mode %2d %s",
			i, param.mode, modes[param.mode]);
		if (param.matrixP != 4 && param.matrixQ != 4)
			ImGui::Text("  transform %s %s -> %s",
				transformMode[param.multiplyMode],
				spaces[param.matrixP],
				spaces[param.matrixQ]);
	}
}

void buildUI(UIActions& uiact, LensFlareAndCoronaExtraData *extra) {
	if (extra->material)
		if (ImGui::SmallButton("show override material"))
			uiact.select(extra->material);
	ImGui::Text("matrix mode %d",
		extra->matrixMode);
	for (uint32_t i=0; i<8; i++) {
		ImGui::Text("param %d mode %d",
			i, extra->mode[i]);
	}

	ImGui::Text("texture 0 %p", extra->texture[0]);
	ImGui::Text("texture 1 %p", extra->texture[1]);
	ImGui::Text("texture 2 %p", extra->texture[2]);
	ImGui::Text("texture 3 %p", extra->texture[3]);
	ImGui::Text("material %p", extra->material);
}

void buildUI(UIActions& uiact, dtp::Intro *intro) {
	auto *objectSection = cdc::g_resolveSections[11];
	if (cdc::Object *object = (cdc::Object*)objectSection->getWrapped(objectSection->getDomainId(intro->objectListIndex))) {
		uint32_t objFamily = buildUI(uiact, object);

		if (objFamily == 0x50) {
			auto *extraData = (DeferredRenderingExtraData*) intro->extraData1;
			buildUI(uiact, extraData);

		} else if (objFamily == 0x5b) {
			auto *extraData = (LensFlareAndCoronaExtraData*) intro->extraData1;
			buildUI(uiact, extraData);
		}
	}
}

void buildUI(UIActions& uiact, Instance *instance) {
	if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Position         %f %f %f",
			instance->position.x,
			instance->position.y,
			instance->position.z);
		ImGui::Text("SceneEntity      %p", instance->sceneEntity);
		ImGui::Text("InstanceDrawable %p", instance->instanceDrawable);
	}
	if (ImGui::CollapsingHeader("Intro", ImGuiTreeNodeFlags_DefaultOpen)) {
		buildUI(uiact, instance->intro);
	}
	if (instance->intro == nullptr && ImGui::CollapsingHeader("Object", ImGuiTreeNodeFlags_DefaultOpen)) {
		buildUI(uiact, instance->object);
	}
	if (ImGui::CollapsingHeader("SoundComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
		dtp::ObjectBaseData *dtpData = instance->object->dtpData;
		const char *names[] = {
			"Sound 0",
			"Sound 1"
		};
		for (uint32_t i=0; i<dtpData->numSounds; i++)
			if (ImGui::SmallButton(i < 2 ? names[i] : "Sound")) {
				cdc::SoundHandle sh = cdc::SOUND_StartPaused(dtpData->sounds[i].m_plex, /*delay=*/ 0.0f);
				cdc::SoundTypes::Controls3d& c3d = sh->controls3d;
				c3d.playbackType = 0x101; // 3D sound
				c3d.position[0] = instance->position.x;
				c3d.position[1] = instance->position.y;
				c3d.position[2] = instance->position.z;
			}
	}
	// if (ImGui::CollapsingHeader("TransformComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
	// 	// TODO
	// }
	// if (ImGui::CollapsingHeader("ObjectComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
	// 	// TODO
	// }
	if (ImGui::CollapsingHeader("MeshComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
		cdc::MeshComponent& mc = instance->GetMeshComponent();
		dtp::Model *currentModel = mc.GetModel();
		uint32_t numModels = instance->GetNumModels();
		dtp::Model **models = instance->GetModels();

		const char *names[] = {
			"Model 0",
			"Model 1"
		};

		if (ImGui::BeginListBox("##models")) {
			for (uint32_t i=0; i<numModels; i++) {
				const bool is_selected = models[i] == currentModel;
				if (ImGui::Selectable(i < 2 ? names[i] : "Model", is_selected))
					mc.SetModel(i);
			}
			ImGui::EndListBox();
		}
	}
}
