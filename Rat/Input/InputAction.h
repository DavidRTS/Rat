#pragma once

#include <unordered_set>
#include <functional>
#include "InputBinding.h"

struct InputAction
{
    std::unordered_set<InputBinding> bindings;
    bool active = false;
    std::function<void()> callback = nullptr;

    void Reset() { active = false; }
};
