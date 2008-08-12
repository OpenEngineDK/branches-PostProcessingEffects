#include "Wobble.h"

void Wobble::Setup() {
    this->offsetx = 0;
    this->offsety = 0;

    pass1 = AddPass("Effects/Wobble.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->BindDepthBuffer("depthbuf");
    pass1->EnableColorBufferOutput();
    pass1->EnableDepthBufferOutput();

    vector<float> initOffset;
    initOffset.push_back(0);
    initOffset.push_back(0);
    pass1->BindFloat("offset", initOffset);
}


void Wobble::PerFrame(const float deltaTime) {

/*
ITexture2DPtr tex = GetFinalColorBufferRef();
printf("before %d\n",tex->GetWrapS());

    SetColorBufferWrap(TEX_REPEAT, TEX_REPEAT);
    SetDepthBufferWrap(TEX_REPEAT, TEX_REPEAT);

printf("after %d\n",tex->GetWrapS());
*/

    // calc fragmentprogram argument values that needs to change each frame
    offsetx += 0.0012 * deltaTime;
    offsety += 0.0012 * deltaTime;

    // set fragmentprogram argument values that needs to change each frame
    vector<float> offsetvalues2;
    offsetvalues2.push_back(offsetx);
    offsetvalues2.push_back(offsety);

    pass1->BindFloat("offset", offsetvalues2);
}
