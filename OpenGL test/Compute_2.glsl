R"===(

#version 440 core
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_image_load_store : enable

layout (binding = 0, rgba32f) uniform readonly image2D Image_read;
layout (binding = 1, rgba32f) uniform writeonly image2D Image_write;
uniform vec2 workSize;
uniform float F;

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
 
void main(void)
{	
	vec2 work = workSize;
	if ( gl_GlobalInvocationID.x >  work.x  ||  gl_GlobalInvocationID.y >  work.y )
		return;
	work /= 2;
	vec2 xy = gl_GlobalInvocationID.xy - work;
	xy /= work;
	vec2 vector = xy * xy;
	float radius = sqrt(vector.x + vector.y);
	const float b = 1.0f;
	const float _F = F;
	vec2 true_image = b * xy;
	vec2 dist_image = true_image + _F * pow(radius, 2) * xy;

	dist_image /= b;
	dist_image *= work;
	dist_image += work;

	
    ivec2 position_read = ivec2(dist_image);
	vec4 rgba = imageLoad(Image_read, position_read);

	ivec2 position_write = ivec2(gl_GlobalInvocationID.xy);
	imageStore(Image_write, position_write, rgba);

}
)==="