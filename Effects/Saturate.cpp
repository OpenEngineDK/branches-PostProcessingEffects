#include "Saturate.h"

Saturate::Saturate(Viewport* viewport) : PostProcessingEffect(viewport,false) {
}

void Saturate::Setup() {
    pass1 = AddPass("Effects/saturate.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();
}


void Saturate::PerFrame(const float deltaTime) {

}
