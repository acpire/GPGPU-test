R"===(
#version 430 compatibility

    in vec3 positions;
	in vec3 normals;
	in vec2 texture;
	in vec3 colors;

	//uniform vec3 lightColor
	uniform vec3 lightPosition;
	uniform mat4 windowMatrix;
	uniform mat4 projectionMatrix;
	uniform mat4 modelMatrix;

	out vec4 _fragPosition;
	out vec3 _lightPosition;
	out vec3 _normal;
	out vec3 outColor;
	out vec2 _textures;

	void main(){
		outColor = colors;
		_textures = texture;
		_normal = normals;
		_lightPosition = lightPosition;
	    _fragPosition =  projectionMatrix * vec4(positions, 1.0f);
		gl_Position =  projectionMatrix * modelMatrix  * windowMatrix *   vec4(positions, 1.0f);
	}



)==="