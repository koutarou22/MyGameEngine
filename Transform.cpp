#include "Transform.h"

Transform::Transform()
    :position_({0,0,0}),
    rotate_({ 0,0,0 }),
    scale_({ 1,1,1 }),
    matTranslate_(XMMatrixIdentity()),
    matRotate_(XMMatrixIdentity()),
    matScale_(XMMatrixIdentity())
{
 /*   float x = XMVectorGetX(position_);
    float y = XMVectorGetY(position_);
    float z = XMVectorGetZ(position_);
    float w = XMVectorGetW(position_):*/

}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //SRTÇÃèáî‘Ç≈ä|ÇØÇÈÇ∆ÅAÉèÅ[ÉãÉhïœä∑Ç…Ç»ÇÈ
   /* float tx = XMVectorGetX(position_);
    float ty = XMVectorGetY(position_);
    float tz = XMVectorGetZ(position_);*/
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    //R=Z*X*YÇÃèáî‘Ç≈çsóÒÇä|ÇØÇÈÇ∆DirectXÇÃâÒì]Ç…Ç»ÇÈÇÊ

   /* float tmp_rx = XMConvertToRadiansX(XMConvertToRadians(rotate_.x));
    float tmp_ry = XMConvertToRadiansY(XMConvertToRadians(rotate_.y));
    float tmp_rz = XMConvertToRadiansZ(XMConvertToRadians(rotate_/z));*/


    XMMATRIX rx = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    XMMATRIX ry = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    XMMATRIX rz = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rz * rx * ry;

 /*   float sx = XMVectorGetX(scale_);
    float sy = XMVectorGetY(scale_);
    float sz = XMVectorGetZ(scale_);*/
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);

}

XMMATRIX Transform::GetWorldMatrix()
{
    return matScale_ * matRotate_ * matTranslate_;
}
