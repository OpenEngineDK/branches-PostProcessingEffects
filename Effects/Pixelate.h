#ifndef __PIXELATE_H__
#define __PIXELATE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class Pixelate : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;
    vector<float> xsize; // zoom-size in pixels
    vector<float> ysize; // zoom-size in pixels

    Viewport* viewport;

    float xcnt;
    float ycnt;

  public:

    Pixelate(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
