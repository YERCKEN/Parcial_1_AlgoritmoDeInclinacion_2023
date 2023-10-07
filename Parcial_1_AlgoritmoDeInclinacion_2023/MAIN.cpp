#include <GLFW/glfw3.h>
#include <iostream>

// Ancho y alto de la ventana
const int ventanaAncho = 850;
const int ventanaAlto = 720;
float shx = 0.0f;

// Coordenadas iniciales
float x_down_i = 0.0f, y_down_i = 0.0f;
float x_up_i = 0.0f, y_up_i = 200.0f;
float x_down_d = 150.0f, y_down_d = 0.0f;
float x_up_d = 150.0f, y_up_d = 200.0f;

// Función para centrar la ventana GLFW en la pantalla
void centrarVentana(GLFWwindow* window) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - ventanaAncho) / 2;
    int yPos = (mode->height - ventanaAlto) / 2;
    glfwSetWindowPos(window, xPos, yPos);
}

// Función para dibujar el rectángulo
void dibujarRectangulo() {

    glBegin(GL_QUADS);

    // Color del rectángulo (azul)
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    // Dibuja el rectángulo usando los vértices definidos
    glVertex2f(x_up_i + (shx * y_up_i), y_up_i); // Vértice 1 (arriba izquierda)
    glVertex2f(x_up_d + (shx * y_up_d), y_up_d); // Vértice 2 (arriba derecha)
    glVertex2f(x_down_d + (shx * y_down_d), y_down_d); // Vértice 3 (abajo derecha)
    glVertex2f(x_down_i + (shx * y_down_i), y_down_i); // Vértice 4 (abajo izquierda)
    glEnd();
}

void cambiarColorFondo() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

// Función para dibujar un plano cartesiano como guía con ejes X e Y
void dibujarPlanoCartesiano(int ancho, int alto, int paso) {

    // Dibujar ejes X e Y
    glBegin(GL_LINES);

    // Eje X (verde)
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex2i(-ancho, 0);
    glVertex2i(ancho, 0);

    // Eje Y (rojo)
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glVertex2i(1, -alto);
    glVertex2i(1, alto);
    glEnd();
}


void menuCambiarShx() {

    std::cout << "\nIngrese el nuevo valor de shx: ";
    std::cin >> shx;

    //limpiar pantalla
    system("cls");

}

void menuCambiarCoordenadas() {
    std::cout << "\nIngrese el nuevo valor de ( x_down_i ,  y_down_i ) separados por espacio: ";
    std::cin >> x_down_i >> y_down_i;
    std::cout << "\nIngrese el nuevo valor de ( x_up_i   ,  y_up_i   ) separados por espacio: ";
    std::cin >> x_up_i >> y_up_i;
    std::cout << "\nIngrese el nuevo valor de ( x_down_d ,  y_down_d ) separados por espacio: ";
    std::cin >> x_down_d >> y_down_d;
    std::cout << "\nIngrese el nuevo valor de ( x_up_d   , y_up_d    )  separados por espacio: ";
    std::cin >> x_up_d >> y_up_d;

    //limpiar pantalla
    system("cls");
}



int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Error: Fallo en la inicialización de GLFW." << std::endl;
        return -1;
    }

    window = glfwCreateWindow(ventanaAncho, ventanaAlto, "Algoritmos De Inclinación", NULL, NULL);

    if (!window) {
        std::cerr << "Error: Fallo en la creación de la ventana GLFW." << std::endl;
        glfwTerminate();
        return -1;
    }

    //centrarVentana(window);
    glfwSetWindowPos(window,0, 100);

    glfwMakeContextCurrent(window);
    glOrtho(0, ventanaAncho, 0, ventanaAlto, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        cambiarColorFondo();
        dibujarRectangulo();
        dibujarPlanoCartesiano(ventanaAncho, ventanaAlto, 50);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Mostrar el menú de opciones
        std::cout << "MENU: \n" << std::endl;
        std::cout << "1. Cambiar shx" << std::endl;
        std::cout << "2. Cambiar coordenadas" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "______________________________________\n\n" << std::endl;


        int opcion;
        std::cout << "OPCION: ";
        std::cin >> opcion;

        //limpiar pantalla
        system("cls");


        switch (opcion) {
        case 1:
            menuCambiarShx();
            break;
        case 2:
            menuCambiarCoordenadas();
            break;
        case 0:
            glfwSetWindowShouldClose(window, true);  // Salir del bucle
            break;
        default:
            std::cout << "Opción no válida. Por favor, elija una opción válida." << std::endl;
            break;
        }
    }

    glfwTerminate();
    return 0;
}
