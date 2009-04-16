#ifndef __SHADOWS_H__
#define __SHADOWS_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Shadows : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

    // light pos i screenspace (som global coords, men (0,0) er i øverst venstre hjørne (1,1) nederst højre)
    vector<float> lightpos;

  public:

    Shadows(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);

    vector<float> GetLightPos();
    void SetLightPos(vector<float> lightpos);

};

#endif
