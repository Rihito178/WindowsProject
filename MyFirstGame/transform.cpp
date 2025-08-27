#include "transform.h"

Transform::Transform()
{
    XMFLOAT3 a;

    a.x = 10.0f;

    a.y = 20.0f;

    a.z = 30.0f;


}

Transform::~Transform()
{

}

void Transform::Calculation()
{
}



XMMATRIX Transform::GetWorldMatrix()
{
    return XMMATRIX();
}
