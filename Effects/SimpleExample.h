#ifndef __SIMPLEEXAMPLE_H__
#define __SIMPLEEXAMPLE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <Core/IEngine.h>

using namespace OpenEngine::PostProcessing;

class SimpleExample : public PostProcessingEffect {
  public:
 SimpleExample(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine) {}
    void Setup();
    void PerFrame(const float deltaTime);
};

#endif
