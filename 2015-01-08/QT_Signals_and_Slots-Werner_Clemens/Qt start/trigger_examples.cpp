#include <QBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include "data.h"
#include "trigger_examples.h"

using namespace std;


void log(const QString& s) 
{
  Log::log(s.toStdString());
}


QDialog* newLogWindow()
{
  auto* pLog = new QDialog;
  pLog->setWindowTitle("Log window");
  pLog->setModal(false);

  auto* pVBox = new QVBoxLayout(pLog);
  auto* pLabel = new QLabel;
  pVBox->addWidget(pLabel);
  pVBox->addStretch(1);

  auto* pTimer = new QTimer(pLog);
  pTimer->start();
  QObject::connect(pTimer, &QTimer::timeout, [pLabel]{ pLabel->setText(Log::singleton().text().c_str()); });

  return pLog;
}


QWidget* newTriggerExamples()
{
  auto* pBar = new QToolBar;

  auto* pLogAction = new QAction(pBar);
  pLogAction->setText("Open log window");
  addTriggerSlot(pLogAction, [pLogAction]{ log(pLogAction->text()); });
  addTriggerSlot(pLogAction, []{ newLogWindow()->show(); });
  pBar->addAction(pLogAction);

  pBar->addAction(new SlotAction(pBar));
  pBar->addAction(new FunctionAction(pBar));
  pBar->addAction(newActionLambda(pBar));
  pBar->addAction(newActionTriggerChild(pBar));

  return pBar;
}


