#pragma once
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/GameObject.hpp"
#include "Zenject/IInitializable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(AntiVertigo, VertigoPlatform, UnityEngine::MonoBehaviour, classof(::Zenject::IInitializable*),
    DECLARE_INSTANCE_FIELD(bool, inMenu);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, cube);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, cylinder);
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, darkEnvironmentSimpleMaterial);

    DECLARE_INSTANCE_METHOD(UnityEngine::Material*, get_darkEnvironmentSimpleMaterial);
    DECLARE_INSTANCE_METHOD(void, SetActive, bool value);
    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnDisable);
    DECLARE_INSTANCE_METHOD(void, UpdateSize);
    DECLARE_INSTANCE_METHOD(void, SetMesh);
    DECLARE_INSTANCE_METHOD(void, CheckMaterials);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
)