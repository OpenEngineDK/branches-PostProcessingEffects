#include "TwoPassBlur.h"

TwoPassBlur::TwoPassBlur(Viewport* viewport) : PostProcessingEffect(viewport,false) {
}

void TwoPassBlur::Setup() {
    pass1 = AddPass("Effects/TwoPassBlur_Pass1.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->AttachUserBuffer(0);

    pass2 = AddPass("Effects/TwoPassBlur_Pass2.frag");
    pass2->BindUserBuffer("colorbuf", pass1, 0);
    pass2->EnableColorBufferOutput();
}

void TwoPassBlur::PerFrame(const float deltaTime) {
}

