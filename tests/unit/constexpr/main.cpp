#include <catch2/catch.hpp>
#include <factorial.hpp>

TEST_CASE("constexpr test name", "[constexpr test suite]")
{
    REQUIRE(::ctsb::factorial(5) == ::ctsb::constevalFactorial<5>());
    REQUIRE(::ctsb::factorial(20) == ::ctsb::constevalFactorial<20>());
}
