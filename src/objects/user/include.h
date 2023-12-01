#include "builtIn/include.h"     // first
#include "userObjects/include.h" // .

static Object *mainObject = new Object({}, {new VectorScript()});
#include "mainObject.cpp" // last
