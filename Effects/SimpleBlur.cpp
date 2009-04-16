#include "SimpleBlur.h"

SimpleBlur::SimpleBlur(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,false) {
    offset.push_back(0.005);
}

void SimpleBlur::Setup() {
    pass1 = AddPass("Effects/SimpleBlur.frag");
    pass1->BindFloat("offset", offset);
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();
}

void SimpleBlur::PerFrame(const float deltaTime) {
    pass1->BindFloat("offset", offset);
}

