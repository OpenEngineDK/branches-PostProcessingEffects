#ifndef __GLOW_H__
#define __GLOW_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Glow : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1; // blur x
    IPostProcessingPass* pass2; // blur y
    IPostProcessingPass* pass3; // glow

    static const int NUM_SAMPLES = 20;
    float blurweights[NUM_SAMPLES];

    float g(float x);
    void  calcBlurWeightArray();

  public:

    Glow(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif

