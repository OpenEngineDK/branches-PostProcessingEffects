#ifndef __MOTIONBLUR_H__
#define __MOTIONBLUR_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <Resources/OpenGL/Texture2D.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class MotionBlur : public PostProcessingEffect {
  private:

    IPostProcessingPass*      pass1;
    ITexture2DPtr oldcolorbuf;

  public:

    MotionBlur(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
