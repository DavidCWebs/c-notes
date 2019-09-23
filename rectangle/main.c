#include <stdio.h>
#include <stdlib.h>

typedef struct v {
	int x;
	int y;
} Vertex;

typedef struct p {
	size_t n_vertexes;
	Vertex *Vertexes;
} Polygon;

Polygon *makeRectangle(Vertex c1, Vertex c2) {
	Polygon *a = malloc(sizeof(*a));
	a->n_vertexes = 4;
	a->points = malloc(a->num_points * sizeof(*a->points));
//	printf("%lu\n", sizeof(*a->points) * a->num_points);
//	printf("%d, %d\n", c1.x, c2.x);
	

	return a;
//	polygon_t * answer = malloc(sizeof(*answer));
//	answer->num_points = 4;
//	answer->points = malloc(answer->num_points * sizeof(*answer->points));
//	answer->points[0]   = c1;
//	answer->points[1].x = c1.x;
//	answer->points[1].y = c2.y;
//	answer->points[2]   = c2;
//	answer->points[3].x = c2.x;
//	answer->points[3].y = c1.y;
//	return answer;
}

int main(void)
{
	point_t p1 = {2, 2};
	point_t p2 = {6, 4};
	polygon_t *myRect = makeRectangle(p1, p2);

	printf("vertex 1: %d, %d\n", myRect->points[1].x, myRect->points[1].y);
	printf("vertex 2: %d, %d\n", myRect->points[3].x, myRect->points[3].y);

	free(myRect->points);
	free(myRect);
	return 0;
}
