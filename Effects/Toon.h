#ifndef __TOON_H__
#define __TOON_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Toon : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

  public:

    Toon(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
