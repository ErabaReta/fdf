#include <stdio.h>
#include "fdf.h"

typedef struct {
    float x, y, z;
} Point3D;

typedef struct {
    float x, y;
} Point2D;

// Define viewpoint
Point3D viewpoint = {0, 0, 0};

// Define projection matrix (simple perspective projection)
float projection_matrix[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

// Function to project a 3D point to a 2D point
Point2D projectPoint(Point3D point3d) {
    // Apply projection
    float x_proj = point3d.x * projection_matrix[0][0] + point3d.y * projection_matrix[1][0] + point3d.z * projection_matrix[2][0];
    float y_proj = point3d.x * projection_matrix[0][1] + point3d.y * projection_matrix[1][1] + point3d.z * projection_matrix[2][1];
    float z_proj = point3d.x * projection_matrix[0][2] + point3d.y * projection_matrix[1][2] + point3d.z * projection_matrix[2][2];

    // Normalize coordinates
    x_proj /= z_proj;
    y_proj /= z_proj;

    // Create 2D point
    Point2D point2d = {x_proj, y_proj};
    return point2d;
}

int main() {
    // Define 3D points
    Point3D points_3d[] = {{1, 1, 1}, {2, 3, 4}, {3, 2, 1}};
    int num_points = sizeof(points_3d) / sizeof(points_3d[0]);

    // Project and print 3D points
    printf("Projected 2D Points:\n");
    for (int i = 0; i < num_points; i++) {
        Point2D point2d = projectPoint(points_3d[i]);
        printf("(%f, %f)\n", point2d.x, point2d.y);
    }

    return 0;
}
