#include <algorithm>
#include "command.h"
#include "data.h"
#include "view.h"
#include "history.h"

using namespace std;


History& History::singleton() 
{ 
  static History history;
  return history;
}

History::History() 
  : m_updating(false) 
{}

bool History::updating() const 
{
  return m_updating;
}

void History::doit(Command* pCommand)
{
  if (m_updating) return; //or assert

  Log::log("Do: " + pCommand->text());

  m_undos.push_back(pCommand);
  m_redos.clear();
  pCommand->doit();
  update(pCommand);
}

void History::undo()
{
  if (m_undos.empty()) return;
  
  auto* pCommand = m_undos.back();
  Log::log("Undo: " + pCommand->text());
  m_redos.push_back(pCommand);
  m_undos.pop_back();
  pCommand->doit();	
  update(pCommand);
}

void History::redo()
{
  if (m_redos.empty()) return;

  auto* pCommand = m_redos.back();
  Log::log("Redo: " + pCommand->text());

  m_undos.push_back(pCommand);
  m_redos.pop_back();
  pCommand->doit();	
  update(pCommand);
}

void History::add(View* pView)
{
  m_views.push_back(pView);
}

void History::remove(View* pView)
{
  m_views.erase(std::remove(begin(m_views), end(m_views), pView), end(m_views)); 
}

void History::update(Command* pCommand)
{
  if (m_updating) return;

  Updating dummy;
  for (auto* pView : m_views) 
    pView->commandUpdate(pCommand);
}

History::Updating::Updating()  
{ 
  singleton().m_updating = true; 
}

History::Updating::~Updating() 
{ 
  singleton().m_updating = false;
}



void doHistory(Command* pCommand)
{
  History::singleton().doit(pCommand);
}
