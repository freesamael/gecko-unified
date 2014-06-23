/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "builtin/SymbolObject.h"

#include "vm/StringBuffer.h"

#include "jsobjinlines.h"

#include "vm/Symbol-inl.h"

using JS::Symbol;
using namespace js;

const Class SymbolObject::class_ = {
    "Symbol",
    JSCLASS_HAS_RESERVED_SLOTS(RESERVED_SLOTS) | JSCLASS_HAS_CACHED_PROTO(JSProto_Symbol),
    JS_PropertyStub,         /* addProperty */
    JS_DeletePropertyStub,   /* delProperty */
    JS_PropertyStub,         /* getProperty */
    JS_StrictPropertyStub,   /* setProperty */
    JS_EnumerateStub,
    JS_ResolveStub,
    convert
};

SymbolObject *
SymbolObject::create(JSContext *cx, JS::Symbol *symbol)
{
    JSObject *obj = NewBuiltinClassInstance(cx, &class_);
    if (!obj)
        return nullptr;
    SymbolObject &symobj = obj->as<SymbolObject>();
    symobj.setPrimitiveValue(symbol);
    return &symobj;
}

const JSPropertySpec SymbolObject::properties[] = {
    JS_PS_END
};

const JSFunctionSpec SymbolObject::methods[] = {
    JS_FN(js_toString_str, toString, 0, 0),
    JS_FN(js_valueOf_str, valueOf, 0, 0),
    JS_FS_END
};

const JSFunctionSpec SymbolObject::staticMethods[] = {
    JS_FN("for", for_, 1, 0),
    JS_FS_END
};

JSObject *
SymbolObject::initClass(JSContext *cx, HandleObject obj)
{
    Rooted<GlobalObject*> global(cx, &obj->as<GlobalObject>());

    // This uses &JSObject::class_ because: "The Symbol prototype object is an
    // ordinary object. It is not a Symbol instance and does not have a
    // [[SymbolData]] internal slot." (ES6 rev 24, 19.4.3)
    RootedObject proto(cx, global->createBlankPrototype(cx, &JSObject::class_));
    if (!proto)
        return nullptr;

    RootedFunction ctor(cx, global->createConstructor(cx, construct,
                                                      ClassName(JSProto_Symbol, cx), 1));
    if (!ctor)
        return nullptr;

    // Define the well-known symbol properties, such as Symbol.iterator.
    ImmutablePropertyNamePtr *names = &cx->names().iterator;
    RootedValue value(cx);
    unsigned attrs = JSPROP_READONLY | JSPROP_PERMANENT;
    WellKnownSymbols *wks = cx->runtime()->wellKnownSymbols;
    for (size_t i = 0; i < JS::WellKnownSymbolLimit; i++) {
        value.setSymbol(wks->get(i));
        if (!DefineNativeProperty(cx, ctor, names[i], value, nullptr, nullptr, attrs))
            return nullptr;
    }

    if (!LinkConstructorAndPrototype(cx, ctor, proto) ||
        !DefinePropertiesAndFunctions(cx, proto, properties, methods) ||
        !DefinePropertiesAndFunctions(cx, ctor, nullptr, staticMethods) ||
        !GlobalObject::initBuiltinConstructor(cx, global, JSProto_Symbol, ctor, proto))
    {
        return nullptr;
    }
    return proto;
}

// ES6 rev 24 (2014 Apr 27) 19.4.1.1 and 19.4.1.2
bool
SymbolObject::construct(JSContext *cx, unsigned argc, Value *vp)
{
    // According to a note in the draft standard, "Symbol has ordinary
    // [[Construct]] behaviour but the definition of its @@create method causes
    // `new Symbol` to throw a TypeError exception." We do not support @@create
    // yet, so just throw a TypeError.
    CallArgs args = CallArgsFromVp(argc, vp);
    if (args.isConstructing()) {
        JS_ReportErrorNumber(cx, js_GetErrorMessage, nullptr, JSMSG_NOT_CONSTRUCTOR, "Symbol");
        return false;
    }

    // steps 1-3
    RootedString desc(cx);
    if (!args.get(0).isUndefined()) {
        desc = ToString(cx, args.get(0));
        if (!desc)
            return false;
    }

    // step 4
    RootedSymbol symbol(cx, JS::Symbol::new_(cx, JS::SymbolCode::UniqueSymbol, desc));
    if (!symbol)
        return false;
    args.rval().setSymbol(symbol);
    return true;
}

// Stand-in for Symbol.prototype[@@toPrimitive], ES6 rev 25 (2014 May 22) 19.4.3.4
bool
SymbolObject::convert(JSContext *cx, HandleObject obj, JSType type, MutableHandleValue vp)
{
    JS_ReportErrorNumber(cx, js_GetErrorMessage, nullptr, JSMSG_SYMBOL_TO_PRIMITIVE);
    return false;
}

// ES6 rev 24 (2014 Apr 27) 19.4.2.2
bool
SymbolObject::for_(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);

    // steps 1-2
    RootedString stringKey(cx, ToString(cx, args.get(0)));
    if (!stringKey)
        return false;

    // steps 3-7
    JS::Symbol *symbol = JS::Symbol::for_(cx, stringKey);
    if (!symbol)
        return false;
    args.rval().setSymbol(symbol);
    return true;
}

MOZ_ALWAYS_INLINE bool
IsSymbol(HandleValue v)
{
    return v.isSymbol() || (v.isObject() && v.toObject().is<SymbolObject>());
}

//ES6 rev 24 (2014 Apr 27) 19.4.3.2
bool
SymbolObject::toString_impl(JSContext *cx, CallArgs args)
{
    // steps 1-3
    HandleValue thisv = args.thisv();
    JS_ASSERT(IsSymbol(thisv));
    Rooted<Symbol*> sym(cx, thisv.isSymbol()
                            ? thisv.toSymbol()
                            : thisv.toObject().as<SymbolObject>().unbox());

    // steps 4-7
    StringBuffer sb(cx);
    if (!sb.append("Symbol("))
        return false;
    RootedString str(cx, sym->description());
    if (str) {
        if (!sb.append(str))
            return false;
    }
    if (!sb.append(')'))
        return false;

    // step 8
    str = sb.finishString();
    if (!str)
        return false;
    args.rval().setString(str);
    return true;
}

bool
SymbolObject::toString(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    return CallNonGenericMethod<IsSymbol, toString_impl>(cx, args);
}

//ES6 rev 24 (2014 Apr 27) 19.4.3.3
bool
SymbolObject::valueOf_impl(JSContext *cx, CallArgs args)
{
    // Step 3, the error case, is handled by CallNonGenericMethod.
    HandleValue thisv = args.thisv();
    MOZ_ASSERT(IsSymbol(thisv));
    if (thisv.isSymbol())
        args.rval().set(thisv);
    else
        args.rval().setSymbol(thisv.toObject().as<SymbolObject>().unbox());
    return true;
}

bool
SymbolObject::valueOf(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    return CallNonGenericMethod<IsSymbol, valueOf_impl>(cx, args);
}

JSObject *
js_InitSymbolClass(JSContext *cx, HandleObject obj)
{
    return SymbolObject::initClass(cx, obj);
}
