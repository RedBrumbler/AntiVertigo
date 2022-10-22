#include "PlatformManagers/GamePlatformManager.hpp"
#include "config.hpp"

#include "UnityEngine/GameObject.hpp" 

DEFINE_TYPE(AntiVertigo, GamePlatformManager);

namespace AntiVertigo {
    void GamePlatformManager::ctor(VertigoPlatform* platform) {
        _platform = platform;
        _platform->inMenu = false;
        _platform->SetActive(config.enabled);
    }

    void GamePlatformManager::Dispose() {
        _platform->SetActive(false);
    }
}