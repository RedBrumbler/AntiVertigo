#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp" 
#include "beatsaber-hook/shared/utils/typedefs.h"

#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "SettingsViewController.hpp"
#include "config.hpp"
#include "VertigoPlatformBehaviour.hpp"

#include <string>

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "custom-types/shared/register.hpp"

static ModInfo modInfo;
extern config_t config;

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output);
std::string activeSceneName = "";

Logger& getLogger()
{
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);
    getLogger().info("Found scene %s", activeSceneName.c_str());
    if (activeSceneName == "GameCore" && config.enabled) // in gamecore, enable the platform
    {
        AntiVertigo::VertigoPlatformBehaviour* platform = UnityEngine::Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>();
        if (!platform)
        {
            UnityEngine::GameObject* newObj = UnityEngine::GameObject::New_ctor();
            newObj->DontDestroyOnLoad(newObj);
            platform = newObj->AddComponent<AntiVertigo::VertigoPlatformBehaviour*>();
        }

        platform->get_gameObject()->SetActive(true);
    }
    else // not gamecore means disable (? -> depends on the other menus, wether or not they have big holes)
    {
        AntiVertigo::VertigoPlatformBehaviour* platform = UnityEngine::Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>();
        if (platform)
        {
            platform->get_gameObject()->SetActive(false);
        }
    }

    return SceneManager_SetActiveScene(scene);
}


extern "C" void Setup(ModInfo info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load()
{
    if (!LoadConfig())
        SaveConfig();
    il2cpp_functions::Init();
    QuestUI::Init();
    LoggerContextObject logger = getLogger().WithContext("load");
    INSTALL_HOOK_OFFSETLESS(logger, SceneManager_SetActiveScene, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));

    custom_types::Register::RegisterType<AntiVertigo::VertigoPlatformBehaviour>();
    custom_types::Register::RegisterType<AntiVertigo::SettingsViewController>();

    QuestUI::Register::RegisterModSettingsViewController<AntiVertigo::SettingsViewController*>((ModInfo){"Anti Vertigo", VERSION}, "Anti Vertigo");
}

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = getLogger().WithContext("scene name");
    Il2CppString* csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = to_utf8(csstrtostr(csString));
    return true; 
}