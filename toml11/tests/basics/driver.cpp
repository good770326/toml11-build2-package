#include <toml.hpp>
#include <cassert>
#include <iostream>
//See another package named "toml11-tests" for complete testing
int main() {
    try {
        std::ofstream ifs("sample.toml");
        ifs << R"(answer  = 42
pi      = 3.14
numbers = [1,2,3]
time    = 1979-05-27T07:32:00Z)";
        ifs.close();
        const auto data      = toml::parse("sample.toml");
        const auto answer    = toml::find<std::int64_t    >(data, "answer");
        const auto pi        = toml::find<double          >(data, "pi");
        const auto numbers   = toml::find<std::vector<int>>(data, "numbers");
        const auto timepoint = toml::find<std::chrono::system_clock::time_point>(data, "time");
        assert(answer == 42);
        assert(pi == 3.14);
        assert(numbers == std::vector<int>({1, 2, 3}));
        assert(std::chrono::duration_cast<std::chrono::seconds>(timepoint.time_since_epoch()).count() % 60 == 0);
        assert(std::chrono::duration_cast<std::chrono::minutes>(timepoint.time_since_epoch()).count() % 60 == 32);
        assert(std::chrono::duration_cast<std::chrono::hours>(timepoint.time_since_epoch()).count() % 24 == 7);
    }
    catch(std::runtime_error const& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}