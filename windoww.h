//
// Created by Admin on 10/3/2023.
//
//check
#include<Windows.h>
#include<stdlib.h>
#include<GL/glut.h>

#include "Undirected Floyd.h"
#include<string>
#include <sstream>
#include"Undirected euler.h"
#include"Undirected dijkstra.h"
#include"Undirected hamilton.h"
#include"Floyd-DijkstraMiniGame.h"
using namespace std;
//FloydMiniGame* mini = new FloydMiniGame(make_pair<int,int>(20,20));
#pragma once
//keyboard
bool isUPKeyPressed;
bool isDOWNKeyPressed;
bool isEnterKeyPressed;
bool isLEFTKeyPressed;
bool isRIGHTKeyPressed;
bool input = false;
string inputText = "";
//mouse
double mouseX = 0;
double mouseY = 0;
bool basemenu = true;
int bchoice = 1;
int choicetxt = 1;
//size of window
double H = 600;
double W = 1500;
double H2 = 500;
double W2 = 600;
//(x,y) start cout
int starttextX = -340;
int starttextY = 200;

//check the completion of matrix.
bool InputData = false;

int totaltxtfile = 4;
//index of matrix
int valuenxn = 0;

//value check in display's choice
int isindis = 0;
bool check_Undirected_graph = 0;
//value check the completion of input
bool checkinputsize = false;

//scroll
int scroll = 0;
int rowss = 0;

void drawRectangle(float x1, float y1, float x2, float y2);
void drawBOX(float x1, float y1, float x2, float y2, float color1, float color2, float color3, string n, bool centerText);
void renderBitmapString(float x, float y, void* font, string string1);

void Init();
void reshape(int width, int height);
void display2();
void display();
void basedisplay();
void dischoice1();
void dischoice2();
void dischoice3();
void dischoice4();
void dischoice5();
void dischoice6();
void dischoice7();
void dischoice8();
void dischoice9();
void handleSpecialKeypress(int key, int x, int y);
void handleSpecialKeyReleased(int key, int x, int y);
void handleKeyPress(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void handleClick(int x, int y);
void mouseMotion(int x, int y);

void drawRectangle(float x1, float y1, float x2, float y2)
{
    glColor3f(0.5, 0.5, 1);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP); // Bắt đầu vẽ đường viền
    glVertex2f(x1 - 1, y1 + 1);    // Đỉnh trái dưới
    glVertex2f(x2 + 1, y1 + 1);    // Đỉnh phải dưới
    glVertex2f(x2 + 1, y2 - 1);    // Đỉnh phải trên
    glVertex2f(x1 - 1, y2 - 1);    // Đỉnh trái trên
    glEnd();               // Kết thúc vẽ đường viền
}
void drawBOX(float x1, float y1, float x2, float y2, float color1, float color2, float color3, string n, bool centerText)
{
    glColor3f(color1, color2, color3);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
    float rectWidth = x2 - x1;
    float rectHeight = y2 - y1;
    float charWidth = 9.0f;
    int charsPerLine = static_cast<int>(rectWidth / charWidth);
    for (int i = 0; i < n.length(); i += charsPerLine)
    {
        string line = n.substr(i, charsPerLine);

        // Tính toán vị trí x cho văn bản
        float textX;
        if (centerText)
        {
            float lineWidth = line.length() * charWidth;
            textX = x1 + (rectWidth - lineWidth) / 2.0f;
        }
        else
        {
            textX = x1;
        }

        // In chuỗi line tại vị trí (textX, y1)
        renderBitmapString(textX, y1 - 18, GLUT_BITMAP_HELVETICA_18, line);
        // Xuống dòng
        y1 -= 20;
    }
    glFlush();
}void renderBitmapString(float x, float y, void* font, string string1,int a,int b,int c)
{
    glColor3f(a, b, c);
    glRasterPos2f(x, y);
    for (char c : string1)
    {
        glutBitmapCharacter(font, c);
    }
}
void renderBitmapString(float x, float y, void* font, string string1)
{
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    for (char c : string1)
    {
        glutBitmapCharacter(font, c);
    }
}
void Init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-W / 2, W / 2, -H / 2, H / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Init2()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-W2 / 2, W2 / 2, -H2 / 2, H2 / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void reshape(int width, int height)
{
    glutReshapeWindow(W, H);
}
void display2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x = -300;
    int y = 230;
    if (!dmatrix.empty()) {

        int n = dmatrix.size();
        // Xây dựng chuỗi thông tin kích thước
        stringstream sizeInfo;
        sizeInfo << "Ma tran " << n << " x " << n << " :";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;
        // Hiển thị ma trận
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                stringstream ss;
                ss << setw(4) << setfill(' ') << dmatrix[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
            x = -300; // Đặt lại x về giá trị ban đầu
            y -= 20; // Di chuyển xuống hàng tiếp theo
        }
        y = 230;
    }
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    basedisplay();
    if (basemenu == true)
    {
        switch (bchoice)
        {
        case 1:drawRectangle(-600, 220, -400, 190); break;
        case 2:drawRectangle(-600, 170, -400, 140); break;
        case 3:drawRectangle(-600, 120, -400, 90); break;
        case 4:drawRectangle(-600, 70, -400, 40); break;
        case 5:drawRectangle(-600, 20, -400, -10); break;
        case 6:drawRectangle(-600, -30, -400, -60); break;
        case 7:drawRectangle(-600, -80, -400, -110); break;
        case 8:drawRectangle(-600, -130, -400, -160); break;
        case 9:drawRectangle(-600, -180, -400, -210); break;
        case 10:drawRectangle(-600, -230, -400, -260); break;
        }
    }
    else
    {
        switch (bchoice)
        {
        case 1:
            dischoice1();
            break;
        case 2:dischoice2();
            break;
        case 3: dischoice3(); break;
        case 4: dischoice4(); break;
        case 5: dischoice5(); break;
        case 6: dischoice6(); break;
        case 7: dischoice7(); break;
        case 8: dischoice8(); break;
        case 9: dischoice9(); break;
        }
    }
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}
void basedisplay()
{
    ostringstream streamX, streamY;
    streamX << fixed << setprecision(0) << mouseX;
    streamY << fixed << setprecision(0) << mouseY;
    string mouseCoord = "PosMouse: (" + streamX.str() + ", " + streamY.str() + ")";
    drawBOX(-670, 270, 670, -270, 1, 1, 0.5, "", 0);//
    drawRectangle(-670, 270, 670, -270);
    drawBOX(-670, 270, -550, 230, 0, 0, 1, "Cre:Nhom 7", 1);//nhom
    drawBOX(-530, 270, -270, 230, 0, 0, 1, "Click or ESC to return menu", 1);//
    drawBOX(-250, 270, -50, 230, 0, 0, 1, mouseCoord, 1);//n
    drawBOX(-40, 270, 500, 230, 0, 0, 1, "MAX MATRIX la 19x19,dung phim mui ten va chuot de thao tac", 1);//n
    drawBOX(-600, 220, -400, 190, 0, 0, 1, "Nhap FIle", 1);//1
    drawBOX(-600, 170, -400, 140, 0, 0, 1, "Nhap thu cong", 1);//2
    drawBOX(-600, 120, -400, 90, 0, 0, 1, "F-Duong di ngan nhat", 1);//3
    drawBOX(-600, 70, -400, 40, 0, 0, 1, "F-Truy vet", 1);//4
    drawBOX(-600, 20, -400, -10, 0, 0, 1, "DIJKSTRA", 1);//5
    drawBOX(-600, -30, -400, -60, 0, 0, 1, "Chu trinh EULER", 1);//6
    drawBOX(-600, -80, -400, -110, 0, 0, 1, "Duong di EULER", 1);//7
    drawBOX(-600, -130, -400, -160, 0, 0, 1, "MazeGame", 1);//8
    drawBOX(-600, -180, -400, -210, 0, 0, 1, "Duong di HAMLTON", 1);//9
    drawBOX(-600, -230, -400, -260, 0, 0, 1, "Dung chuong trinh", 1);//10
    drawBOX(-350, 220, 600, -260, 0, 0, 0, "", 0);//
    if (InputData) {
        if (basemenu)
        {
            int x = starttextX;
            int y = starttextY;
            if (!dmatrix.empty()) {

                int n = dmatrix.size();
                // Xây dựng chuỗi thông tin kích thước
                stringstream sizeInfo;
                sizeInfo << "Ma tran " << n << " x " << n << " :";
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
                y -= 20;
                // Hiển thị ma trận
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        // Định dạng chuỗi ký tự trước khi in ra
                        stringstream ss;
                        ss << setw(4) << setfill(' ') << dmatrix[i][j];
                        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                        x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
                    }
                    x = starttextX; // Đặt lại x về giá trị ban đầu
                    y -= 20; // Di chuyển xuống hàng tiếp theo
                }
                y = starttextY;
            }
        }
    }
}
void dischoice1()
{
    drawBOX(430, -230, 600, -260, 0, 0, 1, "CONFIRM MATRIX", 0);
    drawBOX(240, -230, 340, -260, 0, 0, 1, "PREVIOUS", 0);
    drawBOX(360, -230, 410, -260, 0, 0, 1, "NEXT", 0);
    drawRectangle(-600,220,-400,190);
    string choice = to_string(choicetxt);
    string filename;
    filename = "vidu" + choice + ".txt";
    int starty = starttextY;
    for (int i = 0; i < totaltxtfile; i++)
    {
        string filenam = "vidu" + to_string(i + 1) + ".txt";
        renderBitmapString(starttextX, starty, GLUT_BITMAP_HELVETICA_18, filenam);
        starty -= 20;
    }
    matrixxx = readMatrixFromFile(filename);
    check_Undirected_graph=isUndirected(matrixxx);
    drawBOX(-340, -230, -50, -260, 0, 0, 0, "Moi chon file de doc:", 0);
    drawBOX(-340 + 180, -230, -50 + 180, -260, 0, 0, 0, filename, 0);

    int x = starttextX + 100;
    int y = starttextY;
    if (!matrixxx.empty()) {
        int n = matrixxx.size();
        stringstream sizeInfo;
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "LUU Y: Do thi vo huong");
        y -=20;
        sizeInfo << "Ma tran " << n << " x " << n << " cua " << filename << ":";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                stringstream ss;
                ss << setw(4) << setfill(' ') << matrixxx[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30;
            }
            x = starttextX + 100;
            y -= 20;
        }

        y = starttextY;
    }

}
void dischoice2() {
    drawRectangle(-600, 170, -400, 140);
    if (input) {
        int x = starttextX;
        int y = starttextY;
        if (tmpnn < 1) {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap so dinh: ");
            renderBitmapString(x + 150, y, GLUT_BITMAP_HELVETICA_18, inputText);
        }
        if (tmpnn > 0) {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap so dinh: ");
            renderBitmapString(x + 150, y, GLUT_BITMAP_HELVETICA_18, to_string(nn));
            y -= 20;
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "LUU Y: Do thi vo huong");
            checkinputsize = true;
            int i = (valuenxn) / nn;
            int j = (valuenxn) % nn;
            stringstream a;
            if (i == nn) {
                a << "Moi nhap gia tri matrix[" << nn - 1 << "][" << nn - 1 << "] :";
                drawBOX(-340, -230, -50, -260, 0, 0, 0, a.str(), 0);
            }
            else {
                a << "Moi nhap gia tri matrix[" << i << "][" << j << "] :"; // Sử dụng giá trị của ma trận thay vì inputText
                drawBOX(-340, -230, -50, -260, 0, 0, 0, a.str(), 0);
                renderBitmapString(-100, -250, GLUT_BITMAP_HELVETICA_18, inputText);
            }
            if (!matrixx.empty())
            {
                stringstream sizeInfo;
                sizeInfo << "Ma tran " << nn << " x " << nn << " :";
                renderBitmapString(x, y - 20, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
                y -= 40;
                for (int i = 0; i < nn; ++i) {
                    for (int j = 0; j < nn; ++j) {
                        stringstream ss;
                        ss << setw(4) << setfill(' ') << matrixx[i][j];
                        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                        x = x + to_string(matrixx[i][j]).length() * 10 + 10;
                    }
                    x = starttextX; // Đặt lại x về giá trị ban đầu
                    y -= 20;
                }
                y = starttextY;
            }
            drawBOX(240, -230, 340, -260, 0, 0, 1, "PREVIOUS", 0);
            drawBOX(360, -230, 410, -260, 0, 0, 1, "NEXT", 0);
            drawBOX(430, -230, 600, -260, 0, 0, 1, "CONFIRM MATRIX", 0);
            glutPostRedisplay();
        }
    }
}
void dischoice3()
{
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
    drawRectangle(-600, 120, -400, 90);
        FloydWarshall(dmatrix);
    int x = starttextX;
    int y = starttextY;
    if (!shortestDistances.empty()) {
        int n = shortestDistances.size();
        // Xây dựng chuỗi thông tin kích thước
        stringstream sizeInfo;
        sizeInfo << "Ma tran duong di ngan nhat " << n << " x " << n << " :";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;
        // Hiển thị ma trận
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                stringstream ss;
                ss << setw(4) << setfill(' ') << shortestDistances[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
            x = starttextX; // Đặt lại x về giá trị ban đầu
            y -= 20; // Di chuyển xuống hàng tiếp theo
        }

        if (input) {
            if (startchoiceMinLength < 1) {
                if (startchoiceMinLength != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18,
                        to_string(startchoiceMinLength));
                }
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
                renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, inputText);
            }
            else if (endchoiceMinLength < 1) {
                if (startchoiceMinLength != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18,
                        to_string(startchoiceMinLength));
                }
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
                y -= 20;
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem ket thuc: ");
                renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, inputText);
                if (endchoiceMinLength != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18,
                        to_string(endchoiceMinLength));
                }
            }
            else {
                resultofmin = true;
                input = false;
            }
        }
        if (resultofmin == true) {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
            renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18,
                to_string(startchoiceMinLength));
            y -= 20;
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem ket thuc: ");
            renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(endchoiceMinLength));
            y -= 20;
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Duong di ngan nhat la :");
            if (startchoiceMinLength == endchoiceMinLength)
            {
                renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, "0 (Khong di chuyen)");
            }
            else {
                if (shortestDistances[startchoiceMinLength-1][endchoiceMinLength-1] == 0)
                {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, "0 (Khong co duong di)");
                }
                else {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(
                        Min_length(startchoiceMinLength, endchoiceMinLength)));
                }
            }
        }
    }
}
void dischoice4() {
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
    drawRectangle(-600, 70, -400, 40);
    FloydWarshall(dmatrix);
    int x = starttextX;
    int y = starttextY;
    if (!Luuvetpath.empty()) {

        int n = Luuvetpath.size();

        // Xây dựng chuỗi thông tin kích thước
        std::stringstream sizeInfo;
        sizeInfo << "Ma tran Truy vet " << n << " x " << n << " :";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;
        // Hiển thị ma trận
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                stringstream ss;
                ss << setw(4) << setfill(' ') << Luuvetpath[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
            x = starttextX; // Đặt lại x về giá trị ban đầu
            y -= 20; // Di chuyển xuống hàng tiếp theo
        }
        if (input) {
            if (startchoiceLuuvet < 1) {
                if (startchoiceLuuvet != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(startchoiceLuuvet));
                }
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
                renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, inputText);
            }
            else if (endchoiceLuuvet < 1) {
                if (startchoiceLuuvet != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(startchoiceLuuvet));
                }
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
                y -= 20;
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem ket thuc: ");
                renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, inputText);
                if (endchoiceLuuvet != 0) {
                    renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(endchoiceLuuvet));
                }
            }
            else {
                resultofway = true;
                input = false;
            }
        }
        if (resultofway == true) {
            Way = Truyvet(startchoiceLuuvet, endchoiceLuuvet);
            queue<int> tmpWay = Way; // Tạo một bản sao của Way để không làm thay đổi Way gốc
            stringstream Wayy;
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem bat dau: ");
            renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(startchoiceLuuvet));
            y -= 20;
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem ket thuc: ");
            renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, to_string(endchoiceLuuvet));
            y -= 20;
            Wayy << "Di chuyen tu " << startchoiceLuuvet << " den " << endchoiceLuuvet << " :";
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, Wayy.str());
            if (startchoiceLuuvet == endchoiceLuuvet) {
                renderBitmapString(x + 180, y, GLUT_BITMAP_HELVETICA_18, "tai cho");
            }
            else {
                if (Luuvetpath[startchoiceLuuvet-1][endchoiceLuuvet-1]==0) {
                    renderBitmapString(x + 180, y, GLUT_BITMAP_HELVETICA_18, "Khong co duong di");
                }
                else
                {
                    while (!tmpWay.empty()) {
                        string currentVertex = to_string(tmpWay.front());
                        renderBitmapString(x + 200, y, GLUT_BITMAP_HELVETICA_18, currentVertex);
                        if (tmpWay.size() > 1) {
                            renderBitmapString(x + 200 + 10, y, GLUT_BITMAP_HELVETICA_18, "  ->");
                        }
                        tmpWay.pop();
                        x += 50;
                    }
                }
            }
        }
    }
}
void dischoice5()
{
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
    drawRectangle(-600, 20, -400, -10);
    int x = starttextX;
    int y = starttextY;
    if (input && InputData) {
        if (startchoicedijkstra < 1) {
            if (startchoicedijkstra != 0) {
                renderBitmapString(x + 190, y, GLUT_BITMAP_HELVETICA_18, to_string(startchoicedijkstra));
            }
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem nguon: ");
            renderBitmapString(x + 190, y, GLUT_BITMAP_HELVETICA_18, inputText);
        }
        else {
            resultofdijkstra = true;
            input = false;
        }
    }
    if (resultofdijkstra == true) {
            dijkstra(dmatrix, startchoicedijkstra);
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Moi nhap diem nguon: ");
        renderBitmapString(x + 190, y, GLUT_BITMAP_HELVETICA_18, to_string(startchoicedijkstra));
        y -= 20;
        string a;
        vector<vector<string>> b = waytodo;
        for (int i = 0; i < dist1.size(); i++)
        {
            for (int j = 0; j < dist1.size(); ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_10, b[i][j]);
                x += 40; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
                x = starttextX; // Đặt lại x về giá trị ban đầu
                y -= 20; // Di chuyển xuống hàng tiếp theo
            
        }
        for(int i=0;i<dist1.size();i++)
        {
            a += to_string(dist1[i]);
            a += (i < dist1.size() - 1) ? "   " : "";
        }
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Khoang cach ngan nhat tu diem nguon den cac diem con lai :");
        y -= 20;
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, a);
        
    }
}

void dischoice6()
{
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
        drawRectangle(-600, -30, -400, -60);
        int x1 = starttextX;
        int y1 = starttextY;
        int x = starttextX;
        int y = starttextY;
        if (input&&InputData )
        {
            resultofeuler = true;
            input = false;
        }
        if (resultofeuler)
        {
            std::stringstream sizeInfo;
            sizeInfo << "Ma tran " << nn << " x " << nn << " :";
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
            y -= 20;
            // Hiển thị ma trận
            for (int i = 0; i < nn; ++i) {
                for (int j = 0; j < nn; ++j) {
                    // Định dạng chuỗi ký tự trước khi in ra
                    stringstream ss;
                    ss << setw(4) << setfill(' ') << dmatrix[i][j];
                    renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                    x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
                }
                x1 = x;
                x = starttextX; // Đặt lại x về giá trị ban đầu
                y -= 20; // Di chuyển xuống hàng tiếp theo
            }
            int i;
            
                i = findStartVert();
                if (hasEulerCycle() && !hasEulerPath()&&call==false)
                {
                    fleuryAlgorithm(i);
                    path.insert(path.begin(), i + 1);
                    call = true;
                }
                if (!path.empty() && hasEulerCycle())
                {
                    i = findStartVert();
                    renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Co chu trinh euler trong do thi tren:");
                    y -= 20;
                    string demo;
                    demo = "Chu trinh euler :";
                    renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, demo);
                    y -= 20;
                    for (int i = 0; i < path.size(); i++)
                    {
                        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, to_string(path[i]));
                        x += to_string(path[i]).length() * 15;
                    }
                }
                else
                {
                    renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Khong co chu trinh euler trong do thi tren");
                }
            
        }
        // Xây dựng chuỗi thông tin kích thước
}
void dischoice7()
{
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
    if (input && InputData)
    {
        resultofeuler = true;
        input = false;
    }
    if (resultofeuler)
    {
        drawRectangle(-600, -80, -400, -110);
        int x = starttextX;
        int y = starttextY;
        std::stringstream sizeInfo;
        sizeInfo << "Ma tran " << nn << " x " << nn << " :";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;
        // Hiển thị ma trận
        for (int i = 0; i < nn; ++i) {
            for (int j = 0; j < nn; ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                stringstream ss;
                ss << setw(4) << setfill(' ') << dmatrix[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
            x = starttextX; // Đặt lại x về giá trị ban đầu
            y -= 20; // Di chuyển xuống hàng tiếp theo
        }
        int i;
        i = findStartVert();
        if (hasEulerPath() && !hasEulerCycle() && call == false)
        {
            fleuryAlgorithm(i);
            path.insert(path.begin(), i + 1);
            call = true;
        }
        if (!path.empty() && hasEulerPath())
        {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Co duong di euler trong do thi tren:");
            y -= 20;
            string demo;
            demo = "Duong di euler: ";
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, demo);
            y -= 20;
            for (int i = 0; i < path.size(); i++)
            {
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, to_string(path[i]));
                x += to_string(path[i]).length() * 15;
            }x = starttextX;
        }
        else
        {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "Khong co duong di euler trong do thi tren");
        }

    }

}
stack<pair<int, int>> test;
void dischoice8()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    
    if (call == false)
    {
        
        Maze = InitWindoww();
        
        MazeGame(Maze, StartGame, EndGame);
        glutTimerFunc(0, drawWay, 0);
        drawMap(siizze, Maze);
        glutPostRedisplay();
    }
    //drawMap(siizze, Maze);
    
}
void dischoice9()
{
    if (!InputData && !basemenu) {
        renderBitmapString(starttextX, starttextY, GLUT_BITMAP_HELVETICA_18, "ERROR:Chua nhap ma tran");
    }
    drawRectangle(-600, -180, -400, -210);
    int x = starttextX;
    int y = starttextY;
    if (input && InputData)
    {
        resultofhamilton = true;
        input = false;
    }
    if (resultofhamilton)
    {

        int x = starttextX;
        int y = starttextY;
        std::stringstream sizeInfo;
        sizeInfo << "Ma tran " << nn << " x " << nn << " :";
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, sizeInfo.str());
        y -= 20;
        // Hiển thị ma trận
        for (int i = 0; i < nn; ++i) {
            for (int j = 0; j < nn; ++j) {
                // Định dạng chuỗi ký tự trước khi in ra
                stringstream ss;
                ss << setw(4) << setfill(' ') << dmatrix[i][j];
                renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, ss.str());
                x += 30; // Cập nhật x để di chuyển sang phần tử tiếp theo của hàng
            }
            x = starttextX; // Đặt lại x về giá trị ban đầu
            y -= 20; // Di chuyển xuống hàng tiếp theo
        }

        if ((hashamiltoncycle_DIRAC(matrixofhamilton) || hashamiltoncycle_ORE(matrixofhamilton)) && call == false)
        {

            findAllHamiltonPaths();
            complete();
            call = true;
        }

        if (!pathofhamiltonpath.empty() && (hashamiltoncycle_DIRAC(matrixofhamilton) || hashamiltoncycle_ORE(matrixofhamilton)))
        {

            string demo;
            pathofhamiltonpath.shrink_to_fit();
            num_rows = pathofhamiltonpath.size();
            demo = "Co " + to_string(num_rows) + " duong Hamilton trong do thi tren";
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, demo);
            int y1 = y;
            rowss = (y + 260) / 20;
            y -= 20;
            int j = scroll;
            string tmp;
            for (j; j < pathofhamiltonpath.size(); j++)
            {

                if (y > -260 && y <= y1)
                {
                    tmp = to_string(j + 1) + ".";
                    renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, tmp, 1, 1, 1);
                    x += 50;
                    for (int i = 0; i < pathofhamiltonpath[j].size(); i++)
                    {
                        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, to_string(pathofhamiltonpath[j][i]), 1, 1, 1);
                        x += 30;
                    }
                    x = starttextX;
                    y -= 20;
                }

            }

        }
        else
        {
            renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, "khong co duong di hamilton");
        }
    }
}
//function change value when press key_up and _down
void handleSpecialKeypress(int key, int x, int y)
{
    if (basemenu)
    {
        switch (key) {
        case GLUT_KEY_UP: {
            if (!isDOWNKeyPressed) {
                //change value of choice base menu
                if (bchoice <= 11 && bchoice >= 0)
                    bchoice = (bchoice == 1) ? 10 : (bchoice - 1);
            }
            isUPKeyPressed = true;
            break;
        }
        case GLUT_KEY_DOWN: {
            if (!isUPKeyPressed) {
                if (bchoice <= 11 && bchoice >= 0)
                    bchoice = (bchoice == 10) ? 1 : (bchoice + 1);
            }
            isDOWNKeyPressed = true;
            break;
        }
        }
    }
    else
    {
        switch (key)
        {
        case GLUT_KEY_UP: {

            if (!isDOWNKeyPressed) {
                if (isindis == 1)
                {
                    if (choicetxt <= totaltxtfile && choicetxt >= 0)
                        choicetxt = (choicetxt == totaltxtfile) ? 1 : (choicetxt + 1);

                }
               
                if (isindis == 9)
                {
                    if (scroll <= pathofhamiltonpath.size() && scroll >= 0)
                    {
                        scroll -= 1;
                        if (scroll <= 0)
                            scroll = 0;
                    }
                }
            }
            isUPKeyPressed = true;
            break;
        }
        case GLUT_KEY_DOWN: {
            if (!isUPKeyPressed) {
                if (isindis == 1)
                {
                    if (choicetxt <= totaltxtfile && choicetxt >= 0)
                        choicetxt = (choicetxt == 1) ? totaltxtfile : (choicetxt - 1);
                }
                
                if (isindis == 9)
                {
                    if (scroll >= 0 && scroll <= pathofhamiltonpath.size() - rowss && rowss < pathofhamiltonpath.size())
                    {
                        scroll += 1;
                        if (scroll >= pathofhamiltonpath.size())
                            scroll = pathofhamiltonpath.size();

                    }
                }
            }
            isDOWNKeyPressed = true;
            break;
        }
        case GLUT_KEY_LEFT: {
            if (!isLEFTKeyPressed) {
                if (isindis == 2)
                {
                    if (valuenxn >= 0 && valuenxn < nn * nn)
                    {
                        valuenxn = (valuenxn == 0) ? nn * nn - 1 : (valuenxn - 1);
                    }

                }
                if (isindis == 1)
                {
                    if (choicetxt <= totaltxtfile && choicetxt >= 0)
                        choicetxt = (choicetxt == 1) ? totaltxtfile : (choicetxt - 1);
                }

            }isLEFTKeyPressed = true;
            break;
        }
        case GLUT_KEY_RIGHT: {
            if (!isRIGHTKeyPressed) {
                if (isindis == 2)
                {
                    if (valuenxn >= 0 && valuenxn < nn * nn)
                    {
                        valuenxn = (valuenxn == nn * nn - 1) ? 0 : (valuenxn + 1);
                    }

                }
                if (isindis == 1)
                {
                    if (choicetxt <= totaltxtfile && choicetxt >= 0)
                        choicetxt = (choicetxt == totaltxtfile) ? 1 : (choicetxt + 1);

                }

            }isRIGHTKeyPressed = true;
            break;
        }
        }
    }
    glutPostRedisplay();
}
void handleSpecialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        isUPKeyPressed = false;
        break;
    case GLUT_KEY_DOWN:
        isDOWNKeyPressed = false;
        break;
    case GLUT_KEY_LEFT:
        isLEFTKeyPressed = false;
        break;
    case GLUT_KEY_RIGHT:
        isRIGHTKeyPressed = false;
        break;
    }
    glutPostRedisplay();
}
void handleKeyPress(unsigned char key, int x, int y) {
    switch (key)
    {
    case 13:
    {
        // 13 là mã ASCII của phím Enter
        // Xử lý khi phím Enter được nhấn
        if (basemenu) {
            switch (bchoice) {
            case 1:
                isindis = 1;
                break;
            case 2:
                isindis = 2;
                input = true;
                break;
            case 3:
                isindis = 3;
                input = true;
                break;
            case 4:
                isindis = 4;
                input = true;
                break;
            case 5:
                isindis = 5;
                input = true;
                break;
            case 6:
                isindis = 6;
                input = true;
                break;
            case 7:
                isindis = 7;
                input = true;
                break;
            case 8:
                isindis = 8;
                input = true;
                break;
            case 9:
                isindis = 9;
                input = true;
                break;
            case 10:
                std::exit(0);
                return;
            }
        }
        isEnterKeyPressed = true;
        break;
    }
    default:
        break;
    }
    if (input)
    {
        if (key == 13) {  // 13 là mã ASCII của Enter
            // Xử lý dữ liệu đầu vào ở đây (inputText)
            switch (bchoice)
            {
            case 1: {
                break;
            }
            case 2: {

                if (isDigit(inputText))
                {
                    if (atoi(inputText.c_str()) <= 19 && atoi(inputText.c_str()) >1) {
                        if (tmpnn < 2) {
                            tmpnn = atoi(inputText.c_str());
                           
                            nn = tmpnn;
                            vector<vector<int>>a(nn,vector<int>(nn,0));
                            matrixx = a;
                            inputText = "";
                            
                        }
                    }if (valuenxn <= nn * nn && checkinputsize == true) {
                        int i = (valuenxn) / nn; // Tính chỉ số hàng
                        int j = (valuenxn) % nn; // Tính chỉ số cột
                        if (i == j) {
                            // Đây là phần tử trên đường chéo chính
                            if (atoi(inputText.c_str()) != 0) {
                                matrixx[i][j] = 0;
                            }
                            else {
                                matrixx[i][j] = atoi(inputText.c_str());// Đặt giá trị mặc định cho phần tử trung tâm
                            }
                            valuenxn++;
                        }
                        else {
                            // Đây không phải là phần tử trên đường chéo chính
                            matrixx[i][j] = atoi(inputText.c_str());
                            valuenxn++;
                        }
                        if (valuenxn == nn * nn)
                        {
                            valuenxn = 0;
                        }
                        check_Undirected_graph = isUndirected(matrixx);
                        inputText = "";
                    }
                }
                break;
            }
            case 3: {
                if (isDigit(inputText) && (atoi(inputText.c_str()) <= dmatrix.size())) {
                    if (startchoiceMinLength < 1)
                    {
                        startchoiceMinLength = atoi(inputText.c_str());
                    }
                    else if (endchoiceMinLength < 1)
                    {
                        endchoiceMinLength = atoi(inputText.c_str());
                    }
                }
                break;
            }
            case 4:
            {
                if (isDigit(inputText) && (atoi(inputText.c_str()) <= dmatrix.size())) {
                    if (startchoiceLuuvet < 1)
                    {
                        startchoiceLuuvet = atoi(inputText.c_str());
                    }
                    else if (endchoiceLuuvet < 1)
                    {
                        endchoiceLuuvet = atoi(inputText.c_str());
                    }
                }
                break;
            }
            case 5:
            {
                if (isDigit(inputText) && (atoi(inputText.c_str()) <= dmatrix.size())) {
                    if (startchoicedijkstra < 1)
                    {
                        startchoicedijkstra = atoi(inputText.c_str());
                    }
                }
                break;
            }
            case 6:break;

            case 8: {
                break;
            }
            case 9: {break; }
            }
            inputText = "";
        }
        else if (key == 8 && !inputText.empty())
        { // 8 là mã ASCII của Backspace
            inputText.pop_back(); // Xóa ký tự cuối cùng
        }
        else if (key >= 32 && key <= 126)
        { // Kiểm tra xem key có nằm trong khoảng ký tự in được
            inputText += key;  // Thêm ký tự vào văn bản
        }
    } // Vẽ lại cảnh
    glutPostRedisplay();
}
void handleKeyReleased(unsigned char key, int x, int y)
{
    if (key == 13)
    {
        // Xử lý khi phím Enter được thả ra
        if (basemenu)
        {
            /*switch (bchoice)
            {
            case 1:
                resultofmin = false; resultofeuler = false;
                resultofway = false;
                resultofdijkstra = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                valuenxn = 0;
                checkinputsize = false;
                basemenu = false;
                isindis = 1;
                bchoice = 1;
                matrixofhamilton.clear();
                path.clear(); 
                
                pathofhamiltonpath.clear();
                matrixx.clear();
                matrixxx.clear();
                b.clear();
                
                call=false;scroll=0;
                break;
            case 2:
                resultofmin = false; resultofeuler = false;
                resultofdijkstra = false;
                resultofway = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                valuenxn = 0;
                basemenu = false;
                checkinputsize = false;
                isindis = 2;
                path.clear();
                pathofhamiltonpath.clear();
                
                matrixofhamilton.clear();
                matrixx.clear();
                matrixxx.clear();
                b.clear();
                call=false;scroll=0;
                bchoice = 2;
                input = true;
                break;
            case 3:
                resultofmin = false; resultofeuler = false;
                resultofway = false;
                resultofdijkstra = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 3;
                bchoice = 3;
                
                input = true;
                checkinputsize = false;
                valuenxn = 0;
                path.clear(); 
                
                pathofhamiltonpath.clear();
                matrixofhamilton.clear();
                matrixx.clear();
                call=false;scroll=0;
                matrixxx.clear();
                b.clear();
                break;
            case 4:
                resultofmin = false; resultofeuler = false;
                resultofdijkstra = false;
                resultofway = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 4;
                bchoice = 4;
                checkinputsize = false;
                path.clear();pathofhamiltonpath.clear();
                
                input = true;
                valuenxn = 0;
                matrixofhamilton.clear();
                matrixx.clear();
                call=false;scroll=0;
                matrixxx.clear();
                b.clear();
                break;
            case 5:
                input = true;
                resultofmin = false; resultofeuler = false;
                resultofway = false;
                resultofdijkstra = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 5;
                checkinputsize = false;
                bchoice = 5;
                path.clear();pathofhamiltonpath.clear();
                
                valuenxn = 0;
                matrixofhamilton.clear();
                matrixx.clear();
                matrixxx.clear();
                call=false;scroll=0;
                b.clear();
                break;
            case 6:
                input = true;
                resultofmin = false; resultofeuler = false;
                resultofdijkstra = false;
                resultofway = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 6;
                checkinputsize = false;
                bchoice = 6;
                valuenxn = 0;
                
                matrixofhamilton.clear();
                path.clear();pathofhamiltonpath.clear();
                b = dmatrix;
                call=false;scroll=0;
                matrixx.clear();
                matrixxx.clear();
                break;
            case 7:
                input = true;
                resultofmin = false; resultofeuler = false;
                resultofdijkstra = false;
                resultofway = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 7;
                checkinputsize = false;
                bchoice = 7;
                b = dmatrix;
                
                path.clear();pathofhamiltonpath.clear();
                valuenxn = 0;
                matrixofhamilton.clear();
                matrixx.clear();
                call=false;scroll=0;
                matrixxx.clear();
                break;
            case 8:
                input = true;
                resultofmin = false; resultofeuler = false;
                resultofdijkstra = false;
                resultofway = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 8;
                checkinputsize = false;
                bchoice = 8;
                valuenxn = 0;
                matrixofhamilton = dmatrix;
                
                path.clear();
                pathofhamiltonpath.clear();
                matrixx.clear();
                matrixxx.clear();
                call=false;scroll=0;
                b.clear();
                break;
            case 9:
                input = true;
                resultofmin = false; resultofeuler = false;
                resultofway = false;
                resultofdijkstra = false;
                startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
                tmpnn = 0; resultofhamilton = false;
                basemenu = false;
                isindis = 9;
                checkinputsize = false;
                bchoice = 9;
                valuenxn = 0;
                
                path.clear(); pathofhamiltonpath.clear();
                matrixx.clear();
                matrixxx.clear();
                b.clear();
                call=false;scroll=0;
                break;
            }*/
        }
        else
        {
            switch (isindis) {
            case 1: {
                if (check_Undirected_graph)
                {
                    basemenu = true;
                    valuenxn = 0;
                    isindis = 0;
                    dmatrix = matrixxx;
                    InputData = true;

                }
                break;
            }
            case 2:
            {
             
                break;
            }
            }
            
        }
        isEnterKeyPressed = false;
    }
    if (key == 27)
    {
        // command to basemenu
        basemenu = true;
        input = false;
        resultofmin = false;resultofeuler=false;
        resultofway = false;
        resultofdijkstra = false;
        checkinputsize = false;
        valuenxn = 0;
        isindis = 0;
        tmpnn=0;resultofhamilton = false;
        matrixofhamilton.clear();
        path.clear();
        pathofhamiltonpath.clear();
        call =false;
        startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
        Maze.clear();
        number = 12;
        pathss.clear();
        glutPostRedisplay();
    }
}
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseX = (x - (W / 2.0));
            mouseY = ((H / 2.0) - y);
            inputText = "";
            handleClick(mouseX, mouseY);
            
        }
        
    }
    glutPostRedisplay();
}
void mouseMotion(int x, int y) {
    // Cập nhật vị trí chuột khi di chuyển chuột
    mouseX = (x - (W / 2.0));
    mouseY = ((H / 2.0) - y);
    
}
void handleClick(int x, int y)
{
    if (x >= -530 && x <= -270 && y <= 270 && y >= 230)
    {
        Maze.clear();
        number = 12;
        pathss.clear();
        basemenu = true;
        input = false;
        resultofmin = false;resultofeuler=false;
        resultofway = false;
        resultofdijkstra = false;
        checkinputsize = false;
        valuenxn = 0;
        matrixofhamilton.clear();
        isindis = 0;
        path.clear();pathofhamiltonpath.clear();
        tmpnn=0;resultofhamilton = false;
        matrixx.clear();
        matrixxx.clear();
        b.clear();
        call =false;
        startchoiceMinLength = startchoiceLuuvet = endchoiceMinLength = endchoiceLuuvet = startchoicedijkstra = 0;
    }
    if (isindis == 1)
    {
        if ((x >= 240 && x <= 340 && y <= -230 && y >= -260))
        {
            choicetxt--;
            if (choicetxt < 1)
                choicetxt = totaltxtfile;
        }
        if ((x >= 360 && x <= 410 && y <= -230 && y >= -260))
        {
            choicetxt++;
            if (choicetxt > totaltxtfile)
                choicetxt = 1;
        }
        if ((x >= 430 && x <= 6000 && y <= -230 && y >= -260))
        {
            if (check_Undirected_graph)
            {
                basemenu = true;
                valuenxn = 0;
                isindis = 0;
                dmatrix = matrixxx;
                InputData = true;

            }
        }
    }
    if (x >= -600 && x <= -400 && y <= 220 && y >= 190)//case1
    {
        basemenu = false;
        isindis = 1;
        bchoice = 1;
        matrixx.clear();
        matrixxx.clear();
        b.clear();
        
        call =false;
    }
    if (isindis == 2)
    {
        if ((x >= 240 && x <= 340 && y <= -230 && y >= -260))
        {
            valuenxn--;
            if (valuenxn < 0)
                valuenxn = nn * nn - 1;
        }
        if ((x >= 360 && x <= 410 && y <= -230 && y >= -260))
        {
            valuenxn++;
            if (valuenxn > nn * nn - 1)
                valuenxn = 0;
        }
        if ((x >= 430 && x <= 6000 && y <= -230 && y >= -260))
        {
            
            if (check_Undirected_graph == true)
            {
                basemenu = true;
                valuenxn = 0;
                isindis = 0;
                dmatrix = matrixx;
                InputData = true;
            }
        }
    }
    if (x >= -600 && x <= -400 && y <= 170 && y >= 140)
    {
        valuenxn = 0;
        basemenu = false;
        checkinputsize = false;
        isindis = 2;
        matrixx.clear();
        matrixxx.clear();
        b.clear();
        call =false;
        bchoice = 2;
        input = true;
    }
    if (x >= -600 && x <= -400 && y <= 120 && y >= 90)
    {
        resultofmin = false;
              
        startchoiceMinLength  = endchoiceMinLength = 0;
        
        basemenu = false;
        isindis = 3;
        bchoice = 3;
        
        input = true;
        
        matrixx.clear();
        call =false;
        matrixxx.clear();
        b.clear();

    }
    if (x >= -600 && x <= -400 && y <= 70 && y >= 40)
    {
        resultofway = false;
        startchoiceLuuvet = endchoiceLuuvet  = 0;
        
        basemenu = false;
        isindis = 4;
        bchoice = 4;
      
        
        input = true;
        matrixx.clear();
        call =false;
        matrixxx.clear();
        b.clear();
    }
    if (x >= -600 && x <= -400 && y <= 20 && y >= -10)
    {
        input = true;
        resultofdijkstra = false;
        startchoicedijkstra = 0;
        
        basemenu = false;
        isindis = 5;
        
        bchoice = 5;
        
        matrixx.clear();
        matrixxx.clear();
        call =false;
        b.clear();
    }
    if (x >= -600 && x <= -400 && y <= -30 && y >= -60)
    {
        input = true;
        resultofeuler=false;
        basemenu = false;
        isindis = 6;
        bchoice = 6;
        b = dmatrix;
        call =false;
        matrixx.clear();
        matrixxx.clear();
        
    }
    if (x >= -600 && x <= -400 && y <= -80 && y >= -110)
    {
        input = true;
        resultofeuler=false;
        basemenu = false;
        isindis = 7;
        bchoice = 7;
        b = dmatrix;
        matrixx.clear();
        call =false;
        matrixxx.clear();
        
    }
    if (x >= -600 && x <= -400 && y <= -130 && y >= -160)
    {
        basemenu = false;
        isindis = 8;
        bchoice = 8;
        valuenxn = 0;
        call=false;
        b.clear();
        Maze.clear();
        number = 12;
        pathss.clear();
        //movi.clear();
    }
    if (x >= -600 && x <= -400 && y <= -180 && y >= -210)
    {
        input = true;
        
        tmpnn=0;
        resultofhamilton = false;
        basemenu = false;
        isindis = 9;
        checkinputsize = false;
        bchoice = 9;
        matrixofhamilton = dmatrix;
        path.clear();
        pathofhamiltonpath.clear();
        b.clear();
        call =false;
        scroll = 0;
    }
    if (x >= -600 && x <= -400 && y <= -230 && y >= -260)
    {
        std::exit(0);
    }
}

