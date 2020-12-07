#pragma once
#include "../extern/beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"
#include "modloader/shared/modloader.hpp"
#include <string>
typedef enum _shape_t {
    CUBE = 0,
    CYLINDER = 1
} shape_t;


typedef struct _config_t {
    bool enabled = true;
    double xmin = -5.0;
    double xmax = 5.0;
    double zmin = -5.0;
    double zmax = 20.0;
    int shape = 0;
} config_t;


Configuration& getConfig();
void SaveConfig();
bool LoadConfig();