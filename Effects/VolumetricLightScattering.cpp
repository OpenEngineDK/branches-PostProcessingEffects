#include "VolumetricLightScattering.h"

VolumetricLightScattering::VolumetricLightScattering(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,false) {
    screenlightpos.push_back(0.5);
    screenlightpos.push_back(0.5);
}

void VolumetricLightScattering::Setup() {
    pass1 = AddPass("Effects/VolumetricLightScattering.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->BindFloat("screenLightPos", screenlightpos);
    pass1->EnableColorBufferOutput();

}

void VolumetricLightScattering::PerFrame(const float deltaTime) {
    pass1->BindFloat("screenLightPos", screenlightpos);
}

void VolumetricLightScattering::SetLightPos(vector<float> pos) {
    screenlightpos = pos;
}
