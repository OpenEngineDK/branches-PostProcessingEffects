// Game Factory for a test project.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

// header define to avoid including definitions several times
#ifndef _TEST_GAME_FACTORY_H_
#define _TEST_GAME_FACTORY_H_

// Game engine interface
#include <Core/IGameFactory.h>
#include <Display/Viewport.h>
#include <Scene/ISceneNode.h>

// effects
#include "Effects/Wobble.h"
#include "Effects/Shadows.h"
#include "Effects/SimpleBlur.h"
#include "Effects/TwoPassBlur.h"
#include "Effects/GaussianBlur.h"
#include "Effects/Glow.h"
#include "Effects/SimpleMotionBlur.h"
#include "Effects/MotionBlur.h"
#include "Effects/EdgeDetection.h"
#include "Effects/Toon.h"
#include "Effects/SimpleDoF.h"
#include "Effects/VolumetricLightScattering.h"
#include "Effects/GrayScale.h"
#include "Effects/Pixelate.h"
#include "Effects/Saturate.h"
#include "Effects/ShowImage.h"
#include "Effects/DoF.h"
#include "Effects/SimpleExample.h"


// Namespaces
using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Renderers;

/**
 * Game factory definition.
 *
 * The factory is implemented in GameFactory.cpp
 * Documentation on game factories can be found in Core/IGameFactory.h
 *
 * @see IGameFactory
 */
class GameFactory : public IGameFactory {

private:
    IFrame*      frame;         // member variable for the engine frame
    IRenderer*   renderer;      // member variable for the engine renderer

    Viewport* viewport;

    Wobble* wobble;
    Glow* glow;
    SimpleBlur* simpleBlur;
    TwoPassBlur* twoPassBlur;
    GaussianBlur* gaussianBlur;
    SimpleMotionBlur* simpleMotionBlur;
    MotionBlur* motionBlur;
    SimpleDoF* simpleDoF;
    EdgeDetection* edgeDetection;
    Toon* toon;
    GrayScale* grayscale;
    Saturate* saturate;
    Pixelate* pixelate;
    VolumetricLightScattering* volumetricLightScattering;
    Shadows* shadows;
    ShowImage* showImage;

    vector<IPostProcessingEffect*> fullscreeneffects;

public:
    GameFactory();
    bool         SetupEngine(IGameEngine& engine);
    IFrame*      GetFrame();
    IRenderer*   GetRenderer();

    void Test(ISceneNode* node, int ident);

};

#endif // _TEST_GAME_FACTORY_H_
