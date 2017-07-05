// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubPropertyManager_custom.h file.

#include "common/PropertyManager.h"
#include "stubPropertyManager_custom.h"

#ifndef STUB_COMMON_PROPERTYMANAGER_H
#define STUB_COMMON_PROPERTYMANAGER_H

#ifndef STUB_PropertyManager_PropertyManager
//#define STUB_PropertyManager_PropertyManager
   PropertyManager::PropertyManager()
  {
    
  }
#endif //STUB_PropertyManager_PropertyManager

#ifndef STUB_PropertyManager_installFactory
//#define STUB_PropertyManager_installFactory
  void PropertyManager::installFactory(const std::string &, PropertyKit *)
  {
    
  }
#endif //STUB_PropertyManager_installFactory

#ifndef STUB_PropertyManager_PropertyManager_DTOR
//#define STUB_PropertyManager_PropertyManager_DTOR
   PropertyManager::~PropertyManager()
  {
    
  }
#endif //STUB_PropertyManager_PropertyManager_DTOR

#ifndef STUB_PropertyManager_addProperty
//#define STUB_PropertyManager_addProperty
  PropertyBase* PropertyManager::addProperty(const std::string & name, int type)
  {
    return nullptr;
  }
#endif //STUB_PropertyManager_addProperty

#ifndef STUB_PropertyManager_installFactory
//#define STUB_PropertyManager_installFactory
  int PropertyManager::installFactory(const std::string & type_name, const Atlas::Objects::Root & type_desc, PropertyKit * factory)
  {
    return 0;
  }
#endif //STUB_PropertyManager_installFactory

#ifndef STUB_PropertyManager_getPropertyFactory
//#define STUB_PropertyManager_getPropertyFactory
  PropertyKit* PropertyManager::getPropertyFactory(const std::string &) const
  {
    return nullptr;
  }
#endif //STUB_PropertyManager_getPropertyFactory


#endif