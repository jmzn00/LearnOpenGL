#include "Material.h"

Material Material::Gold()
{
    return 
    {
        {0.24725f, 0.1995f, 0.0745f},
        {0.75164f, 0.60648f, 0.22648f},
        {0.628281f, 0.555802f, 0.366065f},
        32.0f
    };
}
Material Material::Silver()
{
    return {
        {0.19225f, 0.19225f, 0.19225f},
        {0.50754f, 0.50754f, 0.50754f},
        {0.508273f, 0.508273f, 0.508273f},
        32.0f
    };
}