#include"windoww.h"
int main(int argv, char** argc) {
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(0, 0);
    int base = glutCreateWindow("Do thi vo huong Nhom 7");
    Init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyReleased);
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);
    glutMouseFunc(mouseClick);
    
    glutInitWindowSize(W2, H2); // Kích thước cửa sổ thứ hai
    glutInitWindowPosition(100, 100); // Vị trí cửa sổ thứ hai
    int secondWindow = glutCreateWindow("Ma tran");
    Init2();
    glutDisplayFunc(display2);
    glutMainLoop();

}

