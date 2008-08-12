// looks best with a slight blur afterwards.

#ifndef __WOBBLE_H__
#define __WOBBLE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Wobble : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

    float offsetx;
    float offsety;

  public:

    Wobble(Viewport* viewport) : PostProcessingEffect(viewport,false) {}
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
