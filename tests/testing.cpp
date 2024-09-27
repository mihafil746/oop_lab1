#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include <algorithm>
#include <iterator>
#include "../lib/xml.h"

using namespace lab1;

TEST_CASE("array_to_xml") {
    SECTION("const_char*") {
        const char* cc = "<a><b>1</b></a>";
        const char* n = "a";
        const char* t = "b";
        int v1[1] = {1};
        REQUIRE(array2xml(n, t, v1, 1) == cc);
        cc = "<a><b>1</b><b>2</b><b>3</b></a>";
        int v3[3] = {1, 2, 3};
        REQUIRE(array2xml(n, t, v3, 3) == cc);
        REQUIRE_THROWS(array2xml(nullptr, t, v3, 3));
        REQUIRE_THROWS(array2xml(n, nullptr, v3, 3));
        REQUIRE_THROWS(array2xml(n, t, nullptr, 3));
    }
    SECTION("const_char*+size_t") {
        const char* cc = "<a><b>1</b></a>";
        const char* n = "a";
        const char* t = "b";
        int v1[1] = {1};
        size_t s = 0;
        REQUIRE(array2xml(n, t, v1, 1, s) == cc);
        cc = "<a><b>1</b><b>2</b><b>3</b></a>";
        int v3[3] = {1, 2, 3};
        REQUIRE(array2xml(n, t, v3, 3, s) == cc);
        REQUIRE_THROWS(array2xml(nullptr, t, v3, 3, s));
        REQUIRE_THROWS(array2xml(n, nullptr, v3, 3, s));
        REQUIRE_THROWS(array2xml(n, t, nullptr, 3, s));
    }
    SECTION("std::string") {
        std::string ss = "<a><b>1</b></a>";
        std::string n = "a";
        std::string t = "b";
        int v1[1] = {1};
        REQUIRE(array2xml(n, t, v1, 1) == ss);
        ss = "<a><b>1</b><b>2</b><b>3</b></a>";
        int v3[3] = {1, 2, 3};
        REQUIRE(array2xml(n, t, v3, 3) == ss);
        REQUIRE_THROWS(array2xml(nullptr, t, v3, 3));
        REQUIRE_THROWS(array2xml(n, nullptr, v3, 3));
        REQUIRE_THROWS(array2xml(n, t, nullptr, 3));
    }
}

TEST_CASE("xml_to_array") {
    SECTION("const_char*") {
        const char* x = "<a><b>1</b><b>2</b><b>3</b></a>";
        std::string n = "", t = "";
        size_t s = 0;
        int v3[3] = {1, 2, 3};
        int* v = xml2array(x, n, t, s);
        bool equal = true;
        for (int i = 0; i < 3; i++) {
            if (v3[i] != v[i])
                equal = false;
        }
        REQUIRE(equal == true);
        const char* y = "<a><b>test</b></a>";
        REQUIRE_THROWS(xml2array(y, n, t, s));
        REQUIRE_THROWS(xml2array(nullptr, n, t, s));
    }
    SECTION("const_char*+size_t") {
        const char* x = "<a><b>1</b><b>2</b><b>3</b></a>";
        std::string n = "", t = "";
        size_t s = 0;
        int v3[3] = {1, 2, 3};
        int* v = xml2array(x, 31, n, t, s);
        bool equal = true;
        for (int i = 0; i < 3; i++) {
            if (v3[i] != v[i])
                equal = false;
        }
        REQUIRE(equal == true);
        const char* y = "<a><b>test</b></a>";
        REQUIRE_THROWS(xml2array(y, 18, n, t, s));
        REQUIRE_THROWS(xml2array(nullptr, 0, n, t, s));
    }
    SECTION("std::string") {
        std::string x = "<a><b>1</b><b>2</b><b>3</b></a>";
        std::string n = "", t = "";
        size_t s = 0;
        int v3[3] = {1, 2, 3};
        int* v = xml2array(x, n, t, s);
        bool equal = true;
        for (int i = 0; i < 3; i++) {
            if (v3[i] != v[i])
                equal = false;
        }
        REQUIRE(equal == true);
        x = "<a><b>test</b></a>";
        REQUIRE_THROWS(xml2array(x, n, t, s));
        std::string y;
        REQUIRE_THROWS(xml2array(y, n, t, s));
    }
}

