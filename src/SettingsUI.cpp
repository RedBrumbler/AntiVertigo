#include "SettingsUI.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "VertigoPlatform.hpp"
#include "PlatformManagers/SettingsPlatformManager.hpp"
#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(AntiVertigo, SettingsUI);

namespace AntiVertigo {
    void SettingsUI::ctor(VertigoPlatform* platform) {
        _platform = platform;
    }

    ListWrapper<Il2CppObject*> SettingsUI::get_shape_options() {
        if (!_shape_options) {
            _shape_options = List<Il2CppObject*>::New_ctor();
            _shape_options->Add(StringW("Cube"));
            _shape_options->Add(StringW("Cylinder"));
        }
        return _shape_options;
    }

    void SettingsUI::PostParse() {
        DEBUG("PostParse");
        root->get_gameObject()->AddComponent<SettingsPlatformManager*>()->platform = _platform;
    }

    void SettingsUI::Initialize() {
        DEBUG("Initialize");
        BSML::Register::RegisterSettingsMenu("Anti Vertigo", MOD_ID "_settings", this);
    }

    void SettingsUI::Dispose() {
        DEBUG("Dispose");
        BSML::Register::UnRegisterSettingsMenu(this);
    }

    bool SettingsUI::get_enabled() { return config.enabled; }
    void SettingsUI::set_enabled(bool value) { 
        config.enabled = value; 
        SaveConfig();
    }
    float SettingsUI::get_xmin() { return -config.xmin; }
    void SettingsUI::set_xmin(float value) { 
        config.xmin = -value; 
        SaveConfig();
        _platform->UpdateSize();
    }
    float SettingsUI::get_xmax() { return config.xmax; }
    void SettingsUI::set_xmax(float value) { 
        config.xmax = value; 
        SaveConfig();
        _platform->UpdateSize();
    }
    float SettingsUI::get_zmin() { return -config.zmin; }
    void SettingsUI::set_zmin(float value) { 
        config.zmin = -value; 
        SaveConfig();
        _platform->UpdateSize();
    }
    float SettingsUI::get_zmax() { return config.zmax; }
    void SettingsUI::set_zmax(float value) { 
        config.zmax = value; 
        SaveConfig();
        _platform->UpdateSize();
    }
    StringW SettingsUI::get_shape() { return get_shape_options()[config.shape]; }
    void SettingsUI::set_shape(StringW value) { 
        config.shape = get_shape_options()->IndexOf(value); 
        SaveConfig();
        _platform->SetMesh();
    }
}
