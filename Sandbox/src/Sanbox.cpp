#include "BAD.h"


class GameLayer : public BAD::Layer
{
public:
	GameLayer() : Layer("Game") {}

	void OnAttach() override {
		BAD_DBUG("GameLayer::OnAttach");
	}
	void OnUpdate() override {
		//BAD_TRACE("GameLayer::OnUpdate");
	}
};

class Sandbox : public BAD::Application {
public:
	Sandbox() {
		PushLayer(new GameLayer());
	}
};

BAD::Application* BAD::CreateApplication() {
	return new Sandbox();
}