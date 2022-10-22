#include "Installers/AppInstaller.hpp"
#include "VertigoPlatform.hpp"

#include "UnityEngine/GameObject.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(AntiVertigo, AppInstaller);

namespace AntiVertigo {
    void AppInstaller::InstallBindings() {
        auto container = get_Container();

        auto go = UnityEngine::GameObject::New_ctor();
        UnityEngine::Object::DontDestroyOnLoad(go);
        go->set_name("AntiVertigoPlatform");
        container->BindInterfacesAndSelfTo<VertigoPlatform*>()->FromNewComponentOn(go)->AsSingle()->Lazy();
    }
}