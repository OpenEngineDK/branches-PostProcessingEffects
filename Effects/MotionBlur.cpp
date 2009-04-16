#include "MotionBlur.h"

MotionBlur::MotionBlur(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,true) {
}

void MotionBlur::Setup() {
    oldcolorbuf = ITexture2DPtr(new Texture2D(0,0,TEX_RGBA,TEX_REPEAT,TEX_REPEAT,TEX_LINEAR,TEX_LINEAR));

    pass1 = AddPass("Effects/MotionBlur.frag");
    pass1->BindColorBuffer("newcolorbuf");
    pass1->BindTexture("oldcolorbuf",oldcolorbuf); // just to init it to something
    pass1->EnableColorBufferOutput();
}

void MotionBlur::PerFrame(const float deltaTime) {
    GetFinalColorBuffer(oldcolorbuf);
    pass1->BindTexture("oldcolorbuf",oldcolorbuf);
}

