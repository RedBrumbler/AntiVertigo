#pragma once
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(AntiVertigo, VertigoPlatformBehaviour, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, OnEnable);
    DECLARE_METHOD(void, OnDisable);
    DECLARE_METHOD(void, UpdateSize);
    DECLARE_METHOD(void, SetMesh);

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnEnable);
        REGISTER_METHOD(OnDisable);
        REGISTER_METHOD(UpdateSize);
        REGISTER_METHOD(SetMesh);
    )
)