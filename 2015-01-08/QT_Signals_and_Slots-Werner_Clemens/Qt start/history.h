#pragma once
#include <vector>

class Command;
class View;


class History
{
public:
  static History& singleton();

  bool updating() const;
  void doit(Command* pCommand);
  void undo();
  void redo();
  void add(View* pView);
  void remove(View* pView);

private:
  History();

  void update(Command* pCommand);

  std::vector<Command*> m_undos;
  std::vector<Command*> m_redos;
  std::vector<View*>    m_views;
  bool m_updating;

  struct Updating 
  {
    Updating();  
    ~Updating(); 
  };
};


//convenience call
void doHistory(Command* pCommand);
