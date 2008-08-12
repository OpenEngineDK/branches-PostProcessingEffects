#ifndef __SATURATE_H__
#define __SATURATE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Saturate : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

  public:

    Saturate(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
