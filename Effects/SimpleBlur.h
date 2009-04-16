#ifndef __SIMPLEBLUR_H__
#define __SIMPLEBLUR_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class SimpleBlur : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

    vector<float> offset;

  public:

    SimpleBlur(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
