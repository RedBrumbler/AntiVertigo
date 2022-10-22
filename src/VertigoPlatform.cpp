#include "VertigoPlatform.hpp"
#include "config.hpp"
#include "logging.hpp"
#include <string>

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

DEFINE_TYPE(AntiVertigo, VertigoPlatform);

namespace AntiVertigo {
    void VertigoPlatform::Initialize() {
        inMenu = true;
        SetActive(false);
    }

    void VertigoPlatform::SetActive(bool value) {
        get_gameObject()->SetActive(value);
    }

    void VertigoPlatform::OnEnable()
    {
        if (config.enabled)
        {
            INFO("Vertigo Platform enabling!");
            UpdateSize();
            SetMesh();
        }
    }

    void VertigoPlatform::OnDisable() {
        INFO("Vertigo Platform disabling!");
    }

    void VertigoPlatform::UpdateSize() {
        INFO("Setting new size!");
        float xmin = (float)(config.xmin - 1.5);
        float xmax = (float)(config.xmax + 1.5);
        float zmin = (float)(config.zmin - 1.0);
        float zmax = (float)(config.zmax + 1.0);

        float x = (xmax + xmin) / 2;
        float z = (zmax + zmin) / 2;
        float y = inMenu ? -0.05f : -0.15f;

        UnityEngine::Vector3 newSize = UnityEngine::Vector3(xmax - xmin, 1.0f, zmin - zmax);
        UnityEngine::Vector3 newPos = UnityEngine::Vector3(x, y, z);

        get_transform()->set_localScale(newSize);
        get_transform()->set_localPosition(newPos);
    }

    UnityEngine::Material* VertigoPlatform::get_darkEnvironmentSimpleMaterial() {
        if (darkEnvironmentSimpleMaterial && darkEnvironmentSimpleMaterial->m_CachedPtr.m_value) return darkEnvironmentSimpleMaterial;
        return darkEnvironmentSimpleMaterial = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>().FirstOrDefault([](auto mat){ return mat && mat->get_name() == "DarkEnvironmentSimple";});
    }

    void VertigoPlatform::CheckMaterials() {
        UnityEngine::Material* darkmat = get_darkEnvironmentSimpleMaterial();
        if (!darkmat) return;

        if (cube && cube->m_CachedPtr.m_value) {
            auto renderer = cube->GetComponent<UnityEngine::MeshRenderer*>();
            if (renderer->get_material()->get_name() != "DarkEnvironmentSimple") {
                renderer->set_material(darkmat);
            }
        }

        if (cylinder && cylinder->m_CachedPtr.m_value) {
            auto renderer = cylinder->GetComponent<UnityEngine::MeshRenderer*>();
            if (renderer->get_material()->get_name() != "DarkEnvironmentSimple") {
                renderer->set_material(darkmat);
            }
        }
    }

    void VertigoPlatform::SetMesh() {
        CheckMaterials();
        switch(config.shape) {
            default: // fallthrough
            case CUBE: {
                if (cube && cube->m_CachedPtr.m_value) {
                    cube->SetActive(true);
                } else {
                    cube = UnityEngine::GameObject::CreatePrimitive(3); // Cube = 3
                    cube->set_name("vertigoCube");
                    cube->get_transform()->SetParent(get_transform(), false);
                    cube->get_transform()->set_localScale(UnityEngine::Vector3(1.0f, 0.2f, 1.0f));
                }

                if (cylinder && cylinder->m_CachedPtr.m_value) {
                    cylinder->SetActive(false);
                }

                break;
            }
            case CYLINDER: {
                if (cylinder && cylinder->m_CachedPtr.m_value) {
                    CheckMaterials();
                    cylinder->SetActive(true);
                } else {
                    cylinder = UnityEngine::GameObject::CreatePrimitive(2); // Cylinder = 2
                    cylinder->set_name("vertigoCylinder");
                    cylinder->get_transform()->SetParent(get_transform(), false);
                    cylinder->get_transform()->set_localScale(UnityEngine::Vector3(1.0f, 0.1f, 1.0f));
                }

                if (cube && cube->m_CachedPtr.m_value) {
                    cube->SetActive(false);
                }

                break;
            }
        }
    }
}