#pragma once
#include "history.h"

class Command;


class View
{
public:
  View()          { History::singleton().add(this); }
  virtual ~View() { History::singleton().remove(this); }
  
  virtual void commandUpdate(const Command* pCommand) = 0;
};

