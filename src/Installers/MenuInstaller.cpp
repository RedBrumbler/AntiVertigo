#include "Installers/MenuInstaller.hpp"
#include "SettingsUI.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(AntiVertigo, MenuInstaller);

namespace AntiVertigo {
    void MenuInstaller::InstallBindings() {
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<SettingsUI*>()->AsSingle();
    }
}