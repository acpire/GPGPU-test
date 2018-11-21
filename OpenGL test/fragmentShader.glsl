R"===(

	#version 330 core

	in vec3 _fragPosition;
	in vec3 _lightPosition;
	in vec3 _normal;
	in vec3 outColor;

	void main(){
		vec3 norm = normalize(_normal);
		vec3 lightPosition = normalize(_lightPosition - _fragPosition);
		float diff = max(dot(norm, lightPosition), 0.0);
		vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

		vec3 result = diffuse * outColor;

		gl_FragColor = vec4(result, 1.0f);
		//gl_FragColor = vec4(outColor, 1.0f);
	}

)==="