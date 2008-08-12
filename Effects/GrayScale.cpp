#include "GrayScale.h"

GrayScale::GrayScale(Viewport* viewport) : PostProcessingEffect(viewport,false) {
}

void GrayScale::Setup() {
    pass1 = AddPass("Effects/grayscale.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();
}


void GrayScale::PerFrame(const float deltaTime) {

}


