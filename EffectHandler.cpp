// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "EffectHandler.h"

#include <Core/IGameEngine.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Utils {

using OpenEngine::Core::IGameEngine;
using OpenEngine::Math::Vector;
using OpenEngine::Scene::TransformationNode;

EffectHandler::EffectHandler(vector<IPostProcessingEffect*> fullscreeneffects, ShowImage* showImage, SunModule* sunModule) {
    this->fullscreeneffects = fullscreeneffects;
    this->showImage = showImage;
    this->sunModule = sunModule;
}

EffectHandler::~EffectHandler() {
}

void EffectHandler::Handle(KeyboardEventArg arg) {
	if (arg.type != KeyboardEventArg::PRESS) return;
	
	printf("Switching effect on input %i if possible\n", arg.sym);

    switch (arg.sym) {
	case KEY_1: fullscreeneffects[ 0]->Enable(!(fullscreeneffects[ 0]->IsEnabled())); break;
	case KEY_2: fullscreeneffects[ 1]->Enable(!(fullscreeneffects[ 1]->IsEnabled())); break;
	case KEY_3: fullscreeneffects[ 2]->Enable(!(fullscreeneffects[ 2]->IsEnabled())); break;
	case KEY_4: fullscreeneffects[ 3]->Enable(!(fullscreeneffects[ 3]->IsEnabled())); break;
	case KEY_5: fullscreeneffects[ 4]->Enable(!(fullscreeneffects[ 4]->IsEnabled())); break;
	case KEY_6: fullscreeneffects[ 5]->Enable(!(fullscreeneffects[ 5]->IsEnabled())); break;
	case KEY_7: fullscreeneffects[ 6]->Enable(!(fullscreeneffects[ 6]->IsEnabled())); break;
	case KEY_8: fullscreeneffects[ 7]->Enable(!(fullscreeneffects[ 7]->IsEnabled())); break;
	case KEY_9: fullscreeneffects[ 8]->Enable(!(fullscreeneffects[ 8]->IsEnabled())); break;
	case KEY_0: fullscreeneffects[ 9]->Enable(!(fullscreeneffects[ 9]->IsEnabled())); break;
	case KEY_q: fullscreeneffects[10]->Enable(!(fullscreeneffects[10]->IsEnabled())); break;
	case KEY_e: fullscreeneffects[11]->Enable(!(fullscreeneffects[11]->IsEnabled())); break;
	case KEY_t: fullscreeneffects[12]->Enable(!(fullscreeneffects[12]->IsEnabled())); break;
	case KEY_y: fullscreeneffects[13]->Enable(!(fullscreeneffects[13]->IsEnabled())); break;
	case KEY_u: fullscreeneffects[14]->Enable(!(fullscreeneffects[14]->IsEnabled())); break;
	case KEY_SPACE:
	    for (int i=0; i<15; i++)
	        fullscreeneffects[i]->Enable(false);
	    break;
        case KEY_f: sunModule->SetFollowSun(!sunModule->GetFollowSun()); break;

	case KEY_h: showImage->FadeToggle(); break;
	default:    break;
    }

}


} // NS Utils
} // NS OpenEngine
