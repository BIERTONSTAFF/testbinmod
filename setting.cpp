#include "setting.h"

template <typename T>
Setting<T>::Setting(
    const QString &name,
    T *child,
    QWidget *parent
)
    : QWidget{parent},
    child{child}
{
    setFixedHeight(48);

    auto layout = new QHBoxLayout(this);
    auto label = new QLabel(name, this);

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(this->child);

    setLayout(layout);
}

template <typename T>
T *Setting<T>::getChild() const
{
    return this->child;
}

template class Setting<QComboBox>;
template class Setting<QCheckBox>;
template class Setting<QSpinBox>;
