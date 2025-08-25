#include "environment.hpp"

void Environment::render(std::int32_t delta) {
	for (auto particle : particles) {
		particle->render(delta);
	}
}

Environment::~Environment() {
	for (auto particle : particles) {
		delete particle;
	}
}