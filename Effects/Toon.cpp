#include "Toon.h"

Toon::Toon(Viewport* viewport) : PostProcessingEffect(viewport,false) {
}

void Toon::Setup() {
    pass1 = AddPass("Effects/Toon.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();
}

void Toon::PerFrame(const float deltaTime) {
}

