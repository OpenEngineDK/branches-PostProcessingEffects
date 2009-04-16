#ifndef __SIMPLEMOTIONBLUR_H__
#define __SIMPLEMOTIONBLUR_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Core/IEngine.h>

#include <Resources/OpenGL/Texture2D.h>

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;

class SimpleMotionBlur : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;

    static const unsigned int numSavedFrames = 3;
    ITexture2DPtr colorBufferFrames[numSavedFrames];

  public:

    SimpleMotionBlur(Viewport* viewport, IEngine& engine);
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
