#include "SettingsViewController.hpp"
#include "config.hpp"

extern config_t config;

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/InputFieldView.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "VertigoPlatformBehaviour.hpp"

#include <cstdlib>
#include <vector>
#include <string>

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

DEFINE_CLASS(AntiVertigo::SettingsViewController);

std::vector<std::string> shapes = {
    "Cube",
    "Cylinder"
};

void AntiVertigo::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    AntiVertigo::VertigoPlatformBehaviour* platform = Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>();
    if (!platform)
    {
        GameObject* newObj = GameObject::New_ctor();
        newObj->DontDestroyOnLoad(newObj);
        platform = newObj->AddComponent<AntiVertigo::VertigoPlatformBehaviour*>();
    }

    platform->get_gameObject()->SetActive(true);

    if (firstActivation)
    {
        get_gameObject()->AddComponent<Touchable*>();
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        BeatSaberUI::CreateToggle(container->get_transform(), "Enable Anti Vertigo Platform", config.enabled, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](SettingsViewController* view, bool value) { 
                config.enabled = value;
                SaveConfig();
            }));
        BeatSaberUI::CreateText(container->get_transform(), "");
        BeatSaberUI::CreateText(container->get_transform(), "== Platform size settings ==");
        QuestUI::IncrementSetting* xmin = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Platform left side offset", 2, 0.2f, -config.xmin, 0.0f, 1000, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SettingsViewController* view, float value) {
                config.xmin = -value;
                SaveConfig();
                Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>()->UpdateSize();
            }));
        BeatSaberUI::AddHoverHint(xmin->get_gameObject(), "How far the platform extends to the left side");
        QuestUI::IncrementSetting* xmax = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Platform right side offset", 2, 0.2f, config.xmax, 0.0f, 1000, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SettingsViewController* view, float value) {
                config.xmax = value;
                SaveConfig();
                Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>()->UpdateSize();
            }));
        BeatSaberUI::AddHoverHint(xmax->get_gameObject(), "How far the platform extends to the right side");
        QuestUI::IncrementSetting* zmin = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Platform back side offset", 2, 0.2f, -config.zmin, 0.0f, 1000, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SettingsViewController* view, float value) {
                config.zmin = -value;
                SaveConfig();
                Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>()->UpdateSize();
            }));
        BeatSaberUI::AddHoverHint(zmin->get_gameObject(), "How far the platform extends to the back side");
        QuestUI::IncrementSetting* zmax = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Platform front side offset", 2, 0.2f, config.zmax, 0.0, 1000, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SettingsViewController* view, float value) {
                config.zmax = value;
                SaveConfig();
                Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>()->UpdateSize();
            }));
        BeatSaberUI::AddHoverHint(zmax->get_gameObject(), "How far the platform extends to the front side");
        
        QuestUI::IncrementSetting* shape = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Shape of the platform", 0, 1.0f, config.shape, 0.0f, 1.0f, nullptr);
        shape->OnValueChange = il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), shape, +[](QuestUI::IncrementSetting* self, float value) {
                config.shape = value;
                SaveConfig();
                Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>()->SetMesh();
                self->Text->SetText(il2cpp_utils::createcsstr(shapes[value]));
            });
        shape->Text->SetText(il2cpp_utils::createcsstr(shapes[config.shape]));
        BeatSaberUI::AddHoverHint(shape->get_gameObject(), "The shape of the platform");
    }
}

void AntiVertigo::SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
{
    AntiVertigo::VertigoPlatformBehaviour* platform = Object::FindObjectOfType<AntiVertigo::VertigoPlatformBehaviour*>();
    if (!platform)
    {
        GameObject* newObj = GameObject::New_ctor();
        newObj->DontDestroyOnLoad(newObj);
        platform = newObj->AddComponent<AntiVertigo::VertigoPlatformBehaviour*>();
    }

    platform->get_gameObject()->SetActive(false);
}