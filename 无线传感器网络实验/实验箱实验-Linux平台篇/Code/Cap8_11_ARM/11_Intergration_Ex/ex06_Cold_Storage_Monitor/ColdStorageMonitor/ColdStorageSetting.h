#ifndef COLDSTORAGESETTING_H
#define COLDSTORAGESETTING_H

#include <QObject>

class ColdStorageSetting : public QObject
{
    Q_OBJECT
public:
    explicit ColdStorageSetting(QObject *parent = 0);

    float minThreshold() const;
    float maxThreshold() const;

    static ColdStorageSetting *Instance();
    static ColdStorageSetting *Create();
    static void Destroy();

signals:
    void thresholdChanged(float min, float max);

public slots:
    void setThreshold(float min, float max);
    void changeThreshold(float min, float max);

private:
    static ColdStorageSetting *_csSetting;
    float _minThreshold, _maxThreshold;
};

#endif // COLDSTORAGESETTING_H
