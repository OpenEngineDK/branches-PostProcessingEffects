// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _EFFECT_HANDLER_H_
#define _EFFECT_HANDLER_H_

#include <Devices/IKeyboard.h>
#include <Scene/TransformationNode.h>
#include <vector>

#include <PostProcessing/IPostProcessingEffect.h>
#include "Effects/ShowImage.h"
#include "SunModule.h"

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Devices;
using namespace OpenEngine::PostProcessing;

/**
 * 
 */
class EffectHandler : public IListener<KeyboardEventArg> {
  private:
    vector<IPostProcessingEffect*> fullscreeneffects;
    vector<std::string> names;
    ShowImage* showImage;
    SunModule* sunModule;
    void ToggleEffect(unsigned int index);
  public:
    EffectHandler(vector<IPostProcessingEffect*> fullscreeneffects, ShowImage* showImage, SunModule* sunModule);
    ~EffectHandler();
    void Handle(KeyboardEventArg arg);
    void SetNameList(vector<std::string> list);
};

} // NS Utils
} // NS OpenEngine

#endif // _MOVE_HANDLER_H_
