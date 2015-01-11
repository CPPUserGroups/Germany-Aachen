#pragma once
#include <functional>
#include <QAction>
#include <QObject>


class TriggerObject : public QObject
{
public:
  TriggerObject(QAction* pAction, const std::function<void(void)>& func) 
    : QObject(pAction), m_func(func) 
  {
    connect(pAction, &QAction::triggered, this, &TriggerObject::callFunc);
  }

private:
  void callFunc() { m_func(); }
  std::function<void(void)> m_func;
};


inline void addTriggerSlot(QAction* pAction, const std::function<void(void)>& func)
{
  new TriggerObject(pAction, func);
}
