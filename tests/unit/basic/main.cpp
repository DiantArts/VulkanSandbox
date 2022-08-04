#include <pch.hpp>
#include <catch2/catch.hpp>
#include <factorial.hpp>

TEST_CASE("test name", "[test suite]")
{
    REQUIRE(::ctsb::factorial(5) == 120);
}

TEST_CASE("test name 2", "[test suite]")
{
    REQUIRE(::ctsb::factorial(20) == 2432902008176640000);
}

TEST_CASE("test name 3", "[test suite]")
{
    // REQUIRE(::ctsb::factorial(0) == 1);
    REQUIRE(::ctsb::factorial(0) == 1);
    REQUIRE(::ctsb::factorial(1) == 1);
    REQUIRE(::ctsb::factorial(2) == 2);
    REQUIRE(::ctsb::factorial(3) == 6);
    REQUIRE(::ctsb::factorial(4) == 24);
    REQUIRE(::ctsb::factorial(5) == 120);
    REQUIRE(::ctsb::factorial(6) == 720);
    REQUIRE(::ctsb::factorial(7) == 5040);
    REQUIRE(::ctsb::factorial(8) == 40320);
    REQUIRE(::ctsb::factorial(9) == 362880);
    REQUIRE(::ctsb::factorial(10) == 3628800);
    REQUIRE(::ctsb::factorial(11) == 39916800);
    REQUIRE(::ctsb::factorial(12) == 479001600);
    REQUIRE(::ctsb::factorial(13) == 6227020800);
    REQUIRE(::ctsb::factorial(14) == 87178291200);
    REQUIRE(::ctsb::factorial(15) == 1307674368000);
    REQUIRE(::ctsb::factorial(16) == 20922789888000);
    REQUIRE(::ctsb::factorial(17) == 355687428096000);
    REQUIRE(::ctsb::factorial(18) == 6402373705728000);
    REQUIRE(::ctsb::factorial(19) == 121645100408832000);
}
