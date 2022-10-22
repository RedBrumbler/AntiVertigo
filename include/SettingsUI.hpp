#pragma once

#include "VertigoPlatform.hpp"

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"

#include "UnityEngine/Transform.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#define SETTINGSUI_INTERFACES { classof(::System::IDisposable*), classof(::Zenject::IInitializable*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(AntiVertigo, SettingsUI, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "AntiVertigo", SETTINGSUI_INTERFACES, 0, nullptr, 
    DECLARE_PRIVATE_FIELD(UnityEngine::Transform*, root);
    DECLARE_PRIVATE_FIELD(VertigoPlatform*, _platform);
    DECLARE_PRIVATE_FIELD(List<Il2CppObject*>*, _shape_options);

    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(ListWrapper<Il2CppObject*>, get_shape_options);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());

    DECLARE_CTOR(ctor, VertigoPlatform* platform);

    DECLARE_BSML_PROPERTY(bool, enabled);
    DECLARE_BSML_PROPERTY(float, xmin);
    DECLARE_BSML_PROPERTY(float, xmax);
    DECLARE_BSML_PROPERTY(float, zmin);
    DECLARE_BSML_PROPERTY(float, zmax);
    DECLARE_BSML_PROPERTY(StringW, shape);
)