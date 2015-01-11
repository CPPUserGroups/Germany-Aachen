#pragma once
#include <string>


class Data
{
public:
  Data() : m_i(42), m_b(true) {}

  void setNumber(int i)   { m_i = i; }
  int number() const      { return m_i; }

  void setEnabled(bool b) { m_b = b; }
  bool enabled() const    { return m_b; }

private:
  int m_i;
  bool m_b;
};


class Log
{
public:
  static Log& singleton()               { static Log l; return l; }
  static void log(const std::string& s) { singleton().m_s += s + "\n"; }

  const std::string& text() const       { return m_s; }

private:
  Log() {}
  std::string m_s;
};
