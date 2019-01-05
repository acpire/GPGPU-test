R"===(

#version 430 compatibility
#extension GL_ARB_compute_shader : enable

uniform vec2 workSize;
uniform vec2 factors;
uniform float multiply;

layout(std430) buffer Positions 
{
    float position [];
};

 
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
 
 
 float factorial(float n){
	float last_n = n;
	last_n--;
	while(last_n > 0.1f){
		n *= (last_n);
		last_n-=1.0f;
	}
	if (n > -0.00001f && n < 0.00001f)
		n = 1.0f;
	return n;
 }

 float radialPolynomials(float radius, float m, float n){
	m = abs(m);
	float N = int(n - m) / 2;
	float result = 0.0f;
	float k = 0.0f;
	do {
		result += ((pow(-1.0f, k) * factorial(n - k) /
			(factorial(k) * 	factorial((n + m) / 2.0f - k)  * factorial((n - m) / 2.0f - k)))) * pow(radius, n - 2.0f * k);
		k += 1.0f;
	} while (k < N);
	return result;
 }

 float coma(float x, float y){
 
	float angle = atan(y, x);
	float radius = sqrt(x * x + y * y);
	float coma = 2 * sqrt(2.0f) * (3.0f * pow(radius, 3) - 2 * radius) * sin(angle);
	return coma;
 }

 float ZernikePolynomials(float x, float y, float m, float n){
	float angle = atan(y, x);
	float radius = sqrt(x * x + y * y);
	if (m < 0.0f)
		return  radialPolynomials(radius, m, n) * sin(m * angle);
	else
		return  radialPolynomials(radius, m, n) * cos(m * angle);

 }

void main(void)
{	
	vec2 work = workSize;
	//work.x = 400;
	//work.y = 400;
	const int idx = int(gl_WorkGroupID.x * gl_WorkGroupSize.x + gl_LocalInvocationID.x);
	const int idy =  int(gl_WorkGroupID.y * gl_WorkGroupSize.y + gl_LocalInvocationID.y);
	if (idx > work.x || idy > work.y)
		return;
	int stride_x = int(work.x);
	work /= 2;
	float x = float(idx) - work.x;
	float y = float(idy) - work.y;
	x /= work.x;
	y /= work.y;

	uint index = idy * stride_x + idx;
	index *= 3;

	position[index + 2] = multiply * ZernikePolynomials(x, y, factors.x, factors.y);

    //position[index + 2] = coma(x , y);
 
 

}
)==="