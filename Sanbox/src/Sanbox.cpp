#include "BAD.h"


class Sandbox : public BAD::Application {
	public:
		Sandbox() {

		}
		~Sandbox(){

		}
};

BAD::Application* BAD::CreateApplication() {
	return new Sandbox();
}