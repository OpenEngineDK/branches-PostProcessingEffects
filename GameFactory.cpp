// Game Factory for the OERacer project.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

// Class header
#include "GameFactory.h"

// Bjarke
#include <Renderers/OpenGL/PostProcessingRenderingView.h> //#include "TestRenderingView.h" 	/***************/
#include <Scene/BlendNode.h>
#include <Scene/MergeNode.h>
#include <Scene/MergeBlendNode.h>


// OpenEngine library
#include <Display/FollowCamera.h>
#include <Display/Frustum.h>
#include <Display/InterpolatedViewingVolume.h>
#include <Display/ViewingVolume.h>
#include <Display/SDLFrame.h>
#include <Devices/SDLInput.h>
#include <Logging/Logger.h>
#include <Renderers/IRenderNode.h>
#include <Renderers/RenderStateNode.h>
#include <Renderers/OpenGL/Renderer.h>
#include <Renderers/OpenGL/RenderingView.h>
#include <Resources/IModelResource.h>
#include <Resources/File.h>
#include <Resources/GLSLResource.h>
#include <Resources/TGAResource.h>
#include <Resources/OBJResource.h>
#include <Resources/ResourceManager.h>
#include <Scene/SceneNode.h>
#include <Scene/GeometryNode.h>
#include <Scene/TransformationNode.h>
#include <Utils/Statistics.h>

// from AccelerationStructures extension
#include <Scene/QuadTreeBuilder.h>
#include <Scene/QuadBSPBuilder.h>
#include <Scene/BSPTreeBuilder.h>
#include <Renderers/AcceleratedRenderingView.h>

// from FixedTimeStepPhysics
#include <Physics/FixedTimeStepPhysics.h>
#include <Physics/RigidBox.h>

// Project files
#include "KeyboardHandler.h"
#include "RenderStateHandler.h"
#include "MoveHandler.h"
#include "QuitHandler.h"
#include "EffectHandler.h"
#include "SunModule.h"

// Additional namespaces (others are in the header).
using namespace OpenEngine::Devices;
using namespace OpenEngine::Renderers::OpenGL;
using namespace OpenEngine::Renderers;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Utils;
using namespace OpenEngine::Physics;

// composite rendering view. Uses RenderingView for drawing and
// AcceleratedRenderingView for clipping.
class MyRenderingView :
    public RenderingView,
    public AcceleratedRenderingView {
public:
    MyRenderingView(Viewport& viewport) :
        IRenderingView(viewport),
        RenderingView(viewport),
        AcceleratedRenderingView(viewport) {

    }
};

/**
 * Factory constructor.
 *
 * Initializes the different components so they are accessible when
 * the setup method is executed.
 */
GameFactory::GameFactory() {

    // Create a frame and viewport.
    this->frame = new SDLFrame(800, 600, 32);

    // Main viewport
    viewport = new Viewport(*frame);

    // ** load en eller anden texture (via resource manageren) **
    ResourceManager::SetPath("projects/VolumetricLightTest/data/"); // <- set path hvor textures (og alle andre resources) loades relativt fra
    ResourceManager::AddTexturePlugin(new TGAPlugin()); // <- nu kan den lave textures ud fra TGA-filer
    ITextureResourcePtr texture = ResourceManager::CreateTexture("VolumetricTestHelp.tga"); // <- load og return texture

    this->wobble                    = new Wobble(viewport);
    this->glow                      = new Glow(viewport);
    this->simpleBlur                = new SimpleBlur(viewport);
    this->twoPassBlur               = new TwoPassBlur(viewport);
    this->gaussianBlur              = new GaussianBlur(viewport);
    this->simpleMotionBlur          = new SimpleMotionBlur(viewport);
    this->motionBlur                = new MotionBlur(viewport);
    this->simpleDoF                 = new SimpleDoF(viewport);
    this->edgeDetection             = new EdgeDetection(viewport);
    this->toon                      = new Toon(viewport);
    this->grayscale                 = new GrayScale(viewport);
    this->saturate                  = new Saturate(viewport);
    this->pixelate                  = new Pixelate(viewport);
    this->volumetricLightScattering = new VolumetricLightScattering(viewport);
    this->shadows                   = new Shadows(viewport);
    this->showImage                 = new ShowImage(viewport, texture);

    // muligvis skal rækkefølgen laves om...
    wobble->Add(edgeDetection);
    wobble->Add(toon);
    wobble->Add(glow);
    wobble->Add(simpleBlur);
    wobble->Add(twoPassBlur);
    wobble->Add(gaussianBlur);
    wobble->Add(simpleMotionBlur);
    wobble->Add(motionBlur);
    wobble->Add(simpleDoF);
    wobble->Add(grayscale);
    wobble->Add(saturate);
    wobble->Add(volumetricLightScattering);
    wobble->Add(shadows);
    wobble->Add(pixelate);
    wobble->Add(showImage);

    wobble->Enable(false);
    glow->Enable(false);
    simpleBlur->Enable(false);
    twoPassBlur->Enable(false);
    gaussianBlur->Enable(false);
    simpleMotionBlur->Enable(false);
    motionBlur->Enable(false);
    simpleDoF->Enable(false);
    edgeDetection->Enable(false);
    toon->Enable(false);
    grayscale->Enable(false);
    saturate->Enable(false);
    pixelate->Enable(false);
    volumetricLightScattering->Enable(false);
    shadows->Enable(false);

    // add to effects
    this->fullscreeneffects.push_back(wobble);
    this->fullscreeneffects.push_back(glow);
    this->fullscreeneffects.push_back(simpleBlur);
    this->fullscreeneffects.push_back(twoPassBlur);
    this->fullscreeneffects.push_back(gaussianBlur);
    this->fullscreeneffects.push_back(simpleMotionBlur);
    this->fullscreeneffects.push_back(motionBlur);
    this->fullscreeneffects.push_back(simpleDoF);
    this->fullscreeneffects.push_back(edgeDetection);
    this->fullscreeneffects.push_back(toon);
    this->fullscreeneffects.push_back(grayscale);
    this->fullscreeneffects.push_back(saturate);
    this->fullscreeneffects.push_back(pixelate);
    this->fullscreeneffects.push_back(volumetricLightScattering);
    this->fullscreeneffects.push_back(shadows);

    // Create a renderer.
    this->renderer = new Renderer();

    // Add a rendering view to the renderer
    this->renderer->AddRenderingView(new PostProcessingRenderingView(*viewport, wobble));
}

/**
 * Setup handler.
 *
 * This is the main setup method of the game factory. Here you can add
 * any non-standard modules and perform other setup tasks prior to the
 * engine start up.
 *
 * @param engine The game engine instance.
 */
bool GameFactory::SetupEngine(IGameEngine& engine) {

    // Add mouse and keyboard module here
    SDLInput* input = new SDLInput();
    engine.AddModule(*input);

    // Add Statistics module
    engine.AddModule(*(new OpenEngine::Utils::Statistics(1000)));

    // Create a root scene node
    SceneNode* scene = new SceneNode();

    // Supply the scene to the renderer
    this->renderer->SetSceneRoot(scene);

    // Add RenderStateNode to change rendering features at runtime
    RenderStateNode* rNode = new RenderStateNode();
    rNode->AddOptions(RenderStateNode::RENDER_TEXTURES);
    rNode->AddOptions(RenderStateNode::RENDER_SHADERS);
    rNode->AddOptions(RenderStateNode::RENDER_BACKFACES);
    scene->AddNode(rNode);

    // Bind keys for changing rendering state
    RenderStateHandler* renderStateHandler = new RenderStateHandler(rNode);
    renderStateHandler->BindToEventSystem();

    // Bind the quit handler
    QuitHandler* quit_h = new QuitHandler();
    quit_h->BindToEventSystem();

    // Bind the camera to the viewport
    //FollowCamera* camera = new FollowCamera( *(new InterpolatedViewingVolume( *(new ViewingVolume()) )));
    //Camera* camera = new Camera( *(new InterpolatedViewingVolume( *(new ViewingVolume()) )));
    Camera* camera = new Camera(  *(new ViewingVolume()) );
    Frustum* frustum = new Frustum(*camera, 20, 5000);
    viewport->SetViewingVolume(frustum);

    // Register movement handler to be able to move the camera
    MoveHandler* move = new MoveHandler(*camera);
    move->BindToEventSystem();
    engine.AddModule(*move);

    // set the resources directory
    string resources = "projects/VolumetricLightTest/data/";
    ResourceManager::SetPath(resources);
    logger.info << "Resource directory: " << resources << logger.end;

    // load the resource plug-ins
    ResourceManager::AddModelPlugin(new OBJPlugin());
    ResourceManager::AddTexturePlugin(new TGAPlugin());
    ResourceManager::AddShaderPlugin(new GLSLPlugin());

    // pointer to Box transformation node
    RigidBox* box = NULL;
    Vector<3,float> position(2, 100, 2);

    // Add models from models.txt to the scene
    ISceneNode* current = rNode;
    ISceneNode* dynamicObjects = new SceneNode();
    ISceneNode* staticObjects  = new SceneNode();
    ISceneNode* physicObjects  = new SceneNode();
    TransformationNode* sunTransNode = NULL;
    GeometryNode*       sunGeoNode2 = NULL;
    TransformationNode* lightsTransNode = NULL;
    GeometryNode*       lightsGeoNode2 = NULL;

    // Open the models file
    ifstream* mfile = File::Open("projects/VolumetricLightTest/models.txt");

    bool dynamic = false;
    while (!mfile->eof()) {
        string mod_str;
        getline(*mfile, mod_str);

        // Check the string
        if (mod_str[0] == '#' || mod_str == "") continue;

        // switch to static elements
        if (mod_str == "dynamic") {
            dynamic = true;
            current = dynamicObjects;
            continue;
        }
        else if (mod_str == "static") {
            dynamic = false;
            current = staticObjects;
            continue;
        }
        else if (mod_str == "physic") {
            dynamic = false;
            current = physicObjects;
            continue;
        }

        // Load the model
        IModelResourcePtr mod_res = ResourceManager::CreateModel(mod_str);
        mod_res->Load();
        if( mod_res->GetFaceSet() == NULL ) continue;

        GeometryNode* mod_node = new GeometryNode();
        mod_node->SetFaceSet(mod_res->GetFaceSet());
        GeometryNode* mod_node2 = new GeometryNode();
        mod_node2->SetFaceSet(mod_res->GetFaceSet());
        mod_res->Unload();

        TransformationNode* mod_tran = new TransformationNode();
        mod_tran->AddNode(mod_node);

        if (mod_str == "TestLightScene/TestLightSceneSun.obj") {
            sunTransNode = mod_tran;
            sunGeoNode2 = mod_node2;
	}

        if (mod_str == "TestLightScene/TestLightSceneLights.obj") {
            lightsTransNode = mod_tran;
            lightsGeoNode2 = mod_node2;
	}

        if (dynamic) {
            // Load ridget-box
            box = new RigidBox( Box(*(mod_node->GetFaceSet())) );
            box->SetCenter( position );
            box->SetTransformationNode(mod_tran);

            //camera->SetPosition(position + Vector<3,float>(-150,40,0)); // z, y, x
            //camera->SetPosition(position + Vector<3,float>(-150,-100,0)); // z, y, x
            camera->Rotate(-3.14/4.0, Vector<3,float>(0,1,0));
            camera->SetPosition(Vector<3,float>(-400,50,0)); // z, y, x

            //camera->LookAt(position);
            //camera->Follow(mod_tran);

        }
        current->AddNode(mod_tran);

        // add the node to the move handler
        move->nodes.push_back(mod_tran);
        logger.info << "Successfully loaded " << mod_str << logger.end;
    }
    mfile->close();
    delete mfile;

    //rNode->AddNode(dynamicObjects);

    // Process static tree
    logger.info << "Preprocessing of physics tree: started" << logger.end;
    QuadBSPBuilder quadbsp;
    QuadNode* hybridTreeRoot = quadbsp.Build(*physicObjects);
    FixedTimeStepPhysics* physic = new FixedTimeStepPhysics( hybridTreeRoot );
    logger.info << "Preprocessing of physics tree: done" << logger.end;

    // Add FixedTimeStepPhysics module
    //physic->AddRigidBody(box);
    //engine.AddModule(*physic, IGameEngine::TICK_DEPENDENT);

    logger.info << "Preprocessing of static tree: started" << logger.end;
    QuadTreeBuilder qtb(500,100);
    QuadNode* qn = qtb.Build(*staticObjects);
    rNode->AddNode(qn);
    logger.info << "Preprocessing of static tree: done" << logger.end;

    // Visualization of the frustum
    //frustum->VisualizeClipping(true);
    //rNode->AddNode(frustum->GetFrustumNode());

    // add the RigidBox to the scene, for debuging
    //if (box != NULL) rNode->AddNode( box->GetRigidBoxNode() );

    // Keyboard bindings to the rigid box and camera
    /*
    KeyboardHandler* keyHandler = new KeyboardHandler(camera,box,physic);
    keyHandler->BindToEventSystem();
    engine.AddModule(*keyHandler);
    */

    // add nodes to scene graph
    PostProcessingEffect* sunGlow = new Glow(viewport);
    VolumetricLightScattering* sunVolumetricLightScattering = new VolumetricLightScattering(viewport);
    sunGlow->Add(sunVolumetricLightScattering);
    ISceneNode* mergeblendnode = new MergeBlendNode(sunGlow,1);
    rNode->AddNode(dynamicObjects);
    sunTransNode->AddNode(mergeblendnode);
    mergeblendnode->AddNode(sunGeoNode2);

    PostProcessingEffect* lightGlow = new Glow(viewport);
    ISceneNode* mergeblendnode2 = new MergeBlendNode(lightGlow,1);
    lightsTransNode->AddNode(mergeblendnode2);
    mergeblendnode2->AddNode(lightsGeoNode2);


    // lav sunmodule
    SunModule* sunmodule = new SunModule(sunVolumetricLightScattering, sunTransNode, camera);
    engine.AddModule(*sunmodule, IGameEngine::TICK_INDEPENDENT);

    SunModule* sunmodule2 = new SunModule(volumetricLightScattering, sunTransNode, camera);
    engine.AddModule(*sunmodule2, IGameEngine::TICK_INDEPENDENT);

    printf("Sun TransNode = %x\n", sunTransNode);
    Test(scene, 0);


    // Register effect handler to be able to toggle effects
    EffectHandler* effectHandler = new EffectHandler(fullscreeneffects, showImage, sunmodule);
    effectHandler->BindToEventSystem();
    engine.AddModule(*effectHandler);


    // Return true to signal success.
    return true;
}

void GameFactory::Test(ISceneNode* node, int ident) {

    // ident
    for (int i=0; i<ident; i++) printf(" ");

    // print node
    if(dynamic_cast<GeometryNode*>(node) != NULL) {
	printf("GeoNode %x\n", node);
    } else if(dynamic_cast<TransformationNode*>(node) != NULL) {
	printf("TransNode %x\n", node);
    } else if(dynamic_cast<RenderStateNode*>(node) != NULL) {
	printf("RenderStateNode %x\n", node);
    } else {
	printf("OtherNode %x\n", node);
    }

    // visit subnodes
    list<ISceneNode*>::iterator itr;
    for (itr = node->subNodes.begin(); itr != node->subNodes.end(); itr++) {
        //(*itr)->Accept(visitor);
        ISceneNode* subnode = *itr;

        Test(subnode, ident+4);
    }

}



// Other factory methods. The returned objects are all created in the
// factory constructor.
IFrame*      GameFactory::GetFrame()    { return this->frame;    }
IRenderer*   GameFactory::GetRenderer() { return this->renderer; }
