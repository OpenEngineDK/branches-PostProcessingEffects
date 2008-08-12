#include "SimpleExample.h"

void SimpleExample::Setup() {
    IPostProcessingPass* pass1 = AddPass("Effects/SimpleExample.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();
}

void SimpleExample::PerFrame(const float deltaTime) {
}
