#include "SimpleMotionBlur.h"

SimpleMotionBlur::SimpleMotionBlur(Viewport* viewport) : PostProcessingEffect(viewport,false) {
}

void SimpleMotionBlur::Setup() {
    for (int i=0; i<numSavedFrames; i++)
	colorBufferFrames[i] = ITexture2DPtr(new Texture2D(0, 0, TEX_RGBA, TEX_REPEAT, TEX_REPEAT, TEX_LINEAR, TEX_LINEAR));

    pass1 = AddPass("Effects/SimpleMotionBlur.frag");
    pass1->BindColorBuffer("newColBuf");
    pass1->EnableColorBufferOutput();
    pass1->AttachUserBuffer(1);
}

void SimpleMotionBlur::PerFrame(const float deltaTime) {

    // roter colorBufferFrames-array en tak til venstre
    ITexture2DPtr tmp = colorBufferFrames[0];
    for (int i=0; i<numSavedFrames - 1; i++)
	colorBufferFrames[i] = colorBufferFrames[i+1];
    colorBufferFrames[numSavedFrames-1] = tmp;

    // put a copy of the colorbuffer-texture from last frame into the texture at the rightmost position in the array
    GetFinalColorBuffer(colorBufferFrames[numSavedFrames-1]);  // <- ser faktist federe ud hvis man bruger den her!
    //pass1->getOutputUserBufferTexture(1, colorBufferFrames[numSavedFrames-1]);

    // bind them all to the fp of pass1
    if (numSavedFrames != 3) printf("argh! change code here!\n");
    pass1->BindTexture("oldColBuf0", colorBufferFrames[0]);
    pass1->BindTexture("oldColBuf1", colorBufferFrames[1]);
    pass1->BindTexture("oldColBuf2", colorBufferFrames[2]);
}

