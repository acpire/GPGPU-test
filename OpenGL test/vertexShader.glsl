R"===(
	#version 330 core

    in vec3 positions;
	in vec3 normals;
	in vec3 texture;
	in vec3 colors;

	uniform vec3 lightPosition;
	uniform mat4 windowMatrix;
	uniform mat4 projectionMatrix;
	uniform mat4 modelMatrix;

	out vec3 _fragPosition;
	out vec3 _lightPosition;
	out vec3 _normal;
	out vec3 outColor;

	void main(){
		outColor = colors;
		_normal = normals;
	    _fragPosition = vec3( projectionMatrix * vec4(positions, 1.0f));
		_lightPosition = lightPosition;
		gl_Position =  modelMatrix * windowMatrix *  vec4(_fragPosition, 1.0f);
	}



)==="