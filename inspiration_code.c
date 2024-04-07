#include <stdio.h>
// #include "fdf.h"

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


//==========================================================================================
// #include <stdio.h>
// #include <math.h>

// typedef struct {
//     float x, y, z;
// } Point3D;

// // Function to rotate a point around the X axis
// Point3D rotateX(Point3D point, float angle) {
//     float sinAngle = sin(angle);
//     float cosAngle = cos(angle);
//     Point3D rotatedPoint;
//     rotatedPoint.x = point.x;
//     rotatedPoint.y = point.y * cosAngle - point.z * sinAngle;
//     rotatedPoint.z = point.y * sinAngle + point.z * cosAngle;
//     return rotatedPoint;
// }

// // Function to rotate a point around the Y axis
// Point3D rotateY(Point3D point, float angle) {
//     float sinAngle = sin(angle);
//     float cosAngle = cos(angle);
//     Point3D rotatedPoint;
//     rotatedPoint.x = point.x * cosAngle + point.z * sinAngle;
//     rotatedPoint.y = point.y;
//     rotatedPoint.z = -point.x * sinAngle + point.z * cosAngle;
//     return rotatedPoint;
// }

// // Function to rotate a point around the Z axis
// Point3D rotateZ(Point3D point, float angle) {
//     float sinAngle = sin(angle);
//     float cosAngle = cos(angle);
//     Point3D rotatedPoint;
//     rotatedPoint.x = point.x * cosAngle - point.y * sinAngle;
//     rotatedPoint.y = point.x * sinAngle + point.y * cosAngle;
//     rotatedPoint.z = point.z;
//     return rotatedPoint;
// }

// int main() {
//     // Define a point
//     Point3D point = {1, 0, 0};

//     // Rotate around X axis by 45 degrees
//     point = rotateX(point, M_PI_4);

//     // Rotate around Y axis by 30 degrees
//     point = rotateY(point, M_PI / 6);

//     // Rotate around Z axis by 60 degrees
//     point = rotateZ(point, M_PI / 3);

//     printf("Rotated point: (%f, %f, %f)\n", point.x, point.y, point.z);

//     return 0;
}
