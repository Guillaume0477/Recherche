#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <iostream>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



int main() {

	int W, H, C;
	
	//stbi_set_flip_vertically_on_load(true);
	unsigned char *image1 = stbi_load("8733654151_b9422bb2ec_k.jpg",
                                 &W,
                                 &H,
                                 &C,
                                 STBI_rgb);
	std::vector<double> image_double1(W*H*3);
	for (int i=0; i<W*H*3; i++)
		image_double1[i] = image1[i];

	unsigned char *image2 = stbi_load("redim.jpg",
                                 &W,
                                 &H,
                                 &C,
                                 STBI_rgb);
	std::vector<double> image_double2(W*H*3);
	for (int i=0; i<W*H*3; i++)
		image_double2[i] = image2[i];
	
	std::vector<std::pair<float,int>> projection_1(W*H); //pair projection indice 1
	std::vector<std::pair<float,int>> projection_2(W*H);



	for (int loop = 0; loop < 10; loop++){


	double u,v,w;
	u = (float) rand()/RAND_MAX -0.5;
	v = (float) rand()/RAND_MAX -0.5;
	w = (float) rand()/RAND_MAX -0.5;

	u = u/sqrt(pow(u,2)+pow(v,2)+pow(w,2));
	v = v/sqrt(pow(u,2)+pow(v,2)+pow(w,2));
	w = w/sqrt(pow(u,2)+pow(v,2)+pow(w,2));

	std::cout<<u<<" , "<<v<<" , "<<w<<std::endl;


		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {

				projection_1[(i*W + j)] = std::pair<float,int>(image_double1[(i*W+j)*3+0]*u+image_double1[(i*W+j)*3+1]*v+image_double1[(i*W+j)*3+2]*w,i*W + j);
				projection_2[(i*W + j)] = std::pair<float,int>(image_double2[(i*W+j)*3+0]*u+image_double2[(i*W+j)*3+1]*v+image_double2[(i*W+j)*3+2]*w,i*W + j);


				/*image_result[(i*W + j) * 3 + 1] = image_double1[(i*W+j)*3+1];
				image_result[(i*W + j) * 3 + 2] = image_double1[(i*W+j)*3+2];


				image_result[(i*W + j) * 3 + 0] = image_double2[(i*W+j)*3+0];
				image_result[(i*W + j) * 3 + 1] = image_double2[(i*W+j)*3+1];
				image_result[(i*W + j) * 3 + 2] = image_double2[(i*W+j)*3+2];*/
			}
		}
		std::sort(projection_1.begin(),projection_1.end());
		std::sort(projection_2.begin(),projection_2.end());


		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				//(projection_2(i*W + j)-projection_1(i*W + j))*[u,v,w];
				//std::cout<<projection_1[(i*W + j)]<std::endl<;
				
				image_double1[(projection_1[(i*W + j)].second) *3 + 0] += u * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first);
				image_double1[(projection_1[(i*W + j)].second) *3 + 1] += v * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first);
				image_double1[(projection_1[(i*W + j)].second) *3 + 2] += w * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first);

/*
				std::cout<<u * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<v * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<w * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<std::endl;
				std::cout<<u * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<v * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<w * (projection_2[(i*W + j)].first-projection_1[(i*W + j)].first)<<std::endl;
				std::cout<<std::endl;
				std::cout<<std::endl;
				*/

				//image_double1[projection_1(i*W + j).second ] = image_double2[(i*W+j)*3+1];
				//image_double1[projection_1(i*W + j).second ] = image_double2[(i*W+j)*3+2];
			}
		}

	}


	std::vector<unsigned char> image_result(W*H * 3, 0);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			image_result[(i*W + j) * 3 + 0] = image_double1[(i*W+j)*3+0];
			image_result[(i*W + j) * 3 + 1] = image_double1[(i*W+j)*3+1];
			image_result[(i*W + j) * 3 + 2] = image_double1[(i*W+j)*3+2];
		}
	}
	stbi_write_png("image_result.png", W, H, 3, &image_result[0], 0);




	return 0;
}