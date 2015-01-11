#pragma once
#include <QSpinBox>
#include "view.h"

class QAction;
class QWidget;
class Command;
class Data;


QAction* newUndoAction(QWidget* pParent); 
QAction* newRedoAction(QWidget* pParent);
QWidget* newUpdateExamples(Data* pData);


class ViewDataNumber : public QSpinBox, public View
{
public: 
  ViewDataNumber(Data* data, QWidget* pParent); 

  void commandUpdate(const Command*) override;

private:
  void viewToData(); 
  void dataToView(); 

  Data* m_pData;
};
