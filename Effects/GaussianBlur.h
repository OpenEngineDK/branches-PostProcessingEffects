#ifndef __GAUSSIANBLUR_H__
#define __GAUSSIANBLUR_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class GaussianBlur : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;
    IPostProcessingPass* pass2;

    static const int NUM_SAMPLES = 20;
    float blurweights[NUM_SAMPLES];

    float g(float x);
    void  calcBlurWeightArray();

  public:

    GaussianBlur(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif

