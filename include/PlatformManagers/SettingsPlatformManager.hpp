#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "VertigoPlatform.hpp"

DECLARE_CLASS_CODEGEN(AntiVertigo, SettingsPlatformManager, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(VertigoPlatform*, platform);
    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnDisable);
)