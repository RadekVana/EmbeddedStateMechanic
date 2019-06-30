#ifndef _MY_EVENT_HANDLER_
#define _MY_EVENT_HANDLER_

#include <map>
#include <vector>
#include <algorithm>
//na konci inkluduju MyEventHandler_T.c
//to muze obsahovat pouze definice sablon

/******************************************************************************/
//event
template <class T>
class event{
  public:
    virtual void operator()(T)=0;
};
/******************************************************************************/
//_event_handler
//abstraktni, muze mit ulozenej jinej typ T nez je typ eventy TE
template <class T, class TE>
class _event_handler{
  //pristupovat prez metody
  T                     elem;  
protected:
  vector<event<TE>*>     events; 

  virtual void send_events(T val) = 0;
public:
  _event_handler();
  void set_elem(T el);
  T get_elem();
  const T get_elem() const;
  void registet_event(event<TE>& f);
};

//event_handler
//typ a typ eventy jsou stejne
template <class T>
class event_handler:public _event_handler<T,T> {
protected:  
  virtual void send_events(T val);
};

/******************************************************************************/
//univerzalni updater pro non static mem fce
//pozor musi byt znamo pri prekladu, mozna bude muset bejt trida static
// TC je trida
// T je typ napr. int
// mmemfce je member fci tridy typu TC co bere param T
template <class T, class TC, void (TC::*memfce)(T)>
class updater: public event<T>{
  TC& parent;
public:
  updater(TC& x): parent(x) {}
  virtual void operator()(T x){(parent.*memfce)(x);}
};  

/******************************************************************************/
//univerzalni updater pro fce nebo static mem fce 
// T je typ napr. int
// mmemfce je member fci tridy typu TC co bere param T
template <class T, void (*fce)(T)>
class s_updater: public event<T>{
public:
  virtual void operator()(T x){fce(x);}
};  

/******************************************************************************/
//_event_handler
template <class T, class TE>
_event_handler<T,TE>::_event_handler():
  //elem(T(NULL)){}
  elem(T()){}
 
  
template <class T, class TE>
void _event_handler<T,TE>::set_elem(T el){
  Mutex m;
  elem = el;
  send_events(el);
}

template <class T, class TE>
T _event_handler<T,TE>::get_elem(){
  return elem;
}

template <class T, class TE>
const T _event_handler<T,TE>::get_elem() const{
  return elem;
}

//1 handler cannot be registered twice
template <class T, class TE>
void _event_handler<T,TE>::registet_event(event<TE>& f){
  if (events.empty()){
    events.push_back(&f);
  }else{
    if (find(events.begin(), events.end(), &f) == events.end() ) events.push_back(&f);
  }
}



template <class T>
void event_handler<T>::send_events(T val){
  //the compiler can't inspect vector<event<T>*> (it doesn't have its definition 
  //at this point) and so it doesn't know whether vector<event<T>*>::iterator is 
  //either a static field or a type.
  //In such a situation, the compiler assumes that it is a field, so it yields 
  //a syntax error. To solve the issue, just tell the compiler 
  //that it is a type by putting a typename ahead of the declaration:
  typename vector<event<T>*>::iterator it;
  for (it = _event_handler<T,T>::events.begin(); it != _event_handler<T,T>::events.end();it++){
    (**it)(val);//mam ukazatel na funktor - dereferencuju 2x
  }
  
}
#endif