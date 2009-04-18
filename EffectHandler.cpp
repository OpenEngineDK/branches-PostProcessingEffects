// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "EffectHandler.h"

//#include <Core/IGameEngine.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Utils {

    //using OpenEngine::Core::IGameEngine;
using OpenEngine::Math::Vector;
using OpenEngine::Scene::TransformationNode;

EffectHandler::EffectHandler(vector<IPostProcessingEffect*> fullscreeneffects,
                             ShowImage* showImage, SunModule* sunModule) {
    this->fullscreeneffects = fullscreeneffects;
    this->showImage = showImage;
    this->sunModule = sunModule;
}

EffectHandler::~EffectHandler() {}

void EffectHandler::SetNameList(vector<std::string> list) {
    names = list;
}

void EffectHandler::ToggleEffect(unsigned int index) {
    IPostProcessingEffect* effect = fullscreeneffects[index];
    std::string name = "unknown";
    if (names.size() > index)
        name = names[index];

    effect->Enable(!(effect->IsEnabled()));
    logger.info << "effect: "  << name << " = "
                << effect->IsEnabled() << logger.end;
}

void EffectHandler::Handle(KeyboardEventArg arg) {
	if (arg.type != EVENT_PRESS) return;
	
	//printf("Switching effect on input %i if possible\n", arg.sym);

    switch (arg.sym) {
	case KEY_1: ToggleEffect( 0); break;
	case KEY_2: ToggleEffect( 1); break;
	case KEY_3: ToggleEffect( 2); break;
	case KEY_4: ToggleEffect( 3); break;
	case KEY_5: ToggleEffect( 4); break;
	case KEY_6: ToggleEffect( 5); break;
	case KEY_7: ToggleEffect( 6); break;
	case KEY_8: ToggleEffect( 7); break;
	case KEY_9: ToggleEffect( 8); break;
	case KEY_0: ToggleEffect( 9); break;
	case KEY_e: ToggleEffect(10); break;
	case KEY_r: ToggleEffect(11); break;
	case KEY_t: ToggleEffect(12); break;
	case KEY_y: ToggleEffect(13); break;
    case KEY_u: ToggleEffect(14); break;
    case KEY_i: ToggleEffect(15); break;
    case KEY_o: ToggleEffect(16); break;
	case KEY_SPACE:
	    for (int i=0; i<15; i++)
	        fullscreeneffects[i]->Enable(false);
        logger.info << "disabling all effects" << logger.end;
	    break;
    case KEY_f:
        if (sunModule != NULL) {
            sunModule->SetFollowSun(!sunModule->GetFollowSun());
            logger.info << "sunModule is:" 
                        << sunModule->GetFollowSun() << logger.end;
        } else
            logger.info << "sunModule is null" << logger.end;
        break;
	case KEY_g:
        if( showImage != NULL) {
            showImage->FadeToggle();
            logger.info << "showImage is FadeToggle()" << logger.end;
        } else
            logger.info << "showImage is null" << logger.end;
        break;
	default:
        break;
    }
}


} // NS Utils
} // NS OpenEngine
