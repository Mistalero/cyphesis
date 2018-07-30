/*
 Copyright (C) 2018 Erik Ogenvik

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef CYPHESIS_CYPY_LOCATEDENTITY_IMPL_H
#define CYPHESIS_CYPY_LOCATEDENTITY_IMPL_H

#include "CyPy_LocatedEntity.h"
#include "CyPy_Point3D.h"

template<typename TValue, typename TPythonClass>
CyPy_LocatedEntityBase<TValue, TPythonClass>::CyPy_LocatedEntityBase(Py::PythonClassInstance* self, Py::Tuple& args, Py::Dict& kwds)
    : WrapperBase<TValue, TPythonClass>::WrapperBase(self, args, kwds)
{
}

template<typename TValue, typename TPythonClass>
CyPy_LocatedEntityBase<TValue, TPythonClass>::CyPy_LocatedEntityBase(Py::PythonClassInstance* self, TValue value)
    : WrapperBase<TValue, TPythonClass>::WrapperBase(self, std::move(value))
{
}


template<typename TValue, typename TPythonClass>
CyPy_LocatedEntityBase<TValue, TPythonClass>::~CyPy_LocatedEntityBase()
{
}


template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::getattro(const Py::String& name)
{
    auto nameStr = name.as_string();
    if (nameStr == "id") {
        return Py::String(this->m_value->getId());
    }

    if (nameStr == "props") {
        return CyPy_Props::wrap(this->m_value);
    }

    if (nameStr == "type") {
        if (!this->m_value->getType()) {
            throw Py::AttributeError(name);
        }
        return Py::String(this->m_value->getType()->name());
    }


    if (nameStr == "location") {
        return CyPy_Location::wrap(this->m_value->m_location);
    }

    if (nameStr == "contains") {
        if (!this->m_value->m_contains) {
            return Py::None();
        }

        Py::List list;
        for (auto& child : *this->m_value->m_contains) {
            list.append(CyPy_LocatedEntity::wrap(child));
        }
        return list;
    }

    if (nameStr == "visible") {
        return Py::Boolean(this->m_value->isVisible());
    }

    return Py::PythonExtensionBase::getattro(name);
}

template<typename TValue, typename TPythonClass>
int CyPy_LocatedEntityBase<TValue, TPythonClass>::setattro(const Py::String& name, const Py::Object& attr)
{
    auto nameStr = name.as_string();

    //FIXME: perhaps in BaseMind instead?
    if (nameStr == "map") {
        throw Py::AttributeError("map attribute forbidden");
    }
    if (nameStr == "type") {
        if (this->m_value->getType()) {
            throw Py::RuntimeError("Cannot mutate entity type");
        }

        const TypeNode* type = Inheritance::instance().getType(verifyString(attr));
        if (!type) {
            throw Py::ValueError("Entity type unknown");
        }
        this->m_value->setType(type);
        return 0;
    }
    return Py::PythonExtensionBase::setattro(name, attr);
}

template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::rich_compare(const Py::Object& other, int op)
{

    if (CyPy_LocatedEntity::check(other)) {
        auto otherPtr = &CyPy_LocatedEntity::value(other);
        if (this->m_value == nullptr || otherPtr == nullptr) {
            return Py::False();
        }
        if (op == Py_EQ) {
            return (this->m_value == otherPtr) ? Py::True() : Py::False();
        } else if (op == Py_NE) {
            return (this->m_value != otherPtr) ? Py::True() : Py::False();
        }

    } else {
        if (op == Py_EQ) {
            return Py::False();
        } else if (op == Py_NE) {
            return Py::True();
        }
    }

    throw Py::NotImplementedError("Not implemented");

}

template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::as_entity()
{
    Atlas::Message::MapType element;
    this->m_value->addToMessage(element);
    return CyPy_Element::wrap(element);
}

template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::is_reachable_for_other_entity(const Py::Tuple& args)
{

    args.verify_length(1, 3);
    if (!CyPy_LocatedEntity::check(args.front())) {
        throw Py::TypeError("Target must be a located entity");
    }
    WFMath::Point<3> pos;
    float extraReach = 0;
    if (args.length() > 1) {
        pos = CyPy_Point3D::parse(args[1]);
    }
    if (args.length() > 2) {
        extraReach = verifyNumeric(args[2]);
    }

    auto& reacher = verifyObject<CyPy_LocatedEntity>(args.front());
    return Py::Boolean(this->m_value->isReachableForOtherEntity(&reacher, pos, extraReach));
}

template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::describe_entity()
{
    return Py::String(this->m_value->describeEntity());
}

template<typename TValue, typename TPythonClass>
Py::Object CyPy_LocatedEntityBase<TValue, TPythonClass>::wrap(LocatedEntity* value)
{
    return wrapLocatedEntity(value);
}

#endif //CYPHESIS_CYPY_LOCATEDENTITY_IMPL_H