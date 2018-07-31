// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubPythonEntityScript_custom.h file.

#ifndef STUB_RULESETS_PYTHONENTITYSCRIPT_H
#define STUB_RULESETS_PYTHONENTITYSCRIPT_H

#include "rulesets/PythonEntityScript.h"
#include "stubPythonEntityScript_custom.h"

#ifndef STUB_PythonEntityScript_PythonEntityScript
//#define STUB_PythonEntityScript_PythonEntityScript
   PythonEntityScript::PythonEntityScript(const Py::Object& obj)
    : PythonWrapper(obj)
  {
    
  }
#endif //STUB_PythonEntityScript_PythonEntityScript

#ifndef STUB_PythonEntityScript_operation
//#define STUB_PythonEntityScript_operation
  HandlerResult PythonEntityScript::operation(const std::string & opname, const Atlas::Objects::Operation::RootOperation & op, OpVector & res)
  {
    return *static_cast<HandlerResult*>(nullptr);
  }
#endif //STUB_PythonEntityScript_operation

#ifndef STUB_PythonEntityScript_hook
//#define STUB_PythonEntityScript_hook
  void PythonEntityScript::hook(const std::string & function, LocatedEntity * entity)
  {
    
  }
#endif //STUB_PythonEntityScript_hook

#ifndef STUB_PythonEntityScript_processScriptResult
//#define STUB_PythonEntityScript_processScriptResult
   HandlerResult PythonEntityScript::processScriptResult(const std::string& scriptName, const Py::Object& ret, OpVector& res)
  {
    return *static_cast< HandlerResult*>(nullptr);
  }
#endif //STUB_PythonEntityScript_processScriptResult


#endif