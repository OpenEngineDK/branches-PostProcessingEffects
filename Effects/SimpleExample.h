#ifndef __SIMPLEEXAMPLE_H__
#define __SIMPLEEXAMPLE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>

using namespace OpenEngine::PostProcessing;

class SimpleExample : public PostProcessingEffect {
  public:
    SimpleExample(Viewport* viewport) : PostProcessingEffect(viewport) {}
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
