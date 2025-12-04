#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mini_catch {
struct TestCase {
    std::string name;
    std::function<void()> func;
};

inline std::vector<TestCase> &registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(const std::string &name, std::function<void()> func) {
        registry().push_back({name, std::move(func)});
    }
};

struct AssertionFailure : public std::runtime_error {
    explicit AssertionFailure(const std::string &message) : std::runtime_error(message) {}
};

inline void report_failure(const std::string &expr, const char *file, int line) {
    std::cerr << file << ":" << line << " CHECK failed: " << expr << std::endl;
}

inline int run_all() {
    int failed = 0;
    for (const auto &test : registry()) {
        try {
            test.func();
            std::cout << "[ OK ] " << test.name << std::endl;
        } catch (const AssertionFailure &e) {
            failed++;
            std::cerr << "[FAIL] " << test.name << " - " << e.what() << std::endl;
        } catch (const std::exception &e) {
            failed++;
            std::cerr << "[EXC ] " << test.name << " - " << e.what() << std::endl;
        } catch (...) {
            failed++;
            std::cerr << "[UNKN] " << test.name << " - unknown exception" << std::endl;
        }
    }
    std::cout << registry().size() - failed << "/" << registry().size() << " tests passed" << std::endl;
    return failed;
}
} // namespace mini_catch

#define CATCH_CONCAT_IMPL(a, b) a##b
#define CATCH_CONCAT(a, b) CATCH_CONCAT_IMPL(a, b)

#define TEST_CASE(name)                                                                 \
    static void CATCH_CONCAT(test_func_, __LINE__)();                                  \
    static mini_catch::Registrar CATCH_CONCAT(_registrar_, __LINE__)(name, CATCH_CONCAT(test_func_, __LINE__)); \
    static void CATCH_CONCAT(test_func_, __LINE__)()

#define REQUIRE(expr)                                                                                     \
    do {                                                                                                  \
        if (!(expr)) throw mini_catch::AssertionFailure(std::string("REQUIRE failed: ") + #expr);        \
    } while (0)

#define CHECK(expr)                                                                                       \
    do {                                                                                                  \
        if (!(expr)) mini_catch::report_failure(#expr, __FILE__, __LINE__);                               \
    } while (0)

#ifdef CATCH_CONFIG_MAIN
int main() { return mini_catch::run_all(); }
#endif

