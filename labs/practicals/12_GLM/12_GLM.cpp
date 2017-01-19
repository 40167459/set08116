#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() {
	{
		//12.1.1
		vec2 u(1.0, 0.0);
		vec2 v(1.0, 0.0);
		vec3 w(2.0, 0.0, 0.0);
		vec3 x(2.0, 0.0, 0.0);
		vec4 y(1.0, 1.0, 1.0, 0.0);
		vec4 z(1.0, 1.0, 1.0, 0.0);// Or RGBA for colours

		vec2 u(vec3(1.0, 1.0, 0.0)); //z component is dropped
		vec2 v(vec4(0.0, 1.0, 1.0, 0.0)); // z and w components dropped
		vec3 w(vec4(1.0, 1.0, 1.0, 0.0)); // w component dropped
		vec3 x(vec2(1.0, 1.0), 0.0);
		vec4 y(vec2(1.0, 1.0), 1.0, 0.0);
		vec4 z(vec3(1.0, 1.0, 0.0), 0.0);

		float x = u.x;
		u.y = 10.0f;
	}
	//12.1.2
	{
	vec3 u(1.0, 1.0, 0.0);
	vec3 v(2.0, 2.0, 0.0);
	vec3 w(3.0, 3.0, 0.0);
	vec3 x(4.0, 2.0, 0.0);
	vec3 y(3.0, 2.0, 0.0);
	vec3 z(1.0, 3.0, 0.0);

	vec3 w = u + v;
	vec3 v = u + u;
	vec3 x = w + w;
	vec3 y = x + w;
	vec3 z = v + w;
	vec3 y = x + w;

}

	//12.1.3
	{
		vec2 x(1.0, 0.0);
		vec2 y(1.0, 0.0);
		vec3 z(1.0, 1.0, 0.0);
		vec3 u(1.0, 1.0, 0.0);
		vec4 w(1.0, 1.0, 1.0, 0.0);
		vec4 v(.0, 1.0, 1.0, 0.0);


		vec3 v = 5.0f * u;
		vec3 w = u / 5.0f;
		vec3 u = 5.0f * v;
		vec3 x = 2.0f * v;
		vec3 y = 3.0f * w;
		vec3 z = 4.0f * z;

		vec2 x = 5.0f * u;
		vec2 y = u / 6.0f;

		vec4 a = w * 5.0f;
		vec4 b = 6.0f / v;

	}
		// Same for other vector types.
	
	//12.1.4
	{
		vec2 u(1.0, 0.0);
		vec3 v(2.0, 1.0, 0.0);
		vec4 w(3.0, 2.0, 1.0, 0.0);

		float l = length(u);

		float l = length(v);

		float l = length(w);

	}

	//12.1.5
	{
		vec2 m(1.0, 0.0);
		vec3 n(2.0, 1.0, 0.0);
		vec4 o(3.0, 2.0, 1.0, 0.0);

		vec2 a = normalize(m);
		vec3 b = normalize(n);
		vec4 c = normalize(o);

	}

	//12.1.6
	{
		vec2 u(1.0, 0.0);
		vec2 v(1.0, 2.0);
		vec3 w(2.0, 1.0, 0.0);
		vec3 x(1.0, 1.0, 0.0);
		vec4 y(3.0, 2.0, 1.0, 0.0);
		vec4 z(2.0, 1.0, 1.0, 0.0);

		float d = dot(u, v);
		float e = dot(w, x);
		float f = dot(y, z);
	}
	//12.1.7
	{

		vec3 u(1.0, 1.0, 0.0);
		vec3 v(1.0, 0.0, 0.0);

		vec3 c = cross(u, v);

	}
	//12.2
	{

	}
}