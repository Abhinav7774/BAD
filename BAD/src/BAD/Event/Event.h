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

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;}\
							   virtual EventType GetEventType() const override {return GetStaticType(); }\
							   virtual const std::string GetEventName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlag() const override {return category;}

namespace BAD {
class BAD_API Event {
	public:
		friend class EventDispatcher;
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

class BAD_API EventDispatcher {
	template<class T>
	using EventFun = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
		: m_event(event) {};

		template<class T>
		bool Dispatch(EventFun<T> finc) {
			if (m_event.GetEventType() == T::GetStaticType()) {
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	protected:
		Event& m_event;
		
};

}
