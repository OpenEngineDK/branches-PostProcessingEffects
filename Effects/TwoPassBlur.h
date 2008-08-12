#ifndef __TWOPASSBLUR_H__
#define __TWOPASSBLUR_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class TwoPassBlur : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;
    IPostProcessingPass* pass2;

  public:

    TwoPassBlur(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
