#include "robot.h"

Robot::Robot() {
	for (std::string componentName : this->componentNames) {
		glm::vec3 init_scale = INIT_SCALES[componentName];
		glm::vec3 init_center_position = INIT_CENTER_POSITIONS[componentName];
		glm::vec3 init_color = INIT_COLORS[componentName];
		glm::vec3 init_direction = INIT_DIRECTIONS[componentName];
		float init_shaft_percent = INIT_SHAFT_PERCENTS[componentName];
		float init_rotate_degrees = INIT_ROTATE_DEGREES[componentName];
		this->components[componentName] = new Cube(
			init_scale,
			init_center_position,
			init_color,
			init_direction,
			init_shaft_percent,
			init_rotate_degrees
		);
	}
}
Robot::~Robot() {
	for (std::string componentName : this->componentNames) {
		delete this->components[componentName];
	}
}
void Robot::exportToCubes(std::vector<Cube*>& vec) {
	for (auto component : this->components) {
		vec.push_back(component.second);
	}
}
void Robot::rotate(std::string componentName, float degree_x, float degree_y, float degree_z) {
	Cube* moveCube = nullptr;
	if (componentName == "arm_li") {
		moveCube = this->components["arm_lo"];
	}
	if (componentName == "arm_ri") {
		moveCube = this->components["arm_ro"];
	}
	if (componentName == "leg_li") {
		moveCube = this->components["leg_lo"];
	}
	if (componentName == "leg_ri") {
		moveCube = this->components["leg_ro"];
	}
	this->components[componentName]->rotate(degree_x, degree_y, degree_z, moveCube);
}
void Robot::translate(glm::vec3 vec) {
	for (auto it = this->components.begin(); it != this->components.end(); it++) {
		Cube* component = it->second;
		component->translate(vec);
	}
}
void Robot::setActions(std::vector<char> pressList) {
	for (auto it = actions.begin(); it != actions.end(); it++) {
		if (it->second != -1) {
			return;
		}
	}
	for(char press : pressList) {
		if (this->actionByChar.count(press) == 0) {
			continue;
		}
		Action myAction = this->actionByChar[press];
		if (this->actions[myAction] == -1) {
			this->actions[myAction] = 0;
		}
	}
	return;
}
void Robot::action() {
	if (this->actions[Action::Jump] != -1) {
		this->jump();
	}
	if (this->actions[Action::Crouch] != -1) {
		this->crouch();
	}
	if (this->actions[Action::Sprint] != -1) {
		this->sprint();
	}
	if (this->actions[Action::Hi] != -1) {
		this->hi();
	}
}
void Robot::jump() {
	if (this->actions[Action::Jump] >= 100) {
		this->actions[Action::Jump] = -1;
		return;
	}
	if (this->actions[Action::Jump] >= 50) {
		this->translate(glm::vec3(0.0f, -0.03f, 0.0f));
		this->rotate("arm_li", -0.5f, 0.0f, 0.0f);
		this->rotate("arm_lo", 1.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", -0.5f, 0.0f, 0.0f);
		this->rotate("arm_ro", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_li", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_ri", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", -1.0f, 0.0f, 0.0f);
	}
	else {
		this->translate(glm::vec3(0.0f, 0.03f, 0.0f));
		this->rotate("arm_li", 0.5f, 0.0f, 0.0f);
		this->rotate("arm_lo", -1.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", 0.5f, 0.0f, 0.0f);
		this->rotate("arm_ro", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_li", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_ri", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", 1.0f, 0.0f, 0.0f);
	}
	this->actions[Action::Jump]++;
}
void Robot::crouch() {
	if (this->actions[Action::Crouch] >= 100) {
		this->actions[Action::Crouch] = -1;
		return;
	}
	if (this->actions[Action::Crouch] >= 50) {
		this->translate(glm::vec3(0.0f, 0.01f, 0.0f));
		this->rotate("arm_li", -0.5f, 0.0f, 0.0f);
		this->rotate("arm_lo", 1.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", -0.5f, 0.0f, 0.0f);
		this->rotate("arm_ro", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_li", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_ri", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", -1.0f, 0.0f, 0.0f);
	}
	else {
		this->translate(glm::vec3(0.0f, -0.01f, 0.0f));
		this->rotate("arm_li", 0.5f, 0.0f, 0.0f);
		this->rotate("arm_lo", -1.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", 0.5f, 0.0f, 0.0f);
		this->rotate("arm_ro", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_li", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_ri", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", 1.0f, 0.0f, 0.0f);
	}
	this->actions[Action::Crouch]++;
}
void Robot::sprint() {
	if (this->actions[Action::Sprint] >= 500) {
		this->actions[Action::Sprint] = -1;
		return;
	}
	if (this->actions[Action::Sprint] >= 450) {
		this->translate(glm::vec3(0.0f, 0.002f, 0.0f));
		this->rotate("arm_li", 0.2f, 0.0f, 0.0f);
		this->rotate("arm_lo", 3.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", -0.7f, 0.0f, 0.0f);
		this->rotate("arm_ro", 1.5f, 0.0f, 0.0f);
		this->rotate("leg_li", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", -0.2f, 0.0f, 0.0f);
		this->rotate("leg_ri", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", -3.0f, 0.0f, 0.0f);
	}
	else if (this->actions[Action::Sprint] < 50) {
		this->translate(glm::vec3(0.0f, -0.002f, 0.0f));
		this->rotate("arm_li", -0.2f, 0.0f, 0.0f);
		this->rotate("arm_lo", -3.0f, 0.0f, 0.0f);
		this->rotate("arm_ri", 0.7f, 0.0f, 0.0f);
		this->rotate("arm_ro", -1.5f, 0.0f, 0.0f);
		this->rotate("leg_li", -0.5f, 0.0f, 0.0f);
		this->rotate("leg_lo", 0.2f, 0.0f, 0.0f);
		this->rotate("leg_ri", 0.5f, 0.0f, 0.0f);
		this->rotate("leg_ro", 3.0f, 0.0f, 0.0f);
	}
	else if (this->actions[Action::Sprint] % 100 >= 50) {
		this->rotate("arm_li", 0.9f, 0.0f, 0.0f);
		this->rotate("arm_lo", 1.5f, 0.0f, 0.0f);
		this->rotate("arm_ri", -0.9f, 0.0f, 0.0f);
		this->rotate("arm_ro", -1.5f, 0.0f, 0.0f);
		this->rotate("leg_li", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_lo", 2.8f, 0.0f, 0.0f);
		this->rotate("leg_ri", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_ro", -2.8f, 0.0f, 0.0f);
	}
	else {
		this->rotate("arm_li", -0.9f, 0.0f, 0.0f);
		this->rotate("arm_lo", -1.5f, 0.0f, 0.0f);
		this->rotate("arm_ri", 0.9f, 0.0f, 0.0f);
		this->rotate("arm_ro", 1.5f, 0.0f, 0.0f);
		this->rotate("leg_li", -1.0f, 0.0f, 0.0f);
		this->rotate("leg_lo", -2.8f, 0.0f, 0.0f);
		this->rotate("leg_ri", 1.0f, 0.0f, 0.0f);
		this->rotate("leg_ro", 2.8f, 0.0f, 0.0f);

	}
	this->actions[Action::Sprint]++;
}
void Robot::hi() {
	if (this->actions[Action::Hi] >= 300) {
		this->actions[Action::Hi] = -1;
		return;
	}
	if (this->actions[Action::Hi] >= 250) {
		this->rotate("head", 0.4f, 0.9f, 0.0f);
		this->rotate("arm_li", 0.2f, 0.0f, 0.5f);
		this->rotate("arm_lo", 3.8f, 0.0f, 1.2f);
	}
	else if (this->actions[Action::Hi] < 50) {
		this->rotate("head", -0.4f, -0.9f, 0.0f);
		this->rotate("arm_li", -0.2f, 0.0f, -0.5f);
		this->rotate("arm_lo", -3.8f, 0.0f, -1.2f);
	}
	else if (this->actions[Action::Hi] % 100 >= 50) {
		this->rotate("arm_lo", 1.5f, 0.0f, 0.8f);
	}
	else {
		this->rotate("arm_lo", -1.5f, 0.0f, -0.8f);

	}
	this->actions[Action::Hi]++;
}