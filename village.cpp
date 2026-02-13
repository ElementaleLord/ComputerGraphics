#include <GL/glut.h>

class point{ 
    public:
        GLfloat x, y;
        point(GLfloat x,GLfloat y){
            this->x= x;
            this->y= y;
        }
    };
class color{ 
    public:
        GLfloat r,g,b;
        color(GLfloat r, GLfloat g, GLfloat b){
            this->r= r;
            this->g= g;
            this->b= b;
        }
};

void init(void){
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void drawHouse(point peak, GLfloat width, GLfloat height, color c){
    // house color
    glColor3f(c.r, c.g, c.b);
    
    //~ house base
    // bottom line of house square
    glVertex2f(peak.x, peak.y);
    glVertex2f(peak.x+ width, peak.y);
    // right line of house square
    glVertex2f(peak.x+ width, peak.y);
    glVertex2f(peak.x+ width, peak.y+ height);
    // left line of house square
    glVertex2f(peak.x, peak.y+ height);
    glVertex2f(peak.x, peak.y);

    //~ roof
    // top line of house square / bottom line of roof triangle
    glVertex2f(peak.x+ width, peak.y+ height);
    glVertex2f(peak.x, peak.y+ height);
    // left side of roof triangle
    glVertex2f(peak.x, peak.y+ height);
    glVertex2d(peak.x+ width* 0.5, peak.y+ height* 1.7);
    // right side of roof triangle
    glVertex2f(peak.x+ width,   peak.y+ height);
    glVertex2d(peak.x+ width* 0.5, peak.y+ height* 1.7);

    //~door
    // left side of door
    glVertex2f(peak.x+ width*0.2, peak.y);
    glVertex2f(peak.x+ width*0.2, peak.y+ height* 0.5);
    // right side of door
    glVertex2f(peak.x+ width*0.4, peak.y);
    glVertex2f(peak.x+ width*0.4, peak.y+ height* 0.5);
    // top of door
    glVertex2f(peak.x+ width*0.2, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.4, peak.y+ height* 0.5);

    //~ window
    // bottom side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.25);
    // left side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.5);
    // right side of window
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.5);
    // top side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.5);
    // horizontal bar of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.375);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.375);
    // vertical bar of window
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 0.25);

    //~ Chimney
    // left side  of chimney
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 1.42);
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 1.6);
    // right side of chimney
    glVertex2f(peak.x+ width*0.9, peak.y+ height* 1.14);
    glVertex2f(peak.x+ width*0.9, peak.y+ height* 1.6);
    // top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.6);
    // left side of top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.65);
    // right side of top of chimney
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.65);
    // true top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.65);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.65);
}

void drawVillage(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    drawHouse({ 70, 210},    5,   5, {1.0, 1.0, 1.0});// very far white house
    drawHouse({170, 210},   10,  10, {1.0, 0.0, 1.0});// far-far purple house
    drawHouse({ 20, 170},   20,  20, {1.0, 0.0, 0.0});// far red house
    drawHouse({110, 150},   40,  40, {1.0, 1.0, 0.0});// far-middle yellow house
    drawHouse({230, 100},   60,  60, {0.0, 1.0, 0.0});// middle green house
    drawHouse({140,  50},   80,  80, {0.0, 1.0, 1.0});// close-middle cyan house
    drawHouse({ 10,  10},  100, 100, {0.0, 0.0, 1.0});// close blue house

    glEnd();
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutInitWindowPosition(200, 50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("GL Village");

    init();

    glutDisplayFunc(drawVillage);
    glutMainLoop();

    return 0;
}