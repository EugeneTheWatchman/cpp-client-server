#include <iostream>
#include <cpr/cpr.h>

int main()
{   
    std::cout << "enter 2 numbers:" << std::endl;
    std::string a, b;
    std::cin >> a;
    std::cin >> b;

    auto url = cpr::Url{ "http://localhost:1234/sum" };
    
    auto params = cpr::Parameters{ {"a", a },{"b", b}};
    auto r = cpr::Post(url, params);
    if (r.status_code != 200) {
        std::cout << "request failed" << std::endl;
    }
    else
    {
        std::cout << "sum is " << r.text << std::endl;
        cpr::Get(cpr::Url{ "http://localhost:1234/stop" });
    }
}
