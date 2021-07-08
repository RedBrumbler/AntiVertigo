#include "VertigoPlatformBehaviour.hpp"
#include "config.hpp"
#include <string>
extern config_t config;
extern std::string activeSceneName;
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/MeshFilter.hpp"
#include "UnityEngine/Mesh.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/TextMeshPro.hpp"

DEFINE_TYPE(AntiVertigo, VertigoPlatformBehaviour);

extern Logger& getLogger();
#define getPlatformLogger() getLogger()

namespace AntiVertigo
{
    void VertigoPlatformBehaviour::Awake()
    {

    }

    void VertigoPlatformBehaviour::OnEnable()
    {
        if (config.enabled) 
        {
            getPlatformLogger().info("Vertigo Platform enabling!");
            UpdateSize();
            SetMesh();
        }
    }

    void VertigoPlatformBehaviour::OnDisable()
    {
        getPlatformLogger().info("Vertigo Platform disabling!");
    }

    void VertigoPlatformBehaviour::UpdateSize()
    {
        getPlatformLogger().info("Setting new size!");
        float xmin = (float)(config.xmin - 1.5);
        float xmax = (float)(config.xmax + 1.5);
        float zmin = (float)(config.zmin - 1.0);
        float zmax = (float)(config.zmax + 1.0);

        float x = (xmax + xmin) / 2;
        float z = (zmax + zmin) / 2;
        float y = activeSceneName == "GameCore" ? -0.15f : -0.05f;
        UnityEngine::Vector3 newSize = UnityEngine::Vector3(xmax - xmin, 1.0f, zmin - zmax);
        UnityEngine::Vector3 newPos = UnityEngine::Vector3(x, y, z);

        get_transform()->set_localScale(newSize);
        get_transform()->set_localPosition(newPos);
    }

    void VertigoPlatformBehaviour::SetMesh()
    {
        std::string lookingFor = "";
        Il2CppString* transformName = nullptr;
        switch(config.shape)
        {
            default: // fallthrough
            case CUBE:
                lookingFor += "vertigoCube";
                transformName = il2cpp_utils::createcsstr(lookingFor);
                if (UnityEngine::Transform* cube = get_transform()->Find(transformName))
                {
                    cube->get_gameObject()->SetActive(true);
                }
                else
                {
                    UnityEngine::GameObject* cubeGO = UnityEngine::GameObject::CreatePrimitive(3); // Cube = 3
                    cubeGO->set_name(transformName);
                    cubeGO->get_transform()->SetParent(get_transform(), false);
                    cubeGO->get_transform()->set_localScale(UnityEngine::Vector3(1.0f, 0.2f, 1.0f));

                    Array<UnityEngine::Material*>* allMats = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>();
                    std::string matName = "";
                    if (allMats)
                    {
                        for (int i = 0; i < allMats->Length(); i++)
                        {
                            if (!allMats->values[i]) continue;
                            matName = to_utf8(csstrtostr(allMats->values[i]->get_name()));
                            if (matName == "DarkEnvironmentSimple")
                            {
                                cubeGO->GetComponent<UnityEngine::MeshRenderer*>()->set_material(allMats->values[i]);
                                break;
                            }
                        }
                    }
                }
                transformName = il2cpp_utils::createcsstr("vertigoCylinder");
                if (UnityEngine::Transform* cylinder = get_transform()->Find(transformName))
                {
                    cylinder->get_gameObject()->SetActive(false);
                }
                break;
            case CYLINDER:
                lookingFor += "vertigoCylinder";
                transformName = il2cpp_utils::createcsstr(lookingFor);
                if (UnityEngine::Transform* cylinder = get_transform()->Find(transformName))
                {
                    cylinder->get_gameObject()->SetActive(true);
                }
                else
                {
                    UnityEngine::GameObject* cylinderGO = UnityEngine::GameObject::CreatePrimitive(2); // Cylinder = 2
                    cylinderGO->set_name(transformName);
                    cylinderGO->get_transform()->SetParent(get_transform(), false);
                    cylinderGO->get_transform()->set_localScale(UnityEngine::Vector3(1.0f, 0.1f, 1.0f));

                    Array<UnityEngine::Material*>* allMats = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>();
                    std::string matName = "";
                    if (allMats)
                    {
                        for (int i = 0; i < allMats->Length(); i++)
                        {
                            if (!allMats->values[i]) continue;
                            matName = to_utf8(csstrtostr(allMats->values[i]->get_name()));
                            if (matName == "DarkEnvironmentSimple")
                            {
                                cylinderGO->GetComponent<UnityEngine::MeshRenderer*>()->set_material(allMats->values[i]);
                                break;
                            }
                        }
                    }
                }
                transformName = il2cpp_utils::createcsstr("vertigoCube");
                if (UnityEngine::Transform* cube = get_transform()->Find(transformName))
                {
                    cube->get_gameObject()->SetActive(false);
                }
                break;
        }
    }
}