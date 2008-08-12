// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _SUN_MODULE_H_
#define _SUN_MODULE_H_

#include <Core/IModule.h>
#include <Display/Camera.h>
#include <Devices/IKeyboard.h>
#include <Devices/IMouse.h>
#include <Scene/TransformationNode.h>
#include <vector>

#include "Effects/VolumetricLightScattering.h"

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Devices;
using namespace OpenEngine::PostProcessing;

/**
 * Camera movement handler
 */
class SunModule : public IModule {
  private:
    VolumetricLightScattering* volumetricLightScattering;
    TransformationNode* sunTransNode;
    Camera* camera;
    bool followSun;
  public:
    SunModule(VolumetricLightScattering* volumetricLightScattering, TransformationNode* sunTransNode, Camera* camera);
    ~SunModule();
    void Initialize();
    void Deinitialize();
    bool IsTypeOf(const std::type_info& inf);
    void Process(const float dt, const float percent);
    void SetFollowSun(bool followSun);
    bool GetFollowSun();
};

} // NS Utils
} // NS OpenEngine

#endif // _MOVE_HANDLER_H_
