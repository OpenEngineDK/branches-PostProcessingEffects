#ifndef __SHOWIMAGE_H__
#define __SHOWIMAGE_H__

#include <PostProcessing/OpenGL/PostProcessingEffect.h>
#include <PostProcessing/IPostProcessingPass.h>
#include <Display/Viewport.h>
#include <Resources/ITextureResource.h>
#include <Renderers/OpenGL/TextureLoader.h> // for forcing loading of textures

#include <vector>
#include <stdio.h>

using namespace OpenEngine::PostProcessing;
using namespace OpenEngine::Resources;

class ShowImage : public PostProcessingEffect {
  private:

    IPostProcessingPass* pass1;
    ITextureResourcePtr picture;

    vector<float> alpha;
    float cnt;

    bool fadeout;

  public:

    ShowImage(Viewport* viewport, ITextureResourcePtr picture);
    void Setup();
    void PerFrame(const float deltaTime);

    void FadeOut();
    void FadeIn();
    void FadeToggle();
};

#endif


