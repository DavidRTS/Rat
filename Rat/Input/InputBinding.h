#pragma once

#include "InputEnums.h"
#include <vector>
#include <tuple>
#include <functional>

namespace Rat {
    // Forward declaration not needed since we're including InputEnums.h
    // enum class InputType;
}

struct InputBinding
{
    Rat::InputType type = Rat::InputType::Keyboard;
    int code = 0;
    Rat::AxisDirection axisDirection = Rat::AxisDirection::Positive;
    std::vector<int> comboKeys;

    bool operator<(const InputBinding& other) const {
        return std::tie(type, code, axisDirection, comboKeys) <
            std::tie(other.type, other.code, other.axisDirection, other.comboKeys);
    }

    bool operator==(const InputBinding& other) const {
        return type == other.type &&
            code == other.code &&
            axisDirection == other.axisDirection &&
            comboKeys == other.comboKeys;
    }
};

namespace std
{
    template <>
    struct hash<InputBinding>
    {
        std::size_t operator()(const InputBinding& binding) const
        {
            std::size_t hashVal = std::hash<int>()(static_cast<int>(binding.type)) ^
                std::hash<int>()(binding.code);

            for (int k : binding.comboKeys)
                hashVal ^= std::hash<int>()(k);

            hashVal ^= std::hash<int>()(static_cast<int>(binding.axisDirection));
            return hashVal;
        }
    };
}
