// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubMindFactory_custom.h file.

#ifndef STUB_RULES_AI_MINDFACTORY_H
#define STUB_RULES_AI_MINDFACTORY_H

#include "rules/ai/MindFactory.h"
#include "stubMindFactory_custom.h"

#ifndef STUB_MindKit_MindKit
//#define STUB_MindKit_MindKit
   MindKit::MindKit()
    : m_scriptFactory(nullptr)
  {
    
  }
#endif //STUB_MindKit_MindKit

#ifndef STUB_MindKit_MindKit_DTOR
//#define STUB_MindKit_MindKit_DTOR
   MindKit::~MindKit()
  {
    
  }
#endif //STUB_MindKit_MindKit_DTOR

#ifndef STUB_MindKit_newMind
//#define STUB_MindKit_newMind
  BaseMind* MindKit::newMind(const std::string & mind_id, const std::string & entity_id) const
  {
    return nullptr;
  }
#endif //STUB_MindKit_newMind


#endif