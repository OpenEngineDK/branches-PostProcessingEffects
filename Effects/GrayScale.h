#ifndef __GRAYSCALE_H__
#define __GRAYSCALE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class GrayScale : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

  public:

    GrayScale(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif


