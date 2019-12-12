#include <stdio.h>
#include <stdlib.h>

/*
	*Gift wrapping algorithm (Jarvis March) for computing the convex hull
	*Author: Sarker Nadir Afridi Azmi, Sophomore, UTA
	*Reference: Introduction to Algorithms - 3rd Edition
	*This algorithm was my Honors Project for CSE2320 - Algorithms and Data Structures at The University of Texas at Arlington (Fall 2019)
	*Instructor: Dr. Alexandra Stefan - http://vlm1.uta.edu/~alex/
*/

//struct to store coordinates
typedef struct points
{
	int x;
	int y;
} points;

//struct for a linked list which will be used to store the outer most points of the convex hull
typedef struct node
{
	points coorodinate;
	struct node *next;
} node;

//this function compares the y coordinates
int compare_coordinates_y(points points_array, points pivot)
{
	if(points_array.y <= pivot.y)
	{
		return 1;
	}
}

//this function compares the x coordinates
int compare_coordinates_x(points points_array, points pivot)
{
	if(points_array.x <= pivot.x)
	{
		return 1;
	}
}

//this function swaps two values in an array
void swap(points *points_array, int idx1, int idx2)
{
	points temp = points_array[idx1];
	points_array[idx1] = points_array[idx2];
	points_array[idx2] = temp;
}

//partition function for quick sort
int partition(points *points_array, int start, int end, int compare_coordinates(points, points))
{
	points pivot = points_array[end];
	int t = start;
	int j = 0;
	for(j = start; j <= end - 1; j++)
	{
		if(compare_coordinates(points_array[j], pivot) == 1)
		{
			swap(points_array, j, t);
			t++;
		}
	}
	swap(points_array, t, end);
	return t;
}

//Quick sort
//time complexity: NlgN
void QSort(points *points_array, int start, int end, int compare_coordinates(points, points))
{
	if(start >= end) 
		return;
	int pivot = partition(points_array, start, end, compare_coordinates);
	QSort(points_array, start, pivot - 1, compare_coordinates);
	QSort(points_array, pivot + 1, end, compare_coordinates);
}

//this function computes the cross product
int cross_product(points p0, points p1, points p2)
{
	//formula: (p1 - p0) X (p2 - p0)
	//if p1p0 is our current vector, if negative is returned, then the segment p1p0 is to the right of p2p0
	//if p1p0 is our current vector, if positive is returned, then the segment p1p0 is to the left of p2p0
	return (p1.x-p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

//this function adds a node to a linked
void add_node(node **head, points point)
{
	node *NewNode, *TempPtr;
	NewNode = malloc(sizeof(node));
	NewNode->coorodinate = point;
	NewNode->next = NULL;
	
	if(*head == NULL)
		*head = NewNode;
	else
	{
		TempPtr = *head;
		while(TempPtr->next != NULL)
			TempPtr = TempPtr->next;
		
		TempPtr->next = NewNode;
	}
}

//this function prints the linked list
void print_list(node *head)
{
	FILE *fp = fopen("outerpoints.txt", "w");
	node *temp = head;
	while(temp != NULL)
	{
		printf("(%d, %d)\n", temp->coorodinate.x, temp->coorodinate.y);
		fprintf(fp, "%d,%d\n", temp->coorodinate.x, temp->coorodinate.y);
		temp = temp->next;
	}
	fclose(fp);
}

//this function deletes the entire linked list
void delete_linked_list(node *head)
{
    node *current_node, *next_node;
	current_node = head;
	
	while(current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
}

//this functions computes the distance between two points and returns the coordinates that gives the greater distnace from a fixed point
//let us say that the fixed point is p0, and the distances calculated are p0p1 and p0p2
//the coordinates which give the greater distance are going to be returned
points distance(points p0, points p1, points p2)
{
	//distance squared between p1 (x1, y1) and p0 (x0, y0)
	int d1 = (p1.x - p0.x)*(p1.x - p0.x) + (p1.y - p0.y)*(p1.y - p0.y);
	int d2 = (p2.x - p0.x)*(p2.x - p0.x) + (p2.y - p0.y)*(p2.y - p0.y);
	
	if(d1 < d2)
		return p2;
	else
		return p1;
}

int main()
{
	int number_of_points;
	scanf("%d", &number_of_points);
	points *input_pts = malloc(number_of_points*sizeof(points));
	
	FILE *fp = fopen("all_points.txt", "w");
	
	int scanf_flag = 0;
	int i = 0;
	for(i = 0; scanf_flag != -1; i++)
	{
		scanf_flag = scanf("%d %d", &input_pts[i].x, &input_pts[i].y);
	}
	
	int j = 0;
	for(j = 0; j < number_of_points; j++)
	{
		fprintf(fp, "%d,%d\n", input_pts[j].x, input_pts[j].y);
	}
	
	fclose(fp);
	
	//sort the array of points in ascending order
	//the reason for sorting this twice is so that I can get the left corner
	QSort(input_pts, 0, number_of_points-1, compare_coordinates_y);
	//QSort(input_pts, 0, number_of_points-1, compare_coordinates_x);
	//neg right of reference points
	//pos left of reference points
	
	//lowest point found by sorting
	points start_point = input_pts[0];
	node *head = NULL;
	add_node(&head, start_point);
	points current_point = input_pts[0]; //let's say current point is 1,1
	points prev_selected_coordinate;
	
	while(1)
	{
		int idx = 1;
		points assumed_right_point = input_pts[idx];
		//if the assumed_right_point happens to match our current point, we change it to another point
		if(assumed_right_point.x == current_point.x && assumed_right_point.y == current_point.y)
		{
			assumed_right_point = input_pts[idx + 1];
		}
		for(i = 0; i < number_of_points; i++)
		{
			//as long as our current point != input_pts[i]
			if((input_pts[i].x != current_point.x || input_pts[i].y != current_point.y) && (input_pts[i].x != assumed_right_point.x || input_pts[i].y != assumed_right_point.y))
			{
				int cross_product_result = cross_product(current_point, assumed_right_point, input_pts[i]);
				//this suggests that our vector is to the right of the current vector and we update the point
				if((cross_product_result < 0))
				{
					assumed_right_point = input_pts[i];
				}
				else if(cross_product_result == 0)
				{
					assumed_right_point = distance(current_point, assumed_right_point, input_pts[i]);
					//the problem is, after finding 2, 0, I need some way to remove this from my array
				}
			}
		}
		
		current_point = assumed_right_point;

		if(current_point.x == start_point.x && current_point.y == start_point.y)
		{
			break;
		}
		add_node(&head, current_point);
	}
	
	print_list(head);
	delete_linked_list(head);
	free(input_pts);
	
	return 0;
}
