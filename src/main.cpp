#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "modloader/shared/modloader.hpp"

#include "SettingsViewController.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "VertigoPlatformBehaviour.hpp"
#include "config.hpp"

#include <string>

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "custom-types/shared/register.hpp"

#include "hooks.hpp"
#include "logging.hpp"

static ModInfo modInfo;
extern config_t config;

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output);
std::string activeSceneName = "";

MAKE_AUTO_HOOK_MATCH(SceneManager_SetActiveScene, &UnityEngine::SceneManagement::SceneManager::SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);
    INFO("Found scene %s", activeSceneName.c_str());
    if (activeSceneName == "GameCore" && config.enabled) // in gamecore, enable the platform
    {
        ArrayW<AntiVertigo::VertigoPlatformBehaviour*> platforms = UnityEngine::Resources::FindObjectsOfTypeAll<AntiVertigo::VertigoPlatformBehaviour*>();
        if (platforms.Length() == 0)
        {
            UnityEngine::GameObject* newObj = UnityEngine::GameObject::New_ctor();
            newObj->DontDestroyOnLoad(newObj);
            newObj->AddComponent<AntiVertigo::VertigoPlatformBehaviour*>();
        }
        else
        {
            platforms[0]->get_gameObject()->SetActive(true);
        }
    }
    else // not gamecore means disable (? -> depends on the other menus, wether or not they have big holes)
    {
        ArrayW<AntiVertigo::VertigoPlatformBehaviour*> platforms = UnityEngine::Resources::FindObjectsOfTypeAll<AntiVertigo::VertigoPlatformBehaviour*>();
        if (platforms.Length() != 0)
        {
            platforms[0]->get_gameObject()->SetActive(false);
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
    Hooks::InstallHooks(AntiVertigo::Logging::getLogger());
    custom_types::Register::AutoRegister();

    QuestUI::Register::RegisterModSettingsViewController<AntiVertigo::SettingsViewController*>((ModInfo){"Anti Vertigo", VERSION}, "Anti Vertigo");
}

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = AntiVertigo::Logging::getLogger().WithContext("scene name");
    Il2CppString* csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = to_utf8(csstrtostr(csString));
    return true;
}