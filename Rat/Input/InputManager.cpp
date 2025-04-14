#include <RTHeader.h>
#include "InputEnums.h"
#include "InputManager.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "InputAction.h"
#include "InputBinding.h"
#include <fstream>
#include <iostream>

namespace Rat {

    bool PollGamepadButton(int btn)
    {
        // Replace with actual gamepad button polling code
        return false;
    }

    float PollGamepadAxis(int axis)
    {
        // Replace with actual axis polling
        return 0.0f;
    }

    InputManager& InputManager::Get()
    {
        static InputManager instance;
        return instance;
    }

    void InputManager::Initialize() {}

    void InputManager::Shutdown() {}

    void InputManager::Update(float deltaTime)
    {
        m_ElapsedTime += deltaTime;

        UpdateGamepadState();
        ResetActions();

        for (auto& [key, state] : m_KeyStates)
        {
            if (state == InputState::Pressed)
                state = InputState::Held;
            else if (state == InputState::Released)
                state = InputState::None;

            if (state == InputState::Held)
                m_KeyHeldDuration[key] += deltaTime;
        }

        for (auto& [btn, state] : m_MouseButtonStates)
        {
            if (state == InputState::Pressed)
                state = InputState::Held;
            else if (state == InputState::Released)
                state = InputState::None;
        }

        for (auto& [name, action] : m_InputActions)
        {
            if (IsActionActive(name))
            {
                action.active = true;
                if (action.callback)
                    action.callback();
            }
        }
    }

    void InputManager::HandleEvent(Event& e)
    {
        if (e.GetEventType() == EventType::KeyPressed)
            HandleKeyEvent(static_cast<KeyPressedEvent&>(e));
        else if (e.GetEventType() == EventType::KeyReleased)
            HandleKeyReleaseEvent(static_cast<KeyReleasedEvent&>(e));
        else if (e.GetEventType() == EventType::MouseButtonPressed)
            HandleMouseButtonPressed(static_cast<MouseButtonPressedEvent&>(e));
        else if (e.GetEventType() == EventType::MouseButtonReleased)
            HandleMouseButtonReleased(static_cast<MouseButtonReleasedEvent&>(e));
        else if (e.GetEventType() == EventType::MouseMoved)
            HandleMouseMoved(static_cast<MouseMovedEvent&>(e));
    }

    void InputManager::ResetActions()
    {
        for (auto& [_, action] : m_InputActions)
            action.Reset();
    }

    void InputManager::HandleKeyEvent(KeyPressedEvent& e)
    {
        int key = e.GetKeyCode();
        float currentTime = m_ElapsedTime;

        InputState& state = m_KeyStates[key];
        if (state == InputState::None || state == InputState::Released)
        {
            state = InputState::Pressed;
            float lastTime = m_KeyLastPressTime[key];

            if ((currentTime - lastTime < m_DoubleTapThreshold) && m_InputActions.find("DoubleTap") != m_InputActions.end())
                m_InputActions["DoubleTap"].active = true;

            m_KeyLastPressTime[key] = currentTime;
        }

        m_KeyHeldDuration[key] = 0.0f;
    }

    void InputManager::HandleKeyReleaseEvent(KeyReleasedEvent& e)
    {
        int key = e.GetKeyCode();
        m_KeyStates[key] = InputState::Released;

        if (m_KeyHeldDuration[key] >= m_LongHoldThreshold && m_InputActions.find("LongHold") != m_InputActions.end())
            m_InputActions["LongHold"].active = true;

        m_KeyHeldDuration[key] = 0.0f;
    }

    void InputManager::HandleMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        m_MouseButtonStates[e.GetMouseButton()] = InputState::Pressed;
    }

    void InputManager::HandleMouseButtonReleased(MouseButtonReleasedEvent& e)
    {
        m_MouseButtonStates[e.GetMouseButton()] = InputState::Released;
    }

    void InputManager::HandleMouseMoved(MouseMovedEvent& e)
    {
        m_MousePosition = glm::vec2(e.GetX(), e.GetY());
    }

    void InputManager::RegisterInputAction(const std::string& name, const InputAction& action)
    {
        m_InputActions[name] = action;
    }

    void InputManager::UnregisterInputAction(const std::string& name)
    {
        m_InputActions.erase(name);
    }

    void InputManager::BindInput(const std::string& actionName, const InputBinding& binding)
    {
        auto it = m_InputActions.find(actionName);
        if (it != m_InputActions.end())
            it->second.bindings.insert(binding);
        else
            RTE_LOG_WARN("Action name doesn't exist.");
    }

    void InputManager::UnbindInput(const std::string& actionName, const InputBinding& binding)
    {
        auto it = m_InputActions.find(actionName);
        if (it != m_InputActions.end())
            it->second.bindings.erase(binding);
        else
            RTE_LOG_WARN("Action name doesn't exist.");
    }

    bool InputManager::IsActionActive(const std::string& name) const
    {
        auto it = m_InputActions.find(name);
        if (it == m_InputActions.end()) return false;

        for (const auto& binding : it->second.bindings)
        {
            switch (binding.type)
            {
            case InputType::Keyboard:
                if (IsKeyPressed(binding.code)) return true;
                break;
            case InputType::MouseButton:
                if (IsMouseButtonPressed(binding.code)) return true;
                break;
            case InputType::GamepadButton:
                if (IsGamepadButtonPressed(binding.code)) return true;
                break;
            case InputType::GamepadAxis:
            {
                auto axisIt = m_GamepadAxisValues.find(binding.code);
                if (axisIt != m_GamepadAxisValues.end())
                {
                    if (binding.axisDirection == AxisDirection::Positive && axisIt->second > 0.5f)
                        return true;
                    else if (binding.axisDirection == AxisDirection::Negative && axisIt->second < -0.5f)
                        return true;
                }
                break;
            }
            case InputType::Combo:
            {
                bool comboActive = true;
                for (int key : binding.comboKeys)
                {
                    if (!IsKeyHeld(key))
                    {
                        comboActive = false;
                        break;
                    }
                }
                if (comboActive) return true;
                break;
            }
            }
        }
        return false;
    }

    bool InputManager::IsKeyPressed(int keycode) const
    {
        auto it = m_KeyStates.find(keycode);
        return it != m_KeyStates.end() && it->second == InputState::Pressed;
    }

    bool InputManager::IsKeyReleased(int keycode) const
    {
        auto it = m_KeyStates.find(keycode);
        return it != m_KeyStates.end() && it->second == InputState::Released;
    }

    bool InputManager::IsKeyHeld(int keycode) const
    {
        auto it = m_KeyStates.find(keycode);
        return it != m_KeyStates.end() && it->second == InputState::Held;
    }

    bool InputManager::IsMouseButtonPressed(int button) const
    {
        auto it = m_MouseButtonStates.find(button);
        return it != m_MouseButtonStates.end() && it->second == InputState::Pressed;
    }

    bool InputManager::IsMouseButtonReleased(int button) const
    {
        auto it = m_MouseButtonStates.find(button);
        return it != m_MouseButtonStates.end() && it->second == InputState::Released;
    }

    bool InputManager::IsMouseButtonHeld(int button) const
    {
        auto it = m_MouseButtonStates.find(button);
        return it != m_MouseButtonStates.end() && it->second == InputState::Held;
    }

    bool InputManager::IsGamepadButtonPressed(int button) const
    {
        auto it = m_GamepadButtonStates.find(button);
        return it != m_GamepadButtonStates.end() && it->second == InputState::Pressed;
    }

    bool InputManager::IsGamepadButtonHeld(int button) const
    {
        auto it = m_GamepadButtonStates.find(button);
        return it != m_GamepadButtonStates.end() && it->second == InputState::Held;
    }

    bool InputManager::IsGamepadButtonReleased(int button) const
    {
        auto it = m_GamepadButtonStates.find(button);
        return it != m_GamepadButtonStates.end() && it->second == InputState::Released;
    }

    void InputManager::UpdateGamepadState()
    {
        // Example: Poll using your platform's gamepad API

        // Gamepad buttons
        for (int btn = 0; btn < MAX_GAMEPAD_BUTTONS; ++btn)
        {
            bool pressed = PollGamepadButton(btn); // Replace with your system
            auto& state = m_GamepadButtonStates[btn];

            if (pressed)
            {
                if (state == InputState::None || state == InputState::Released)
                    state = InputState::Pressed;
                else
                    state = InputState::Held;
            }
            else
            {
                if (state == InputState::Pressed || state == InputState::Held)
                    state = InputState::Released;
                else
                    state = InputState::None;
            }
        }

        // Gamepad axes
        for (int axis = 0; axis < MAX_GAMEPAD_AXES; ++axis)
            m_GamepadAxisValues[axis] = PollGamepadAxis(axis); // Replace with your system
    }

    void InputManager::SaveBindings(const std::string& filepath) const
    {
        nlohmann::json json;
        for (const auto& [name, action] : m_InputActions)
        {
            for (const auto& bind : action.bindings) {
                nlohmann::json bindJson;
                bindJson["type"] = static_cast<int>(bind.type);
                bindJson["code"] = bind.code;

                if (bind.type == InputType::Combo)
                    bindJson["combo"] = bind.comboKeys;

                if (bind.type == InputType::GamepadAxis)
                    bindJson["axisDirection"] = static_cast<int>(bind.axisDirection);

                json[name].push_back(bindJson);
            }
        }

        std::ofstream file(filepath);
        if (!file)
        {
            RTE_LOG_ERROR("Failed to open file for saving input bindings: {}");
            return;
        }
        file << json.dump(4);
    }

    void InputManager::LoadBindings(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) return;

        nlohmann::json json;
        try {
            file >> json;
        }
        catch (const nlohmann::json::parse_error) {
            RTE_LOG_ERROR("Failed to parse input bindings file: {}");
            return;
        }

        m_InputActions.clear();
        for (auto& [name, binds] : json.items())
        {
            InputAction action;
            for (auto& bind : binds)
            {
                InputBinding binding;
                binding.type = static_cast<InputType>(bind["type"]);
                binding.code = bind["code"];

                if (bind.contains("combo"))
                    binding.comboKeys = bind["combo"].get<std::vector<int>>();
                if (bind.contains("axisDirection"))
                    binding.axisDirection = static_cast<AxisDirection>(bind["axisDirection"].get<int>());

                action.bindings.insert(binding);
            }
            m_InputActions[name] = action;
        }
    }

    void InputManager::ClearBindings()
    {
        for (auto& [_, action] : m_InputActions)
            action.bindings.clear();
    }

    void InputManager::PrintActiveActions() const
    {
        for (const auto& [name, action] : m_InputActions)
        {
            if (action.active)
                std::cout << "Active: " << name << "\n";
        }
    }
}