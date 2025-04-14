#pragma once

#include <unordered_map>
#include <string>
#include <set>
#include <functional>
#include <Utils/glm/glm.hpp>
#include <Utils/nlohmann/json.hpp>
#include "InputAction.h"
#include "InputEnums.h"
#include "InputBinding.h"

// Forward declarations for Event classes
class Event;
class KeyPressedEvent;
class KeyReleasedEvent;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMovedEvent;

namespace Rat {

    class InputManager
    {
    public:
        static InputManager& Get();

        void Initialize();
        void Shutdown();
        void Update(float deltaTime);
        void HandleEvent(Event& e);

        /// Register an input action (e.g. "Jump", "Attack")
        void RegisterInputAction(const std::string& name, const InputAction& action);

        /// Remove an action from the system
        void UnregisterInputAction(const std::string& name);

        /// Add a key/mouse binding to an action
        void BindInput(const std::string& actionName, const InputBinding& binding);

        /// Remove a binding from an action
        void UnbindInput(const std::string& actionName, const InputBinding& binding);

        /// Clear all key/mouse bindings
        void ClearBindings();

        /// Check if an action is active this frame
        bool IsActionActive(const std::string& actionName) const;

        /// Save all bindings to JSON
        void SaveBindings(const std::string& filepath) const;

        /// Load all bindings from JSON
        void LoadBindings(const std::string& filepath);

        /// Print all active actions
        void PrintActiveActions() const;

        // Direct input state
        bool IsKeyPressed(int keycode) const;
        bool IsKeyReleased(int keycode) const;
        bool IsKeyHeld(int keycode) const;
        bool IsMouseButtonPressed(int button) const;
        bool IsMouseButtonReleased(int button) const;
        bool IsMouseButtonHeld(int button) const;

        bool IsGamepadButtonPressed(int button) const;
        bool IsGamepadButtonHeld(int button) const;
        bool IsGamepadButtonReleased(int button) const;

        glm::vec2 GetMousePosition() const { return m_MousePosition; }

        static constexpr int MAX_GAMEPAD_BUTTONS = 16;
        static constexpr int MAX_GAMEPAD_AXES = 8;

    private:
        InputManager() = default;
        void ResetActions();

        void HandleKeyEvent(KeyPressedEvent& e);
        void HandleKeyReleaseEvent(KeyReleasedEvent& e);
        void HandleMouseButtonPressed(MouseButtonPressedEvent& e);
        void HandleMouseButtonReleased(MouseButtonReleasedEvent& e);
        void HandleMouseMoved(MouseMovedEvent& e);
        void UpdateGamepadState();

    private:
        std::unordered_map<int, InputState> m_KeyStates;
        std::unordered_map<int, InputState> m_MouseButtonStates;
        std::unordered_map<std::string, InputAction> m_InputActions;

        std::unordered_map<int, float> m_KeyHeldDuration;
        std::unordered_map<int, float> m_KeyLastPressTime;

        std::unordered_map<int, InputState> m_GamepadButtonStates;
        std::unordered_map<int, float> m_GamepadAxisValues;

        std::unordered_map<int, float> m_GamepadButtonHeldDuration;
        std::unordered_map<int, float> m_GamepadLastPressTime;

        glm::vec2 m_MousePosition = glm::vec2(0.0f);
        float m_DoubleTapThreshold = 0.3f;
        float m_LongHoldThreshold = 0.5f;
        float m_ElapsedTime = 0.0f;
    };

}