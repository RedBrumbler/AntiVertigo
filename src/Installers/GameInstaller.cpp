#include "Installers/GameInstaller.hpp"
#include "PlatformManagers/GamePlatformManager.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(AntiVertigo, GameInstaller);

namespace AntiVertigo {
    void GameInstaller::InstallBindings() {
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<GamePlatformManager*>()->AsSingle();
    }
}