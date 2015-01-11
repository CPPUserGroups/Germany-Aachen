#pragma once
#include <functional>
#include <tuple>
#include <QObject>
#include "command.h"
#include "history.h"
#include "view.h"


template<class GetQt, class SetQt, class GetData, class SetData>
class Update : public QObject, public View
{
public:
    Update(QObject* pParent, GetQt getQt, SetQt setQt, GetData getData, SetData setData);

    bool eventFilter(QObject* pWatched, QEvent* pEvent) override;
    void commandUpdate(const Command* pCommand) override;

private: 
    GetQt m_getQt;
    SetQt m_setQt;
    GetData m_getData;
    SetData m_setData;
};

 
template<class ObjectT, class GetQt, class SetQt, class GetData, class SetData>
void addUpdate(ObjectT* pObject, GetQt getQt, SetQt setQt, GetData getData, SetData setData) 
{  
  new Update<GetQt, SetQt, GetData, SetData>(pObject, getQt, setQt, getData, setData);
}



//convenient overload: <pObject,get,set>-tuple for qt and <get,set>-tuple for data
template<class ObjectGetSet, class GetSetData>
void addUpdate(ObjectGetSet objectGetSet, GetSetData getSetData) 
{
  using namespace std;
	addUpdate(get<0>(objectGetSet), get<1>(objectGetSet), get<2>(objectGetSet), get<0>(getSetData), get<1>(getSetData));
}

//convenient creation of <get,set>-tuple for data from a <pData, get, set>-tuple 
template<class V, class DataT, class GetData, class SetData> 
auto setViaCommand(std::tuple<DataT, GetData, SetData> t) -> std::tuple<std::function<V(void)>, std::function<void(V)>> 
{
  using namespace std;
	auto doCommand = [t](V v){ doHistory(newSetCommand(get<2>(t), v, get<1>(t)() ));	};
	return make_tuple(get<1>(t), doCommand); 
}




//definition of Update member

template<class GetQt, class SetQt, class GetData, class SetData>
Update<GetQt, SetQt, GetData, SetData>::Update(QObject* pParent, GetQt getQt, SetQt setQt, GetData getData, SetData setData) 
  : QObject(pParent), 
  m_getQt(getQt), 
  m_setQt(setQt), 
  m_getData(getData), 
  m_setData(setData) 
{
  setQt(getData()); //init Qt value
  pParent->installEventFilter(this); //events for pParent are checked by Update first 
}

template<class GetQt, class SetQt, class GetData, class SetData>
bool Update<GetQt, SetQt, GetData, SetData>::eventFilter(QObject* pWatched, QEvent* pEvent) 
{
  if (pWatched == parent()) 
    if (m_getQt() != m_getData()) {
      m_setData(m_getQt());
      return true;
    } else return false;
  return QObject::eventFilter(pWatched, pEvent);
}

template<class GetQt, class SetQt, class GetData, class SetData>
void Update<GetQt, SetQt, GetData, SetData>::commandUpdate(const Command*) 
{
  if (m_getQt() != m_getData()) 
    m_setQt(m_getData());
}

