#pragma once
#include <sstream>
#include <string>


class Command
{
public:
  virtual ~Command() {}

  const std::string& text() const        { return m_sText; }
  void setText(const std::string& sText) { m_sText = sText; }

  virtual void doit() = 0;

private:
  std::string m_sText;
};



template<class SetFct, class Value>
class SetCommand : public Command
{
public:
  SetCommand(SetFct setFct, Value doValue, Value undoValue); 

  void doit() override; 

private:
  SetFct m_setFct;
  Value m_doValue;
  Value m_undoValue;
  int m_count;
};


template<class SetFct, class Value>
Command* newSetCommand(SetFct setFct, Value doValue, Value undoValue) 
{
  return new SetCommand<SetFct, Value>(setFct, doValue, undoValue);
}




//definition of SetCommand member

template<class SetFct, class Value> 
SetCommand<SetFct, Value>::SetCommand(SetFct setFct, Value doValue, Value undoValue) 
  : m_setFct(setFct), 
  m_doValue(doValue), 
  m_undoValue(undoValue),
  m_count(0)
{ 
  std::stringstream ss;
  ss << "Value from " << undoValue << " to " << doValue;
  setText(ss.str());
}

template<class SetFct, class Value> 
void SetCommand<SetFct, Value>::doit() 
{
  m_setFct( ++m_count % 2 ? m_doValue : m_undoValue );
}

