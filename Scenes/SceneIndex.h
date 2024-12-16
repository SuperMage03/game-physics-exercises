#include "Scene.h"
#include <map>

#include "Scene1.h"
#include "TestScene.h"
#include "SceneSingleStep.h"
#include "SceneExplicitSimulation.h"

using SceneCreator = std::function<std::unique_ptr<Scene>()>;

template <typename T>
SceneCreator creator()
{
    return []()
    { return std::make_unique<T>(); };
}

std::map<std::string, SceneCreator> scenesCreators = {
    // {"Demo Scene", creator<Scene1>()},
    {"Test Scene", creator<TestScene>()},
    {"Single Step", creator<SceneSingleStep>()},
    {"Explicit Simulation", creator<SceneExplicitSimulation>()}
    // add more Scene types here
};
