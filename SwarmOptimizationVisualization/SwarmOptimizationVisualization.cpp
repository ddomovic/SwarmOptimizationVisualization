#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <time.h>
#include <vector>
#include "SwarmGroup.h"
#include "World.h"

float width = 800;
float height = 600;
GLuint window;
int fps;
GLfloat start_time_fps;
glm::vec2 group_initial_point = glm::vec2(50, 50);
World *world;

void display_f() {

	float current_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	if (current_time_fps - start_time_fps > 1.0f / fps) {
		glClearColor(0.0, 0.0, 0.0, 1.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glLineWidth(1.0f);
		glPointSize(3.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		//glTranslatef(width / 2.0f, height / 2.0f, 0);

		world->draw();

		glFlush();
		start_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
		
		world->run();
	}
}

void reshape_f(int w, int h) {
	
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
}

void mouse_f(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		world->set_goal_X(x);
		world->set_goal_Y(height - y);
		world->reset_groups();
	}
}

void keyboard_f(unsigned char key, int x, int y) {
}

void init_everything() {

	int number_of_swarms;

	world = new World();
	world->set_goal_X(width - 300);
	world->set_goal_Y(height - 300);

	while (true) {
		std::cout << "Input the number of swarms: ";
		std::cin >> number_of_swarms;
		if (number_of_swarms <= 0) {
			std::cout << "Invalid number of swarms, try again...\n";
		}
		else {
			break;
		}
	}
	std::vector<SwarmGroup*> groups;
	for (int i = 0; i < number_of_swarms; i++) {
		groups.push_back(new SwarmGroup(world));
		int swarm_size;
		while (true) {
			std::cout << "Input swarm " << i+1 << " size: ";
			std::cin >> swarm_size;
			if (swarm_size <= 0) {
				std::cout << "Invalid swarm size, try again...\n";
			}
			else {
				break;
			}
		}
		float velocity_modificator;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " velocity modificator: ";
			std::cin >> velocity_modificator;
			if (velocity_modificator <= 0.0f) {
				std::cout << "Invalid velocity modificator value, try again...\n";
			}
			else {
				break;
			}
		}
		float learning_factor_1;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " learning factor 1: ";
			std::cin >> learning_factor_1;
			if (learning_factor_1 < 0.0f) {
				std::cout << "Invalid learning factor value, try again...\n";
			}
			else {
				break;
			}
		}
		float learning_factor_2;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " learning factor 2: ";
			std::cin >> learning_factor_2;
			if (learning_factor_2 < 0.0f) {
				std::cout << "Invalid learning factor value, try again...\n";
			}
			else {
				break;
			}
		}
		float color_R;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " R color component: ";
			std::cin >> color_R;
			if (color_R < 0.0f || color_R > 1.0f) {
				std::cout << "Invalid color value, try again...\n";
			}
			else {
				break;
			}
		}
		float color_G;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " G color component: ";
			std::cin >> color_G;
			if (color_G < 0.0f || color_G > 1.0f) {
				std::cout << "Invalid color value, try again...\n";
			}
			else {
				break;
			}
		}
		float color_B;
		while (true) {
			std::cout << "Input swarm " << i + 1 << " B color component: ";
			std::cin >> color_B;
			if (color_B < 0.0f || color_B > 1.0f) {
				std::cout << "Invalid color value, try again...\n";
			}
			else {
				break;
			}
		}
		glm::vec4 color = glm::vec4(color_R, color_G, color_B, 1.0f);
		groups.back()->initialize_group(swarm_size, velocity_modificator, learning_factor_1, learning_factor_2, color, width, height);
	}
	int frames_per_second;
	while (true) {
		std::cout << "Input frames per second: ";
		std::cin >> frames_per_second;
		if (frames_per_second < 0 || frames_per_second > 120) {
			std::cout << "Invalid fps value, or too high (max 120), try again...\n";
		}
		else {
			break;
		}
	}
	fps = frames_per_second;
	world->set_groups(groups);
	//std::cout << "All set, click anywhere on the screen to set a new goal point.\n Press ENTER to continue...\n";
}

int main(int argc, char *argv[]) {

	srand(time(NULL));
	init_everything();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutInit(&argc, argv);
	window = glutCreateWindow("Swarm Intelligence Visualization");
	glutReshapeFunc(reshape_f);
	glutDisplayFunc(display_f);
	glutIdleFunc(display_f);
	glutMouseFunc(mouse_f);
	glutKeyboardFunc(keyboard_f);
	
	start_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glutMainLoop();

	return 0;
}