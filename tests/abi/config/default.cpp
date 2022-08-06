#include "doctest_compatibility.h"

#include "config.hpp"

#include <nlohmann/json_fwd.hpp>

TEST_CASE("default namespace")
{
    // GCC 4.8 fails with regex_error
#if !DOCTEST_GCC || DOCTEST_GCC >= DOCTEST_COMPILER(4, 9, 0)
    SECTION("namespace matches expectation")
    {
        std::string expected = "nlohmann::json_abi";

#if JSON_DIAGNOSTICS
        expected += "_diag";
#endif

#if JSON_USE_LEGACY_DISCARDED_VALUE_COMPARISON
        expected += "_ldvcmp";
#endif

        expected += "_v" STRINGIZE(NLOHMANN_JSON_VERSION_MAJOR);
        expected += "_" STRINGIZE(NLOHMANN_JSON_VERSION_MINOR);
        expected += "_" STRINGIZE(NLOHMANN_JSON_VERSION_PATCH) "::basic_json";

        // fallback for Clang
        std::string ns{STRINGIZE(NLOHMANN_JSON_NAMESPACE) "::basic_json"};

        CHECK(namespace_name<nlohmann::json>(ns) == expected);
    }
#endif
}
