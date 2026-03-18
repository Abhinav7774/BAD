#pragma once

#include "BAD/Core.h"

#include <functional>
#include <string>

enum class EventType 
{
	None = 0,
	WindowResize, WindowClose, WindowFocus, WindowLoseFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	MouseMoved, MouseScrolled, MouseButtonPressed,MouseButtonReleased,
	KeyPressed, KeyHold,KeyReleased
};

enum EventCategory 
{
	NoEvent = 0,
	EventCategoryApplication	= BIT(0),
	EventCategoryMouse			= BIT(1),
	EventCategoryInput			= BIT(2),
	EventCategoryKeyboard		= BIT(3)
};

#define EVENT_CLASS_TYPE(type) virtual EventType GetEventType() const override {return EventType::type;}\
							   virtual const std::string GetEventName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlag() const override {return category;}

namespace BAD {
class BAD_API Event {
	public:
		
		virtual EventType GetEventType() const = 0;
		virtual const std::string GetEventName() const = 0;
		virtual int GetCategoryFlag() const = 0;
		virtual std::string toString() const {
			return GetEventName();
		}
		inline bool isInCategoryFlags(EventCategory category) {
			return GetCategoryFlag() & category;
		}
	protected:
		bool m_handled = false;
};
}
