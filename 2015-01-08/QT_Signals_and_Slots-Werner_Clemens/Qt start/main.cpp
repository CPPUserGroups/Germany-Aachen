#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include "data.h"
#include "trigger_examples.h"
#include "update_examples.h"


int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  auto* pWidget = new QWidget;
  pWidget->show();

  auto* pBox = new QVBoxLayout(pWidget);
  pBox->addWidget(newTriggerExamples());

  Data data;
  pBox->addWidget(newUpdateExamples(&data));

  return app.exec();
}
