#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>

template <typename T>
class Setting : public QWidget
{
private:
    T *child;
public:
    explicit Setting(
        const QString &name = nullptr,
        T *child = nullptr,
        QWidget *parent = nullptr
    );

    T *getChild() const;
signals:
};

#endif // SETTING_H
