#include <QAction>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QToolBar>
#include "data.h"
#include "update.h"
#include "update_examples.h"

using namespace std;


QAction* newUndoAction(QWidget* pParent) 
{
  auto* pAction = new QAction(pParent);
  pAction->setText("Undo");
  QObject::connect(pAction, &QAction::triggered, []{ History::singleton().undo(); });
  return pAction;
}

QAction* newRedoAction(QWidget* pParent) 
{
  auto* pAction = new QAction(pParent);
  pAction->setText("Redo");
  QObject::connect(pAction, &QAction::triggered, []{ History::singleton().redo(); });
  return pAction;
}


QWidget* newUpdateExamples(Data* pData)
{
  auto* pWidget = new QWidget;
  auto* pGrid = new QGridLayout(pWidget);
  int row = -1;


  auto* pBar = new QToolBar;
  pBar->addAction(newUndoAction(pBar));
  pBar->addAction(newRedoAction(pBar));
  pGrid->addWidget(pBar, ++row, 0);


  pGrid->addWidget(new QLabel("derivation value <=> number"), ++row, 0);
  pGrid->addWidget(new ViewDataNumber(pData, pWidget), row, 1);


  auto* pSpin  = new QSpinBox;
  auto getQt   = [pSpin]{ return pSpin->value(); };
  auto setQt   = [pSpin](int i){ pSpin->setValue(i); };
  auto getData = [pData]{ return pData->number(); };
  auto setData = [pData](int i){ doHistory(newSetCommand([pData](int j){ pData->setNumber(j); }, i, pData->number())); };
  addUpdate(pSpin, getQt, setQt, getData, setData);

  pGrid->addWidget(new QLabel("addUpdate value <=> number"), ++row, 0);
  pGrid->addWidget(pSpin, row, 1);


  auto* pSpin2 = new QSpinBox;
  auto spin2Value = make_tuple(pSpin2, [pSpin2]{ return pSpin2->value(); }, [pSpin2](int i){ pSpin2->setValue(i); });
  auto dataNumber = make_tuple(pData,  [pData ]{ return pData->number(); }, [pData ](int i){ pData->setNumber(i); });
  addUpdate(spin2Value, setViaCommand<int>(dataNumber));

  pGrid->addWidget(new QLabel("addUpdate value <=> number"), ++row, 0);
  pGrid->addWidget(pSpin2, row, 1);


  auto* pLabel = new QLabel;
  auto labelText  = make_tuple(pLabel, [pLabel]{ return pLabel->text().toStdString(); }, [pLabel](string s){ pLabel->setText(s.c_str()); });
  auto numberText = make_tuple(pData,  [pData ]{ return std::to_string(pData->number()); }, [](string){} );
  addUpdate(labelText, setViaCommand<string>(numberText));

  pGrid->addWidget(new QLabel("addUpdate text <=> number"), ++row, 0);
  pGrid->addWidget(pLabel, row, 1);


  auto* pCheckEnable = new QCheckBox;
  pCheckEnable->setText("Enable data");
  auto checked = make_tuple(pCheckEnable, [pCheckEnable]{ return pCheckEnable->isChecked(); }, [pCheckEnable](bool b){ pCheckEnable->setChecked(b); });
  auto dataEnabled = make_tuple(pData, [pData ]{ return pData->enabled(); }, [pData ](bool b){ pData->setEnabled(b); });
  addUpdate(checked, setViaCommand<bool>(dataEnabled));

  pGrid->addWidget(new QLabel("addUpdate checked <=> enable"), ++row, 0);
  pGrid->addWidget(pCheckEnable, row, 1);


  auto* pSpin3 = new QSpinBox;
  auto spin3Value = make_tuple(pSpin3, [pSpin3]{ return pSpin3->value(); }, [pSpin3](int i){ pSpin3->setValue(i); });
  //auto dataNumber = make_tuple(pData,  [pData ]{ return pData->number(); }, [pData ](int i){ pData->setNumber(i); });
  auto spin3Enable = make_tuple(pSpin3, [pSpin3]{ return pSpin3->isEnabled(); }, [pSpin3](bool b){ pSpin3->setEnabled(b); });
  //auto dataEnabled = make_tuple(pData, [pData ]{ return pData->enabled(); }, [pData ](bool b){ pData->setEnabled(b); });
  addUpdate(spin3Value, setViaCommand<int>(dataNumber));
  addUpdate(spin3Enable, setViaCommand<bool>(dataEnabled));

  pGrid->addWidget(new QLabel("addUpdate enable <=> enable, value <=> number"), ++row, 0);
  pGrid->addWidget(pSpin3, row, 1);


  pGrid->setRowStretch(++row, 1);

  return pWidget;
}



ViewDataNumber::ViewDataNumber(Data* data, QWidget* pParent) 
  : View(), 
  QSpinBox(pParent), 
  m_pData(data) 
{
  dataToView();
  connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ViewDataNumber::viewToData);
}

void ViewDataNumber::commandUpdate(const Command*) 
{
  dataToView();
}

void ViewDataNumber::viewToData() 
{ 
  if (History::singleton().updating()) return;

  auto setFct = [this](int i){ m_pData->setNumber(i); };
  doHistory(newSetCommand(setFct, value(), m_pData->number()));
}

void ViewDataNumber::dataToView() 
{ 
  setValue(m_pData->number());
}
