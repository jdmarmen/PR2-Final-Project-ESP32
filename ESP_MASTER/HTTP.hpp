#pragma once
#include <HTTPClient.h>
#include "Config.hpp"
#include "ESP.hpp"

class HTTP
{
public:
    static void post(std::string message);
};
