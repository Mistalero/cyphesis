// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubUsagesProperty_custom.h file.

#ifndef STUB_RULESETS_USAGESPROPERTY_H
#define STUB_RULESETS_USAGESPROPERTY_H

#include "rulesets/UsagesProperty.h"
#include "stubUsagesProperty_custom.h"

#ifndef STUB_UsagesProperty_set
//#define STUB_UsagesProperty_set
  void UsagesProperty::set(const Atlas::Message::Element& val)
  {
    
  }
#endif //STUB_UsagesProperty_set

#ifndef STUB_UsagesProperty_install
//#define STUB_UsagesProperty_install
  void UsagesProperty::install(LocatedEntity* owner, const std::string& name)
  {
    
  }
#endif //STUB_UsagesProperty_install

#ifndef STUB_UsagesProperty_remove
//#define STUB_UsagesProperty_remove
  void UsagesProperty::remove(LocatedEntity* owner, const std::string& name)
  {
    
  }
#endif //STUB_UsagesProperty_remove

#ifndef STUB_UsagesProperty_operation
//#define STUB_UsagesProperty_operation
  HandlerResult UsagesProperty::operation(LocatedEntity* e, const Operation& op, OpVector& res)
  {
    return *static_cast<HandlerResult*>(nullptr);
  }
#endif //STUB_UsagesProperty_operation

#ifndef STUB_UsagesProperty_use_handler
//#define STUB_UsagesProperty_use_handler
  HandlerResult UsagesProperty::use_handler(LocatedEntity* e, const Operation& op, OpVector& res)
  {
    return *static_cast<HandlerResult*>(nullptr);
  }
#endif //STUB_UsagesProperty_use_handler

#ifndef STUB_UsagesProperty_processScriptResult
//#define STUB_UsagesProperty_processScriptResult
  HandlerResult UsagesProperty::processScriptResult(const std::string& scriptName, const Py::Object& ret, OpVector& res, LocatedEntity* e)
  {
    return *static_cast<HandlerResult*>(nullptr);
  }
#endif //STUB_UsagesProperty_processScriptResult


#endif