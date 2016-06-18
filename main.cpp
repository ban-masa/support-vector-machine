#include "lib.h"

#define W 320
#define H 240

std::vector<struct pt> stuck;

SVM svm;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
    struct pt temp;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                temp.val[0] = (double)x/W;
                temp.val[1] = (double)y/H;
                temp.val[2] = 1;
                temp.type = 1.0;
                svm.data.push_back(temp);
                temp.val[0] = x;
                temp.val[1] = y;
                stuck.push_back(temp);
                glPointSize(5);
                glColor3d(1.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                glFlush();
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            std::cout << "x = " << x << " y = " << y << std::endl;
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                temp.val[0] = (double)x/W;
                temp.val[1] = (double)y/H;
                temp.val[2] = 1;
                temp.type = -1.0;
                svm.data.push_back(temp);
                temp.val[0] = x;
                temp.val[1] = y;
                stuck.push_back(temp);

                glPointSize(5);
                glColor3d(0.0, 1.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                glFlush();
            }
            break;
        default:
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    double tmp[2];
    double min_margin = 1000;
    switch (key) {
        case 'q':
        case 'Q':
            exit(0);
        case 'a':
            svm.study(MAX);
            break;
        case 'b':
            glPointSize(1);
            for (int i = 0; i < W; i++) {
                for (int j = 0; j < H; j++) {
                    tmp[0] = (double)i/W;
                    tmp[1] = (double)j/H;
                    glBegin(GL_POINTS);
                    if (svm.output(tmp) > -0.05 && svm.output(tmp) < 0.05) {
                        glColor3d(0.0, 0.0, 0.0);
                    } else {
                        glColor3d(1.0, 1.0, 1.0);
                    }
                    glVertex2i(i, j);
                    glEnd();
                }
            }
            glPointSize(5);
            for (int i = 0; i < stuck.size(); i++) {
                glBegin(GL_POINTS);
                if (stuck[i].type == 1.0) {
                    glColor3d(1.0, 0.0, 0.0);
                } else if (stuck[i].type == -1.0) {
                    glColor3d(0.0, 1.0, 0.0);
                }
                glVertex2i(stuck[i].val[0], stuck[i].val[1]);
                glEnd();
            }
            glFlush();
            break;
        case 'c':
            for (int j = 0; j < 1000; j++) {
                svm.study(10);
                min_margin = 1000;
                for (int i = 0; i < svm.data.size(); i++) {
                    double margin = svm.calc_margin(svm.data[i]);
                    if (margin < min_margin) {
                        min_margin = margin;
                    }
                }
                std::cout << min_margin << std::endl;
            }
            break;
        case 'd':
            svm.show_param();
            break;
        default:
            break;
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    std::cout << "Left click -> Red dot" << std::endl;
    std::cout << "Right click -> Green dot" << std::endl;
    std::cout << "Press a key to study" << std::endl;
    std::cout << "Press b key to show result" << std::endl;
    std::cout << "Press c key to study 10000 and show margin" << std::endl;
    std::cout << "Press d key to show param" << std::endl;
    std::cout << "Press q key to quit" << std::endl;
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W, H);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}

