// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "SunModule.h"

//#include <Core/IGameEngine.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Utils {

    //using OpenEngine::Core::IGameEngine;
using OpenEngine::Math::Vector;
using OpenEngine::Scene::TransformationNode;

SunModule::SunModule(VolumetricLightScattering* volumetricLightScattering, TransformationNode* sunTransNode, Camera* camera) {
    this->volumetricLightScattering = volumetricLightScattering;
    this->sunTransNode = sunTransNode;
    this->camera = camera;
    this->followSun = true;
}

SunModule::~SunModule() {
}

void SunModule::SetFollowSun(bool followSun) {
    this->followSun = followSun;
}

bool SunModule::GetFollowSun() {
    return followSun;
}

void SunModule::Handle(ProcessEventArg arg) {
    // calc new sun object position
    static float cnt = 0;

    float x = cos(cnt) * 100;
    float y = (sin(cnt)+0.5) * 30;

    cnt += arg.approx;

    sunTransNode->SetPosition(Vector<3,float>(0, y, x));

    // convert position to screenspace
    Vector<3,float> accPos;
    Quaternion<float> accRot;
    sunTransNode->GetAccumulatedTransformations(&accPos, &accRot);

    Vector<3,float> sunLocPos(286.866, 1.278+50, 44.593-45);
    sunLocPos = accRot.RotateVector(sunLocPos);
    accPos += sunLocPos;


    Matrix<4,4,float> vm = camera->GetViewMatrix(); // vm = viewmatrix

    float px = accPos[0];
    float py = accPos[1];
    float pz = accPos[2];

    Vector<3, float> globAccPos =
        Vector<3,float> (vm(0,0)*px + vm(1,0)*py + vm(2,0)*pz + vm(3,0),
                         vm(0,1)*px + vm(1,1)*py + vm(2,1)*pz + vm(3,1),
                         vm(0,2)*px + vm(1,2)*py + vm(2,2)*pz + vm(3,2));

    globAccPos[0] /= globAccPos[2];
    globAccPos[1] /= globAccPos[2];

    globAccPos[0] *= -1;
    globAccPos[1] *= -1;


    float sx;
    float sy;
    if (followSun) {
        sx = globAccPos[0] + 0.5;
        sy = globAccPos[1] + 0.5;
    } else {
        sx = 0.5;
        sy = 0.5;
    }


    // set new screenspace position in the effect
    vector<float> screenlightpos;
    screenlightpos.push_back(sx);
    screenlightpos.push_back(sy);
    volumetricLightScattering->SetLightPos(screenlightpos);
}

} // NS Utils
} // NS OpenEngine

