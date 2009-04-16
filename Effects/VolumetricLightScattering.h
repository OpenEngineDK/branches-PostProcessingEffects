#ifndef __VOLUMETRICLIGHTSCATTERING_H__
#define __VOLUMETRICLIGHTSCATTERING_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class VolumetricLightScattering : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;
    vector<float> screenlightpos; // <- in screen coordinates

  public:

    VolumetricLightScattering(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);

    void SetLightPos(vector<float> pos);
};

#endif
