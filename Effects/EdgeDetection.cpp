#include "EdgeDetection.h"

EdgeDetection::EdgeDetection(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,false) {
}

void EdgeDetection::Setup() {
    pass1 = AddPass("Effects/EdgeDetection.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();

    SetColorBufferWrap(TEX_CLAMP_TO_EDGE, TEX_CLAMP_TO_EDGE);
}

void EdgeDetection::PerFrame(const float deltaTime) {
}

