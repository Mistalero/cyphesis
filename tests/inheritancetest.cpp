// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include "common/inheritance.h"

#include <Atlas/Objects/Root.h>

#include <cassert>

using Atlas::Objects::Root;

void descendTree(Root * type, Inheritance & i, int & count)
{
    assert(type != 0);
    ++count;
    if (!type->hasAttr("children")) {
        return;
    }

    Element childrenobj = type->getAttr("children");
    assert(childrenobj.isList());
    ListType & children = childrenobj.asList();

    ListType::const_iterator I = children.begin();
    for(; I != children.end(); ++I) {
        const Element & e = *I;
        assert(e.isString());
        const std::string & es = e.asString();
        assert(!es.empty());
        Root * child = i.get(es);
        descendTree(child, i, count);
    }

}

int main()
{
    Inheritance & i = Inheritance::instance();

    assert(i.opEnumerate("login") == OP_LOGIN);
    assert(i.opEnumerate("logout") == OP_LOGOUT);
    assert(i.opEnumerate("action") == OP_ACTION);
    assert(i.opEnumerate("chop") == OP_CHOP);
    assert(i.opEnumerate("combine") == OP_COMBINE);
    assert(i.opEnumerate("create") == OP_CREATE);
    assert(i.opEnumerate("cut") == OP_CUT);
    assert(i.opEnumerate("delete") == OP_DELETE);
    assert(i.opEnumerate("divide") == OP_DIVIDE);
    assert(i.opEnumerate("eat") == OP_EAT);
    assert(i.opEnumerate("burn") == OP_BURN);
    assert(i.opEnumerate("get") == OP_GET);
    assert(i.opEnumerate("imaginary") == OP_IMAGINARY);
    assert(i.opEnumerate("info") == OP_INFO);
    assert(i.opEnumerate("move") == OP_MOVE);
    assert(i.opEnumerate("nourish") == OP_NOURISH);
    assert(i.opEnumerate("set") == OP_SET);
    assert(i.opEnumerate("sight") == OP_SIGHT);
    assert(i.opEnumerate("sound") == OP_SOUND);
    assert(i.opEnumerate("talk") == OP_TALK);
    assert(i.opEnumerate("touch") == OP_TOUCH);
    assert(i.opEnumerate("tick") == OP_TICK);
    assert(i.opEnumerate("look") == OP_LOOK);
    assert(i.opEnumerate("setup") == OP_SETUP);
    assert(i.opEnumerate("appearance") == OP_APPEARANCE);
    assert(i.opEnumerate("disappearance") == OP_DISAPPEARANCE);
    assert(i.opEnumerate("error") == OP_ERROR);
    assert(i.opEnumerate("squigglymuff") == OP_INVALID);

    Root * rt = i.get("root");

    // Make sure the type tree is coherent, and contains a decent
    // number of types.
    int count = 0;
    descendTree(rt, i, count);
    assert(count > 20);

    // Make sure inserting a type with unknown parents fails with
    // an exception.
    bool thrown = false;
    Root r;
    r.setId("squigglymuff");
    r.setParents(ListType(1, "ludricous_test_parent"));
    try {
       i.addChild(&r);
    }
    catch (InheritanceException ie) {
        thrown = true;
    }
    assert(thrown == true);
}
