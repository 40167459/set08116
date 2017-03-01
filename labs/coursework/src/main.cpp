#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
free_camera cam;
texture sand;
texture stone;
texture pillar;
directional_light light;

bool load_content() {
	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	// box
	meshes["box"] = mesh(geometry_builder::create_box());

	// Tetrahedron 
	/*
	meshes["tetrahedron"] = mesh(geometry_builder::create_tetrahedron());
	*/
	// Pyramid
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid2"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid3"] = mesh(geometry_builder::create_pyramid());
	/*
	// Disk
	meshes["disk"] = mesh(geometry_builder::create_disk());
	*/

	// Cylinder
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinder2"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinder3"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinderTop"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinderTop2"] = mesh(geometry_builder::create_cylinder());

	/*
	// Sphere
	meshes["sphere"] = mesh(geometry_builder::create_sphere());
	// Torus
	meshes["torus"] = mesh(geometry_builder::create_torus());
	*/

	// Set the transforms for your meshes here
	// 5x scale, move(-10.0f, 2.5f, -30.0f)
	meshes["box"].get_transform().scale = vec3(15.0f, 1.0f, 1.0f);
	meshes["box"].get_transform().translate(vec3(-10.0f, 0.5f, -30.0f));

	/*
	// 4x scale, move(-30.0f, 10.0f, -10.0f)
    meshes["tetrahedron"].get_transform().scale = vec3(4.0f, 4.0f, 4.0f);
	meshes["tetrahedron"].get_transform().translate(vec3(-30.0f, 10.0f, -10.0f));

	*/
	
	// 10x scale, 15x widening, move(-10.0f, 7.5f, -30.0f)
	meshes["pyramid"].get_transform().scale = vec3(15.0f, 10.0f, 10.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 5.0f, -30.0f));

	// Two thirds scale of previous pyramid
	meshes["pyramid2"].get_transform().scale = vec3(10.0f, 7.0f, 7.0f);
	meshes["pyramid2"].get_transform().translate(vec3(-15.0f, 2.5f, -20.0f));

	meshes["pyramid3"].get_transform().scale = vec3(13.0f, 9.0f, 9.0f);
	meshes["pyramid3"].get_transform().translate(vec3(-5.0f, 4.5f, -45.0f));
	
	/*
	// scale(3.0f, 1.0f, 3.0f), move(-10.0f, 11.5f, -30.0f), 180 rotate X axis
	meshes["disk"].get_transform().scale = vec3(3.0f, 1.0f, 3.0f);
	meshes["disk"].get_transform().translate(vec3(-10.0f, 11.5f, -30.0f));
	*/

	// 1.5x scale, move(0.0.f, 2.5f, 0.0f)
	meshes["cylinder"].get_transform().scale = vec3(1.5f, 5.5f, 1.5f);
	meshes["cylinder"].get_transform().translate(vec3(0.0f, -0.5f, 0.0f));

	// 1.5x scale, move(0.0.f, 2.5f, 0.0f)
	meshes["cylinder2"].get_transform().scale = vec3(1.5f, 5.5f, 1.5f);
	meshes["cylinder2"].get_transform().translate(vec3(5.0f, 2.0f, 0.0f));

	meshes["cylinderTop"].get_transform().scale = vec3(2.0f, 0.5f, 2.0f);
	meshes["cylinderTop"].get_transform().translate(vec3(5.0f, 5.0f, 0.0f));

	meshes["cylinder3"].get_transform().scale = vec3(1.5f, 5.5f, 1.5f);
	meshes["cylinder3"].get_transform().translate(vec3(0.0f, 2.0f, 5.0f));

	meshes["cylinderTop2"].get_transform().scale = vec3(2.0f, 0.5f, 2.0f);
	meshes["cylinderTop2"].get_transform().translate(vec3(0.0f, 5.0f, 5.0f));

	/*
	// 2.5x scale, move(-25.0f, 10.0f, -25.0f)
	meshes["sphere"].get_transform().scale = vec3(2.5f, 2.5f, 2.5f);
	meshes["sphere"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));

	// 180 rotate X axis, move(-25.0f, 10.0f, -25.0f)
	meshes["torus"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f)); 

	*/

	//Set Materials
	//Pyramid






	// Load texture
	sand = texture("textures/sand3.jpg");
	stone = texture("textures/pyramid_stones.jpg");
	pillar = texture("textures/pillar.jpg");


	// Set lighting values
	light.set_ambient_intensity(vec4(0.3f, 0.3f, 0.3f, 1.0f));
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light.set_direction(vec3(1.0f, 1.0f, -1.0f));

	// Load in shaders
	eff.add_shader("shaders/simple_texture.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/simple_texture.frag", GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	//Load in Camera properties
	cam.set_position(vec3(0.0f, 5.0f, 10.0f));
	cam.set_target(vec3(0.0f, 0.0f, 0.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

bool update(float delta_time) {
	// The ratio of pixels to rotation - remember the fov
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() * renderer::get_screen_aspect()) / static_cast<float>(renderer::get_screen_height());
	static double cursor_x = 0.0;
	static double cursor_y = 0.0;
	double current_x;
	double current_y;
	// Get the current cursor position
	glfwGetCursorPos(renderer::get_window(), &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= ratio_width;
	delta_y *= ratio_height;
	// Rotate cameras by delta
	cam.rotate(delta_x, -delta_y);
	// Use keyboard to move the camera - WASD
	vec3 translation(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(renderer::get_window(), 'W')) {
		translation.z += 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'S')) {
		translation.z -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'A')) {
		translation.x -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'D')) {
		translation.x += 5.0f * delta_time;
	}

	// Move camera
	cam.move(translation);
	// Update the camera
	cam.update(delta_time);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	return true;
}

bool render() {
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		/*
		// Bind material
		renderer::bind(m.get_material(), "mat");
		// Bind light
		renderer::bind(light, "light");
		*/
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

		if (e.first == "plane")
		{
			renderer::bind(sand, 0);
		}
		if (e.first == "pyramid")
		{
			renderer::bind(stone, 0);
		}
		if (e.first == "pyramid2")
		{
			renderer::bind(stone, 0);
		}
		if (e.first == "box")
		{
			renderer::bind(pillar, 0);
		}
		if (e.first == "cylinder")
		{
			renderer::bind(pillar, 0);
		}

		// Render mesh
		renderer::render(m);
	}

	return true;
}

void main() {
	// Create application
	app application("CW1");
	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}