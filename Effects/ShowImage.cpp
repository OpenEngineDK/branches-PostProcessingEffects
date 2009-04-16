#include "ShowImage.h"

#include <Resources/TGAResource.h>
#include <Resources/ResourceManager.h>
#include <Resources/ITextureResource.h>
#include <Renderers/OpenGL/TextureLoader.h> // for forcing loading of textures

using namespace OpenEngine::Resources;
using namespace OpenEngine;

ShowImage::ShowImage(Viewport* viewport, IEngine& engine, ITextureResourcePtr picture) : PostProcessingEffect(viewport,engine,false) {
    this->picture = picture;
    alpha.push_back(1);
    this->cnt = 0;
    this->fadeout = false;
}

void ShowImage::Setup() {
    // force loading of texture
    Renderers::OpenGL::TextureLoader::LoadTextureResource(picture);

    pass1 = AddPass("Effects/ShowImage.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->BindTexture("picture", picture);
    pass1->BindFloat("alpha", alpha);
    pass1->EnableColorBufferOutput();
}


void ShowImage::PerFrame(const float deltaTime) {

    //alpha[0] = (sin(cnt)+1)/2.0;
    //cnt += 0.0001*deltaTime;
    //pass1->BindFloat("alpha", alpha);

    if (fadeout) {
	alpha[0] -= 0.003*deltaTime;
	if (alpha[0] < 0) alpha[0] = 0;
    } else {
	alpha[0] += 0.003*deltaTime;
	if (alpha[0] > 1) alpha[0] = 1;
    }

    pass1->BindFloat("alpha", alpha);

}

void ShowImage::FadeOut() {
    fadeout = true;
}

void ShowImage::FadeIn() {
    fadeout = false;
}

void ShowImage::FadeToggle() {
    fadeout = !fadeout;
}
