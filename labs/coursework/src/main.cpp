#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
effect tex_eff;
effect tex_eff2;
free_camera cam;
texture alpha_map;
texture sand;
texture stone;
texture pillar;
point_light light;
frame_buffer frame;
geometry screen_quad;
bool masking = false;
bool greyscale = false;


bool load_content() {
	//
	// Create frame buffer - use screen width and height
	frame = frame_buffer(renderer::get_screen_width(), renderer::get_screen_height());
	// Create screen quad
	vector<vec3> positions{ vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(-1.0f, 1.0f, 0.0f),
		vec3(1.0f, 1.0f, 0.0f) };
	vector<vec2> tex_coords{ vec2(0.0, 0.0), vec2(1.0f, 0.0f), vec2(0.0f, 1.0f), vec2(1.0f, 1.0f) };
	screen_quad.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	screen_quad.add_buffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	screen_quad.set_type(GL_TRIANGLE_STRIP);

	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	// box
	meshes["box"] = mesh(geometry_builder::create_box());

	// Pyramid
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid2"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid3"] = mesh(geometry_builder::create_pyramid());

	// Cylinder
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinder2"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinder3"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinderTop"] = mesh(geometry_builder::create_cylinder());
	meshes["cylinderTop2"] = mesh(geometry_builder::create_cylinder());

	// Set the transforms for your meshes here
	// 5x scale, move(-10.0f, 2.5f, -30.0f)
	meshes["box"].get_transform().scale = vec3(15.0f, 1.0f, 1.0f);
	meshes["box"].get_transform().translate(vec3(-10.0f, 0.5f, -30.0f));
	

	// 10x scale, 15x widening, move(-10.0f, 7.5f, -30.0f)
	meshes["pyramid"].get_transform().scale = vec3(15.0f, 10.0f, 10.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 5.0f, -30.0f));
	
	// Two thirds scale of previous pyramid
	meshes["pyramid2"].get_transform().scale = vec3(10.0f, 7.0f, 7.0f);
	meshes["pyramid2"].get_transform().translate(vec3(-15.0f, 2.5f, -20.0f));

	meshes["pyramid3"].get_transform().scale = vec3(13.0f, 9.0f, 9.0f);
	meshes["pyramid3"].get_transform().translate(vec3(-5.0f, 4.5f, -45.0f));

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

	//Set Materials
		//All shininess is 25

	//Plane
	meshes["plane"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["plane"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["plane"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["plane"].get_material().set_shininess(75.0f);

	//Pyramids
	meshes["pyramid"].get_material().set_emissive(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid"].get_material().set_shininess(25.0f);
	//Pyramid2
	meshes["pyramid2"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["pyramid2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid2"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid2"].get_material().set_shininess(25.0f);
	//Pyramid3
	meshes["pyramid3"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["pyramid3"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid3"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["pyramid3"].get_material().set_shininess(25.0f);

	//Cylinder
	meshes["cylinder"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["cylinder"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder"].get_material().set_shininess(25.0f);
	//Cylinder2
	meshes["cylinder2"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["cylinder2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder2"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder2"].get_material().set_shininess(25.0f);
	//Cylinder3
	meshes["cylinder3"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["cylinder3"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder3"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinder3"].get_material().set_shininess(25.0f);
	//CylinderTop
	meshes["cylinderTop"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["cylinderTop"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinderTop"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinderTop"].get_material().set_shininess(25.0f);
	//CylinderTop2
	meshes["cylinderTop2"].get_material().set_emissive(vec4(0.5f, 0.5f, 0.5f, 0.5f));
	meshes["cylinderTop2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinderTop2"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["cylinderTop2"].get_material().set_shininess(25.0f);

	// Load texture
	sand = texture("C:/Users/40167459/Desktop/set08116/labs/coursework/res/textures/sand3.jpg");
	stone = texture("C:/Users/40167459/Desktop/set08116/labs/coursework/res/textures/pyramid_stones.jpg");
	pillar = texture("C:/Users/40167459/Desktop/set08116/labs/coursework/res/textures/pillar.jpg");

	alpha_map = texture("C:/Users/40167459/Desktop/set08116/labs/res/textures/checker.png");

	// Set lighting values, Position (-25, 10, -10)
	light.set_position(vec3(-10.0f, 20.0f, -30.0f));
	// Light colour white
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// Set range to 20
	light.set_range(2000);
	// Load in shaders
	eff.add_shader("shaders/point.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/point.frag", GL_FRAGMENT_SHADER);
	tex_eff.add_shader("shaders/masking.frag", GL_FRAGMENT_SHADER);
	tex_eff.add_shader("shaders/simple_textures.vert", GL_VERTEX_SHADER);
	tex_eff2.add_shader("shaders/simple_textures.vert", GL_VERTEX_SHADER);
	tex_eff2.add_shader("shaders/greyscale.frag", GL_FRAGMENT_SHADER);


	// Build effects
	eff.build();
	tex_eff.build();
	tex_eff2.build();

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
	if (glfwGetKey(renderer::get_window(), '1')) {
		masking = true;
	}
	if (glfwGetKey(renderer::get_window(), '2')) {
		masking = false;
	}
	if (glfwGetKey(renderer::get_window(), '3')) {
		greyscale = true;
	}
	if (glfwGetKey(renderer::get_window(), '4')) {
		greyscale = false;
	}

	// Set range
	light.set_range(200);

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

	if (masking == true || greyscale == true)
	{
		// Set render target to frame buffer
		renderer::set_render_target(frame);
		// Clear frame
		renderer::clear();
	}
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		//
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));              
								
						 // Set M matrix uniform
						 glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
						 // Set N matrix uniform - remember - 3x3 matrix
						 glUniformMatrix3fv(eff.get_uniform_location("N"),
							 1,
							 GL_FALSE,
							 value_ptr(m.get_transform().get_normal_matrix()));
						 // Bind material
						renderer::bind(m.get_material(), "mat");
						 // Bind light
						 renderer::bind(light, "point");
						
						 // Set tex uniform
						 glUniform1i(eff.get_uniform_location("tex"), 0);
						 // Set eye position- Get this from active camera
						 glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));


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

	if(masking == true) {

		// Set render target back to the screen
		renderer::set_render_target();
		// Bind Tex effect
		renderer::bind(tex_eff);
		// MVP is now the identity matrix
		auto MVP = glm::mat4();
		// Set MVP matrix uniform
		glUniformMatrix4fv(tex_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Bind texture from frame buffer
		renderer::bind(frame.get_frame(), 0);
		// Set the tex uniform
		glUniform1i(tex_eff.get_uniform_location("tex"), 0);
		// Bind alpha texture to TU, 1
		renderer::bind(alpha_map, 1);
		// Set the tex uniform, 1
		glUniform1i(tex_eff.get_uniform_location("tex"), 1);
		// Render the screen quad
		renderer::render(screen_quad);
	}

	if (greyscale == true) {

		// Set render target back to the screen
		renderer::set_render_target();
		// Bind Tex effect
		renderer::bind(tex_eff2);
		// MVP is now the identity matrix
		auto MVP = glm::mat4();
		// Set MVP matrix uniform
		glUniformMatrix4fv(tex_eff2.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Bind texture from frame buffer
		renderer::bind(frame.get_frame(), 0);
		// Set the tex uniform
		glUniform1i(tex_eff2.get_uniform_location("tex"), 0);
		// Render the screen quad
		renderer::render(screen_quad);
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