#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "VertigoPlatform.hpp"
#include "System/IDisposable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(AntiVertigo, GamePlatformManager, Il2CppObject, classof(System::IDisposable*),
    DECLARE_PRIVATE_FIELD(AntiVertigo::VertigoPlatform*, _platform);
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    DECLARE_CTOR(ctor, AntiVertigo::VertigoPlatform* platform);
)