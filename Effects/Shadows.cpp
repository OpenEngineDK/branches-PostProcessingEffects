#include "Shadows.h"

Shadows::Shadows(Viewport* viewport,IEngine& engine)
    : PostProcessingEffect(viewport,engine,false) {
    lightpos.push_back(0.5);
    lightpos.push_back(0.5);
    lightpos.push_back(-2);
}

void Shadows::Setup() {
    pass1 = AddPass("Effects/shadows.frag");
    pass1->BindFloat("screenLightPos", lightpos);
    pass1->BindColorBuffer("colorbuf");
    pass1->BindDepthBuffer("depthbuf");
    pass1->EnableColorBufferOutput();

    SetColorBufferWrap(TEX_CLAMP_TO_EDGE, TEX_CLAMP_TO_EDGE);
    SetDepthBufferFilter(TEX_NEAREST);
}


void Shadows::PerFrame(const float deltaTime) {
    // set light uniform each frame, so you can move the light
    pass1->BindFloat("screenLightPos", lightpos);
}


vector<float> Shadows::GetLightPos() {
    return lightpos;
}

void Shadows::SetLightPos(vector<float> lightpos) {
    this->lightpos = lightpos;
}
