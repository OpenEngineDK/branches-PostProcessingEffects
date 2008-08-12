#ifndef __DOF_H__
#define __DOF_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class DoF : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1; // xblur
    IPostProcessingPass* pass2; // yblur
    IPostProcessingPass* pass3; // simple DoF

    vector<float> znear;
    vector<float> zfar;
    vector<float> zsharp;

    static const int NUM_SAMPLES = 20;
    float blurweights[NUM_SAMPLES];

    float g(float x);
    void  calcBlurWeightArray();

  public:

    DoF(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
