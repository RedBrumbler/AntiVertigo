#include "PlatformManagers/SettingsPlatformManager.hpp"

#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(AntiVertigo, SettingsPlatformManager);

namespace AntiVertigo {
    void SettingsPlatformManager::OnEnable() {
        if (platform && platform->m_CachedPtr.m_value) {
            platform->inMenu = true;
            platform->SetActive(true);
        }
    }
    
    void SettingsPlatformManager::OnDisable() {
        if (platform && platform->m_CachedPtr.m_value) {
            platform->SetActive(false);
        }
    }
}