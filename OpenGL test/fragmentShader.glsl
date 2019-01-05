R"===(

#version 430 compatibility

	in vec4 _fragPosition;
	in vec3 _lightPosition;
	in vec3 _normal;
	in vec3 outColor;
	in vec2 _textures;
	
	uniform sampler2D mainTexture;

	void main(){

		float ambientStrength = 0.2;
		vec3 ambient = ambientStrength * vec3(1.0f, 1.0f, 1.0f);

		vec3 norm = normalize(_normal);
		vec3 lightPosition = normalize(_lightPosition - vec3(_fragPosition));
		float diff = max(dot(norm, lightPosition), 0.0);
		vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

		vec3 result = (ambient + diffuse) * outColor;

		gl_FragColor = vec4(result, 1.0f) * texture(mainTexture, _textures);;
	}

)==="