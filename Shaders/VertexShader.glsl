#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normala;
layout(location = 2) in vec2 v_text_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform float mouseLeft;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normala;
out vec2 frag_coord;
out vec3 frag_color;

void main()
{
	// TODO: send output to fragment shader
	frag_position = v_position;
	frag_normala = v_normala;
	frag_coord = v_text_coord;
	frag_color = v_color;

	// TODO: compute gl_Position
	if (mouseLeft == 1) {
		//if (cos(time) < 0) {
			//gl_Position = Projection * View * Model * vec4(v_position + vec3(0, 0, -cos(time)), 1.0);
		//} else {
			gl_Position = Projection * View * Model * vec4(v_position + vec3(0, 0, cos(time)), 1.0);
		//}
	} else {
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	}
}
