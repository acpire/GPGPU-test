
__kernel void convolution4(__global uchar* image, __constant uint width, __constant uint height, __constant uint depth,
						__global float* kernel, __constant uint widthKernel, __constant uint heightKernel, __constant uint depthKernel){
		
		__global uchar4* ptrImage = image;
		__global float4* ptrKernel = kernel;
		uint pitchWidth = depth * width;
		uint residue = pitchWidth % 4;
		uint stepsWidth = pitchWidth >> 2;
		uint pitchWidthKernel = widthKernel * depthKernel;
		uint residueKernel = pitchWidthKernel % 4;
		uint stepsWidthKernel = pitchWidthKernel >> 2;
		int stepsPartWidthKernel = pitchWidthKernel >> 1;
		int partHeightKernel = heightKernel >> 1;
		float4 readKernel;
		float4 readImage;
		for (uint h = 0; h < height; h++){
			for (uint w = 0; w < stepsWidth; w++){
				for (uint i = 0; i < heightKernel; i++){
					for (uint j = 0; j < stepsWidthKernel; j++){
						int indexImageY = h - stepsPartWidthKernel  + i;
						int indexImageX = w - partHeightKernel  + j;
						readImage = convert_float4(ptrImage[ indexImageY < 0 || indexImageY > height] || indexImageX < 0 || indexImageX > stepsWidth ? h * stepsWidth + w :  indexImageY * stepsWidth + indexImageX] ); 
						readKernel = ptrKernel[ i * stepsWidthKernel + j ];
					}
				}
			}
		}
							
						
	
}