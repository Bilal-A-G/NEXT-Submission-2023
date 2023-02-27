#pragma once
#include <cassert>

#include "Math.h"
#include "Geometry.h"

namespace GAUSS_TESTS
{
    inline void CheckMath()
    {
        assert(GAUSS::Vector3::Zero() == GAUSS::Vector3(0, 0, 0));
        assert(GAUSS::Vector4::Zero() == GAUSS::Vector4(0, 0, 0, 0));
    
        assert(GAUSS::Vector3(1, 1, 1) + GAUSS::Vector3(1, 1, 1) == GAUSS::Vector3(2, 2, 2));
        assert(GAUSS::Vector4(1, 1, 1, 1) + GAUSS::Vector4(1, 1, 1, 1) == GAUSS::Vector4(2, 2, 2, 2));

        assert(GAUSS::Vector3(1, 1, 1) - GAUSS::Vector3(1, 1, 1) == GAUSS::Vector3::Zero());
        assert(GAUSS::Vector4(1, 1, 1, 1) - GAUSS::Vector4(1, 1, 1, 1) == GAUSS::Vector4::Zero());

        assert(GAUSS::Vector3(1, 1, 1) / 2 == GAUSS::Vector3(0.5f, 0.5f, 0.5f));
        assert(GAUSS::Vector4(1, 1, 1, 1) / 2 == GAUSS::Vector4(0.5f, 0.5f, 0.5f, 0.5f));

        assert(GAUSS::Vector3(1, 1, 1) * 2 == GAUSS::Vector3(2, 2, 2));
        assert(GAUSS::Vector4(1, 1, 1, 1) * 2 == GAUSS::Vector4(2, 2, 2, 2));

        assert(GAUSS::Vector3::Dot(GAUSS::Vector3(1, 1, 1), GAUSS::Vector3(2, 2, 2)) == 6.0f);
        assert(GAUSS::Vector3::Cross(GAUSS::Vector3(1, 0, 0), GAUSS::Vector3(0, 0, 1)) == GAUSS::Vector3(0, -1, 0));
        assert(GAUSS::Vector3(1, 0, 0).Magnitude() == 1.0f);
        assert(GAUSS::Vector3(-1, 1, 1).Abs() == GAUSS::Vector3(1, 1, 1));

        assert(GAUSS::Lerp<float>(1, 2, 0.5f) == 1.5f);

        assert(GAUSS::Matrix4x4::Identity() ==
            GAUSS::Matrix4x4(
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            ));
        
        assert(GAUSS::Matrix4x4::Identity() + GAUSS::Matrix4x4::Identity() == GAUSS::Matrix4x4(
                                                            {2, 0, 0, 0},
                                                            {0, 2, 0, 0},
                                                            {0, 0, 2, 0},
                                                            {0, 0, 0, 2}
                                                        ));
        assert(GAUSS::Matrix4x4::Identity() * GAUSS::Matrix4x4::Identity() == GAUSS::Matrix4x4::Identity());
        assert(GAUSS::Matrix4x4::Identity() * GAUSS::Vector4(1, 1, 1, 1) == GAUSS::Vector4(1, 1, 1, 1));
    }   
}


