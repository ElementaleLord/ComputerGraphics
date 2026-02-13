#include <GL/glut.h> // Includes glu.h and gl.h

// Function to draw the scene
void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);     // Clear the color buffer (background)

    glBegin(GL_TRIANGLES);            // Begin drawing a triangle
    glColor3f(1.0, 0.0, 0.0);       // Set color to red
    glVertex2f(-0.8, -0.8);         // Define a vertex
    glColor3f(0.0, 1.0, 0.0);       // Set color to green
    glVertex2f(0.8, -0.8);          // Define a vertex
    glColor3f(0.0, 0.0, 1.0);       // Set color to blue
    glVertex2f(0.0, 0.9);           // Define a vertex
    glEnd();                          // End drawing the triangle

    glFlush();                        // Flush drawing command buffer to make drawing happen
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);                    // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single color buffer and RGB color mode
    glutInitWindowSize(500, 500);             // Set the window size
    glutInitWindowPosition(100, 100);         // Set the window position
    glutCreateWindow("GL RGB Triangle");      // Create window with a title
    glutDisplayFunc(display);                 // Register the display function
    glutMainLoop();                           // Enter the event-processing loop

    return 0;
}
