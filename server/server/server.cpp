#include <iostream>
#include <httplib.h>

void logger(const std::string& message) {
    std::cout << message << std::endl;
}

bool isNumber(const std::string& anNumber) {
    return anNumber.find_first_not_of("0123456789.") == std::string::npos;
}

int main(void)
{
    using namespace httplib;

    Server svr;

    // sum
    svr.Get("(/sum)", [&](const Request& req, Response& res) {
        auto a = req.get_param_value("a");
        auto b = req.get_param_value("b");

        logger("/sum get request accepted with params: " + a + ", " + b);

        if (!(isNumber(a) && isNumber(b))) {
            res.set_content("a and b should be a numbers", "text/plain");
            return 0;
        }

        double firstNumber = std::atof(a.c_str());
        double secondNumber = std::atof(b.c_str());

        res.set_content(std::to_string(firstNumber + secondNumber), "text/plain");
        });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
        });

    svr.listen("localhost", 1234);
}