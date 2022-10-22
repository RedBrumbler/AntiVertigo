#include "hooks.hpp"

#include "SettingsUI.hpp"
#include "VertigoPlatform.hpp"
#include "config.hpp"
#include "assets.hpp"

#include <string>

#include "custom-types/shared/register.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#include "hooks.hpp"
#include "logging.hpp"

#include "Installers/AppInstaller.hpp"
#include "Installers/GameInstaller.hpp"
#include "Installers/MenuInstaller.hpp"

static ModInfo modInfo;
std::string activeSceneName = "";

extern "C" void Setup(ModInfo info)
{
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load()
{
    if (!LoadConfig())
        SaveConfig();
    il2cpp_functions::Init();
    Hooks::InstallHooks(getLogger());
    custom_types::Register::AutoRegister();

    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<AntiVertigo::AppInstaller*>(Lapiz::Zenject::Location::App);
    zenjector->Install<AntiVertigo::MenuInstaller*>(Lapiz::Zenject::Location::Menu);
    zenjector->Install<AntiVertigo::GameInstaller*>(Lapiz::Zenject::Location::StandardPlayer);
}

BSML_DATACACHE(settings) {
    return IncludedAssets::Settings_bsml;
}