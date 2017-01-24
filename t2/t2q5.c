#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double euclid_dist(int x1, int y1, int x2, int y2);

int main(void){
	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	for(int i = 0 ; i < 10 ; i++){
		int x1 = rand() % 101;
		int x2 = rand() % 101;
		int y1 = rand() % 101;
		int y2 = rand() % 101;
		double e_dist = euclid_dist(x1, y1, x2, y2);
		printf("%d %d %d %d %f\n", x1, y1, x2, y2, e_dist);
	}
}

double euclid_dist(int x1, int y1, int x2, int y2){
	return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}