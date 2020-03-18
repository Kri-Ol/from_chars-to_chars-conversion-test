#include <cstdint>
#include <iostream>
#include <charconv>
#include <system_error>
#include <string_view>
#include <array>

constexpr char NL = '\n';

int main()
{
    std::array<char, 100> str;

    union {
        float    v;
        uint32_t i;
    } u;

    int64_t lmax = 0;
    float   vmax = 0.0f;

    uint64_t n = 0ULL;

    for(uint64_t k = 0ULL; k != 4294967296ULL; ++k)
    {
        u.i = k;

        if (std::isnan(u.v))
            continue;
        if (std::isinf(u.v))
            continue;

        auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), u.v);
        if (ec == std::errc())
        {
            ++n;
            auto l = p - str.data();
            if (l > lmax)
            {
                lmax = l;
                vmax = u.v;
            }

            float d = 0.0f;
            auto [q, ecc] = std::from_chars(str.data(), p, d);
            if (ecc != std::errc())
                std::cout << "Back conversion error" << NL;
            if (u.v != d) {
                std::cout << "NE: " << u.v << "   " << d << NL;
            }
        }
        else
        {
            std::cout << std::make_error_code(ec) << NL;
        }   
    }

    std::cout << "Done!" << NL;

    auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), vmax);
    std::cout << n << "   " << lmax << "   " << vmax << "   " << std::string_view(str.data(), p - str.data()) << NL;

    return 0;
}
