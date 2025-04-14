#pragma once

namespace Rat {

	/// Supported input device types
	enum class InputType
	{
		Keyboard,
		MouseButton,
		GamepadButton,
		GamepadAxis,
		Combo
	};

	enum class AxisDirection
	{
		None,
		Positive,
		Negative
	};

	/// State of a button/key this frame
	enum class InputState
	{
		None,
		Pressed,
		Held,
		Released
	};

}