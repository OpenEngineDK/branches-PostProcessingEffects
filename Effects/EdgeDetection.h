#ifndef __EDGEDETECTION_H__
#define __EDGEDETECTION_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class EdgeDetection : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

  public:

    EdgeDetection(Viewport* viewport);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
