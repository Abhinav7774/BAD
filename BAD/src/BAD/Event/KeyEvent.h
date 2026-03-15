#pragma once

#include "BAD/Event/Event.h"
#include <sstream>
namespace BAD {
class BAD_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const {
			return m_keyCode;
		}
		int GetCategoryFlag() {
			return EventCategoryInput | EventCategoryKeyboard;
		}

	protected:
		KeyEvent(int p_keyCode) {
			m_keyCode = p_keyCode;
		}
		int m_keyCode;
};

class BAD_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int p_keyCode) : KeyEvent(p_keyCode) {};
		EventType GetEventType() const { return EventType::KeyPressed; }
		const std::string GetEventName() const { return "KeyPressed"; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressed" << " : " << m_keyCode;
			return ss.str();
		}
};

class BAD_API KeyHoldEvent : public KeyEvent {
	public:
		KeyHoldEvent(int p_keyCode,bool p_repeat) : KeyEvent(p_keyCode) {};
		EventType GetEventType() const { return EventType::KeyHold; }
		const std::string GetEventName() const { return "KeyHold"; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyHold" << " : " << m_keyCode;
			return ss.str();
		}
};

class BAD_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int p_keyCode) : KeyEvent(p_keyCode) {};
		EventType GetEventType() const { return EventType::KeyReleased; }
		const std::string GetEventName() const { return "KeyReleased"; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleased" << " : " << m_keyCode;
			return ss.str();
		}
};
}