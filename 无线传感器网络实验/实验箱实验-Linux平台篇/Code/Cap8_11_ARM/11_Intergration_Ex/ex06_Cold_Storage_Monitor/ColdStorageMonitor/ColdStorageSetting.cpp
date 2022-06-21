#include "ColdStorageSetting.h"

ColdStorageSetting *ColdStorageSetting::_csSetting = NULL;
ColdStorageSetting::ColdStorageSetting(QObject *parent)
    : QObject(parent)
    , _minThreshold(-40.5), _maxThreshold(-5.3)
{
}

void ColdStorageSetting::setThreshold(float min, float max)
{
    _minThreshold = min;
    _maxThreshold = max;
}

float ColdStorageSetting::minThreshold() const
{
    return _minThreshold;
}

float ColdStorageSetting::maxThreshold() const
{
    return _maxThreshold;
}

void ColdStorageSetting::changeThreshold(float min, float max)
{
    setThreshold(min, max);
    emit this->thresholdChanged(_minThreshold, _maxThreshold);
}

ColdStorageSetting *ColdStorageSetting::Instance()
{
    return _csSetting;
}

ColdStorageSetting *ColdStorageSetting::Create()
{
    if(_csSetting != NULL)
        return _csSetting;
    _csSetting = new ColdStorageSetting();
    return _csSetting;
}

void ColdStorageSetting::Destroy()
{
    if(_csSetting)
        delete _csSetting;
    _csSetting = NULL;
}
