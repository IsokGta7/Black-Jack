// Builds doctest's runner and main() once for the whole test binary.
// doctest.h is vendored from https://github.com/doctest/doctest (v2.4.12, MIT,
// see doctest-LICENSE.txt).
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
