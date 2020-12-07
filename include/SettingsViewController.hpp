#pragma once
#include "HMUI/ViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(AntiVertigo, SettingsViewController, HMUI::ViewController,
    // Override DidActivate, which is called whenever you enter the menu
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);
    REGISTER_FUNCTION(SettingsViewController,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)