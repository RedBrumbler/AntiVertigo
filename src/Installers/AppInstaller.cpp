#include "Installers/AppInstaller.hpp"
#include "VertigoPlatform.hpp"

#include "UnityEngine/GameObject.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"
DEFINE_TYPE(AntiVertigo, AppInstaller);

using namespace Lapiz::Zenject::ZenjectExtensions;

namespace AntiVertigo {
    void AppInstaller::InstallBindings() {
        auto container = get_Container();

        auto params = ::Zenject::GameObjectCreationParameters::New_ctor();
        params->set_Name("VertigoPlatform");
        FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<VertigoPlatform*>(), params)->AsSingle()->Lazy();
    }
}