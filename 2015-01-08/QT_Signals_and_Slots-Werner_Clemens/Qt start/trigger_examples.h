#pragma once
#include "trigger.h"

class QLabel;
class QWidget;
class QString;


void log(const QString& s); 
QDialog* newLogWindow();
QWidget* newTriggerExamples();


class SlotAction : public QAction
{
  Q_OBJECT
public:
  SlotAction(QObject* pParent) : QAction(pParent) 
  {
    setText("SlotAction");
    connect(this, SIGNAL(triggered()), this, SLOT(doAction()));
  }
private slots:
  void doAction() { log(text()); }
};


class FunctionAction : public QAction
{
public:
  FunctionAction(QObject* pParent) : QAction(pParent) 
  {
    setText("FunctionAction");
    connect(this, &QAction::triggered, this, &FunctionAction::doAction);
  }
private:
  void doAction() { log(text()); }
};


inline QAction* newActionLambda(QObject* pParent)
{
  auto* pAction = new QAction(pParent);
  pAction->setText("QAction + lambda");
  QObject::connect(pAction, &QAction::triggered, [pAction]{ log(pAction->text()); });
  return pAction;
}


inline QAction* newActionTriggerChild(QObject* pParent)
{
  auto* pAction = new QAction(pParent);
  pAction->setText("QAction + addTriggerSlot");
  addTriggerSlot(pAction, [pAction]{ log(pAction->text()); });
  return pAction;
}
