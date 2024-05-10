#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Variáveis para controle das cores e estilos do rosto

int faceContour = 1;
int hairStyle = 1;
int eyeShape = 1;
int mouthShape = 1;
int browShape = 1;
int noseShape = 1;

void display(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void drawText(char *string);

// Funções para modificar as partes do rosto
void changeFaceContour(int contour);
void changeHair(int hairstyle);
void changeEyes(int eyeShape);
void changeMouth(int mouthShape);
void changeEyebrows(int browShape);
void changeNose(int noseShape);
void clear_and_redraw(int newContour, int newHair, int newEyes, int newMouth, int newBrows, int newNose);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MiniMii - Modifique com as teclas!");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    return 0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o rosto com as cores atuais
    changeFaceContour(faceContour);
    // Desenha o cabelo
    changeHair(hairStyle);

    // Desenha os olhos
    changeEyes(eyeShape);

    // Desenha a boca
    changeMouth(mouthShape);

    // Desenha as sobrancelhas
    changeEyebrows(browShape);

    // Desenha o nariz
    changeNose(noseShape);


    drawText("Controles: F1-F6 (Cabelos), 1-6 (Olhos), q-y (Boca), a-h (Sobrancelha), z-n (Nariz)");

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    printf("*** Tratamento de teclas comuns\n");
    printf(">>> Tecla pressionada: %c\n", key);
    switch (key) {
        case 27: // Tecla 'Esc' para sair
            exit(0);
        case ' ': // Tecla espaço para resetar a aparência do rosto
            glClear(GL_COLOR_BUFFER_BIT);
            changeFaceContour(1);
            changeHair(1);
            changeEyes(1);
            changeMouth(1);
            changeEyebrows(1);
            changeNose(1);
            drawText("Controles: F1-F6 (Cabelos), 1-6 (Olhos), q-y (Boca), a-h (Sobrancelha), z-n (Nariz)");
            glFlush();
            glutPostRedisplay();
            break;
        case 'q': // Boca - Exemplo
            clear_and_redraw(faceContour, hairStyle, eyeShape, 1, browShape, noseShape);
            break;
        case 'w':
            clear_and_redraw(faceContour, hairStyle, eyeShape, 2, browShape, noseShape);
            break;
        case 'e':
            clear_and_redraw(faceContour, hairStyle, eyeShape, 3, browShape, noseShape);
            break;
        case 'r':
            clear_and_redraw(faceContour, hairStyle, eyeShape, 4, browShape, noseShape);
            break;
        case 't':
            clear_and_redraw(faceContour, hairStyle, eyeShape, 5, browShape, noseShape);
            break;
        case 'y':
            clear_and_redraw(faceContour, hairStyle, eyeShape, 6, browShape, noseShape);
            break;
        case 'a': // Sobrancelha - Exemplo
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 1, noseShape);
            break;
        case 's':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 2, noseShape);
            break;
        case 'd':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 3, noseShape);
            break;
        case 'f':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 4, noseShape);
            break;
        case 'g':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 5, noseShape);
            break;
        case 'h':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, 6, noseShape);
            break;
        case 'z': // Nariz - Exemplo
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 1);
            break;
        case 'x':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 2);
            break;
        case 'c':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 3);
            break;
        case 'v':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 4);
            break;
        case 'b':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 5);
            break;
        case 'n':
            clear_and_redraw(faceContour, hairStyle, eyeShape, mouthShape, browShape, 6);
            break;
        case '1': // Olhos - Exemplo
            clear_and_redraw(faceContour, hairStyle, 1, mouthShape, browShape, noseShape);
            break;
        case '2':
            clear_and_redraw(faceContour, hairStyle, 2, mouthShape, browShape, noseShape);
            break;
        case '3':
            clear_and_redraw(faceContour, hairStyle, 3, mouthShape, browShape, noseShape);
            break;
        case '4':
            clear_and_redraw(faceContour, hairStyle, 4, mouthShape, browShape, noseShape);
            break;
        case '5':
            clear_and_redraw(faceContour, hairStyle, 5, mouthShape, browShape, noseShape);
            break;
        case '6':
            clear_and_redraw(faceContour, hairStyle, 6, mouthShape, browShape, noseShape);
            break;
    }
    glutPostRedisplay();
}


void specialKeyboard(int key, int x, int y) {
    printf("*** Tratamento de teclas especiais\n");
    printf(">>> Tecla pressionada: %d\n", key);
    switch (key) {
        case GLUT_KEY_F1: // Contorno facial
            clear_and_redraw(1, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F2:
            clear_and_redraw(2, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F3:
            clear_and_redraw(3, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F4:
            clear_and_redraw(4, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F5:
            clear_and_redraw(5, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F6:
            clear_and_redraw(6, hairStyle, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F7: // Cabelos
            clear_and_redraw(faceContour, 1, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F8:
            clear_and_redraw(faceContour, 2, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F9:
            clear_and_redraw(faceContour, 3, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F10:
            clear_and_redraw(faceContour, 4, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F11:
            clear_and_redraw(faceContour, 5, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_F12:
            clear_and_redraw(faceContour, 6, eyeShape, mouthShape, browShape, noseShape);
            break;
        case GLUT_KEY_LEFT: // Exemplo de uso da seta esquerda
            // Implemente a lógica desejada
            break;
    }
    glutPostRedisplay();
}

void drawText(char *string) {
    glColor3ub(0, 0, 0); // Cor do texto (preto)
    glRasterPos2f(-0.9, 0.8); // Posição do texto
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string); // Exibe caractere por caractere
        string++;
    }
}

// Implementação das funções para modificar as partes do rosto
void changeFaceContour(int contour) {
    switch (contour) {
        case 1:
            // Contorno facial tipo 1: Círculo completo suave
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.4 * cos(theta); // Raio reduzido para manter dentro do círculo
                    float y = 0.4 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 2:
            // Contorno facial tipo 2: Círculo com "quinas"
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.4 * cos(theta); // Raio reduzido para manter dentro do círculo
                    float y = 0.4 * sin(theta);
                    if (i < 90 || (i > 180 && i < 270)) {
                        x += 0.1;
                    } else {
                        x -= 0.1;
                    }
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 3:
            // Contorno facial tipo 3: Quadrado
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(-0.4, -0.4);
                glVertex2f(0.4, -0.4);
                glVertex2f(0.4, 0.4);
                glVertex2f(-0.4, 0.4);
            glEnd();
            break;
        case 4:
            // Contorno facial tipo 4: Triângulo
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(0.0, 0.4);
                glVertex2f(-0.4, -0.4);
                glVertex2f(0.4, -0.4);
            glEnd();
            break;
        case 5:
            // Contorno facial tipo 5: coração
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(0.0, 0.4);
                glVertex2f(-0.4, 0.0);
                glVertex2f(-0.2, -0.4);
                glVertex2f(0.0, -0.2);
                glVertex2f(0.2, -0.4);
                glVertex2f(0.4, 0.0);
            glEnd();
        case 6:
            // Contorno facial tipo 6: Linhas verticais
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINES); // Desenha linhas
                glVertex2f(-0.4, 0.4);
                glVertex2f(-0.4, -0.4);
                glVertex2f(-0.3, 0.4);
                glVertex2f(-0.3, -0.4);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.2, -0.4);
                glVertex2f(-0.1, 0.4);
                glVertex2f(-0.1, -0.4);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.0, -0.4);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.1, -0.4);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.2, -0.4);
                glVertex2f(0.3, 0.4);
                glVertex2f(0.3, -0.4);
                glVertex2f(0.4, 0.4);
                glVertex2f(0.4, -0.4);
            glEnd();
            break;
    }
}

void changeHair(int hairstyle) {
    switch (hairstyle) {
        case 1:
            // Cabelo tipo 1: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.4);
                glVertex2f(-0.3, 0.35);
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 2:
            // Cabelo tipo 2: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.3, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.25, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.3, 0.4);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 3:
            // Cabelo tipo 3: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.3, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.3, 0.4);
            glEnd();
            break;
        case 4:
            // Cabelo tipo 4: Linhas verticais e horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.3, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.25, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.3, 0.4);
                glVertex2f(0.3, 0.3);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.35); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 5:
            // Cabelo tipo 5: Linhas diagonais e horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.3, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.3, 0.4);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.35); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 6:
            // Cabelo tipo 6: Linhas diagonais e verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.3, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.3, 0.4);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.35); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
    }
}

void changeEyes(int eyeShape) {
    // printf(">>> Alterando olhos para o tipo %d\n", eyeShape);
    switch (eyeShape) {
        case 1:
            // Olhos tipo 1: Círculos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.2 + 0.1 * cos(theta);
                    float y = 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.2 + 0.1 * cos(theta);
                    float y = 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 2:
            // Olhos tipo 2: Retângulos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(-0.1, -0.1);
                glVertex2f(-0.3, -0.1);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
                glVertex2f(0.3, -0.1);
                glVertex2f(0.1, -0.1);
            glEnd();
            break;
        case 3:
            // Olhos tipo 3: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, -0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, -0.1);
            glEnd();
            break;
        case 4:
            // Olhos tipo 4: Triângulos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(-0.2, -0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
                glVertex2f(0.2, -0.1);
            glEnd();
            break;
        case 5:
            // Olhos tipo 5: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
            glEnd();
            break;
        case 6:
            // Olhos tipo 6: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.2, 0.1);
                glVertex2f(-0.2, -0.1);
                glVertex2f(0.2, 0.1);
                glVertex2f(0.2, -0.1);
            glEnd();
            break;
    }
}
void changeMouth(int mouthShape) {
        switch (mouthShape) {
        case 1:
            // Desenho da boca tipo 1 (linha reta)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(-0.2, -0.2);
                glVertex2f(0.2, -0.2);
            glEnd();
            break;
        case 2:
            // Desenho da boca tipo 2 corpo do rosto
            glColor3ub(0, 255, 0); // Cor verde
            glBegin(GL_POLYGON);
                glVertex2f(-0.2, -0.4);
                glVertex2f(0.2, -0.4);
                glVertex2f(0.2, -0.2);
                glVertex2f(-0.2, -0.2);
            glEnd();
            break;
        case 3:
            // Desenho da boca tipo 3 (forma arredondada)
            glColor3ub(0, 0, 255); // Cor azul
            glBegin(GL_POLYGON);
                for (int i = 0; i < 180; ++i) {
                    float theta = i * 2.0 * 3.14159265359 / 180.0;
                    float x = 0.2 * cos(theta);
                    float y = -0.3 + 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 4:
            // Desenho da boca tipo coração
            glColor3ub(255, 255, 0); // Cor amarela
            glBegin(GL_POLYGON);
                for (int i = 0; i < 180; ++i) {
                    float theta = i * 2.0 * 3.14159265359 / 180.0;
                    float x = 0.2 * cos(theta);
                    float y = -0.3 + 0.1 * sin(theta);
                    if (x < 0) {
                        y += 0.1;
                    }
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 5:
            // Desenho da boca tipo 5 (curva para baixo)
            glColor3ub(255, 0, 255); // Cor magenta
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.2, -0.4);
                glVertex2f(-0.1, -0.3);
                glVertex2f(0.0, -0.4);
                glVertex2f(0.1, -0.3);
                glVertex2f(0.2, -0.4);
            glEnd();
            break;
        case 6:
            // Desenho da boca tipo 6 (forma de degrau)
            glColor3ub(0, 255, 255); // Cor ciano
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.2, -0.4);
                glVertex2f(-0.2, -0.3);
                glVertex2f(-0.1, -0.3);
                glVertex2f(-0.1, -0.4);
                glVertex2f(0.0, -0.4);
                glVertex2f(0.0, -0.3);
                glVertex2f(0.1, -0.3);
                glVertex2f(0.1, -0.4);
                glVertex2f(0.2, -0.4);
            glEnd();
            break;
        }
}

void changeEyebrows(int browShape) {
    switch (browShape) {
        case 1:
            // Sobrancelhas tipo 1: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 2:
            // Sobrancelhas tipo 2: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.22); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.27);
                glVertex2f(0.1, 0.27);
                glVertex2f(0.3, 0.22);
            glEnd();
            break;
        case 3:
            // Sobrancelhas tipo 3: Curvas
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.27);
                glVertex2f(0.0, 0.27);
                glVertex2f(0.2, 0.18);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 4:
            // Sobrancelhas tipo 4: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.3, 0.25);
                glVertex2f(-0.1, 0.25);
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.1, 0.25);
                glVertex2f(0.3, 0.25);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 5:
            // Sobrancelhas tipo 5: Zigzag
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.25);
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.0, 0.25);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.2, 0.25);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 6:
            // Sobrancelhas tipo 6: Linhas horizontais e verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.18);
                glVertex2f(-0.1, 0.25);
                glVertex2f(-0.3, 0.25);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.3, 0.18);
                glVertex2f(0.3, 0.25);
                glVertex2f(0.1, 0.25);
            glEnd();
            break;
    }
}
void changeNose(int noseShape) {
    switch (noseShape) {
        case 1:
            // Nariz tipo 1: Triângulo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.1, 0.0);
                glVertex2f(0.1, 0.0);
                glVertex2f(0.0, -0.2);
            glEnd();
            break;
        case 2:
            // Nariz tipo 2: Linha vertical
            glColor3ub(255, 0, 0); // Cor vermelha
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(0.0, 0.0);
                glVertex2f(0.0, -0.2);
            glEnd();
            break;
        case 3:
            // Nariz tipo 3: Retângulo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(-0.1, 0.0);
                glVertex2f(0.1, 0.0);
                glVertex2f(0.1, -0.2);
                glVertex2f(-0.1, -0.2);
            glEnd();
            break;
        case 4:
            // Nariz tipo 4: Losango
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(0.0, 0.0);
                glVertex2f(-0.1, -0.1);
                glVertex2f(0.0, -0.2);
                glVertex2f(0.1, -0.1);
            glEnd();
            break;
        case 5:
            // Nariz tipo 5: Círculo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.05 * cos(theta); // Raio menor para formar um círculo
                    float y = -0.1 + 0.05 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 6:
            // Nariz tipo 6: Triângulo invertido
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.1, -0.2);
                glVertex2f(0.1, -0.2);
                glVertex2f(0.0, 0.0);
            glEnd();
            break;
        default:
            break;
    }
}

void clear_and_redraw(int newContour, int newHair, int newEyes, int newMouth, int newBrows, int newNose) {
    printf(">>> Alterando olhos para o tipo %d\n", newEyes);
    faceContour = newContour;
    hairStyle = newHair;
    eyeShape = newEyes;
    mouthShape = newMouth;
    browShape = newBrows;
    noseShape = newNose;
    glClear(GL_COLOR_BUFFER_BIT);
    changeFaceContour(faceContour);
    changeHair(hairStyle);
    changeEyes(eyeShape);
    changeMouth(mouthShape);
    changeEyebrows(browShape);
    changeNose(noseShape);
    drawText("Controles: F1-F6 (Cabelos), 1-6 (Olhos), q-y (Boca), a-h (Sobrancelha), z-n (Nariz)");
    glFlush();
}