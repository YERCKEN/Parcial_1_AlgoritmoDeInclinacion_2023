#include <GLFW/glfw3.h>
#include <iostream>

// Ancho y alto de la ventana
const int ventanaAncho = 850;
const int ventanaAlto = 900;
float shx = 0.0f;

float R = 0.0f, G = 0.0f, B = 1.0f;

int xRef, yRef;

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

// Función para configurar la proyección ortográfica con el origen en el centro
void configurarProyeccionCentrada(int ancho, int alto) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ancho / 2.0, ancho / 2.0, -alto / 2.0, alto / 2.0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Función para dibujar el rectángulo (BÁSICO)
void dibujarRectangulo() {

    glBegin(GL_QUADS);

    // Color del rectángulo (azul)
    glColor3f(R, G, B); // Azul
    // Dibuja el rectángulo usando los vértices definidos
    glVertex2f(x_up_i, y_up_i); // Vértice 1 (arriba izquierda)
    glVertex2f(x_up_d , y_up_d); // Vértice 2 (arriba derecha)
    glVertex2f(x_down_d , y_down_d); // Vértice 3 (abajo derecha)
    glVertex2f(x_down_i , y_down_i); // Vértice 4 (abajo izquierda)
    glEnd();
}


void aplicacionCoordenadasIniciales() {

    R = 0.0f;
    G = 0.0f;
    B = 1.0f;
    x_down_i = 0.0f, y_down_i = 0.0f;
    x_up_i = 0.0f, y_up_i = 200.0f;
    x_down_d = 150.0f, y_down_d = 0.0f;
    x_up_d = 150.0f, y_up_d = 200.0f;

}


void aplicacionInclinacionBasica() {


    R = 0.0f;
    G = 0.0f;
    B = 1.0f;

    //Vértice 1 (arriba izquierda)
    x_up_i = x_up_i + (shx * y_up_i);
    y_up_i = y_up_i;

    // Vértice 2 (arriba derecha)
    x_up_d = x_up_d + (shx * y_up_d);
    y_up_d = y_up_d;

    // Vértice 3 (abajo derecha)
    x_down_d = x_down_d + (shx * y_down_d);
    y_down_d = y_down_d;

    // Vértice 4 (abajo izquierda)
    x_down_i = x_down_i + (shx * y_down_i);
    y_down_i = y_down_i;

}



// NCLINACIÓN YREF
void aplicarInclinacionConYref(int yRef) {

    R = 1.0f;
    G = 0.631f;
    B = 0.655f;


    //Vértice 1 (arriba izquierda)
    x_up_i = x_up_i + shx * (y_up_i - yRef);
    y_up_i = y_up_i;

    // Vértice 2 (arriba derecha)
    x_up_d = x_up_d + shx * (y_up_d - yRef);
    y_up_d = y_up_d;

    // Vértice 3 (abajo derecha)
    x_down_d = x_down_d + shx * (y_down_d - yRef);
    y_down_d = y_down_d;

    // Vértice 4 (abajo izquierda)
    x_down_i = x_down_i + shx * (y_down_i - yRef);
    y_down_i = y_down_i;
}

// NCLINACIÓN XREF
void aplicarInclinacionConXref(int xRef) {


    R = 0.459f;
    G = 0.761f;
    B = 0.439f;

    //Vértice 1 (arriba izquierda)
    y_up_i = y_up_i + shx * (x_up_i - xRef);
    x_up_i = x_up_i;

    // Vértice 2 (arriba derecha)
    y_up_d = y_up_d + shx * (x_up_d - xRef);
    x_up_d = x_up_d;

    // Vértice 3 (abajo derecha)
    y_down_d = y_down_d + shx * (x_down_d - xRef);
    x_down_d = x_down_d;

    // Vértice 4 (abajo izquierda)
    y_down_i = y_down_i + shx * (x_down_i - xRef);
    x_down_i = x_down_i;
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

    std::cout << "=====================================\n";
    std::cout << "           PARAMETRO (SHX)\n";
    std::cout << "=====================================\n";

    std::cout << "\nIngrese el nuevo valor de shx: ";
    std::cin >> shx;

    //limpiar pantalla
    system("cls");

}

void menuCambiarCoordenadas() {
    std::cout << "================================================================================\n";
    std::cout << "                           DEFINICION DE COORDENADAS\n";
    std::cout << "================================================================================\n";

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


    configurarProyeccionCentrada(ventanaAncho, ventanaAlto);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        cambiarColorFondo();
        dibujarRectangulo();
        dibujarPlanoCartesiano(ventanaAncho, ventanaAlto, 50);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Mostrar el menú de opciones
        std::cout << "=====================================\n";
        std::cout << "               MENU\n";
        std::cout << "=====================================\n";
        std::cout << "\n1. Cambiar shx\n" << std::endl;
        std::cout << "2. Cambiar coordenadas\n" << std::endl;
        std::cout << "3. Inclinacion Basica\n" << std::endl;
        std::cout << "4. Inclinacion con Y_REF\n" << std::endl;
        std::cout << "5. Inclinacion con X_REF\n" << std::endl;
        std::cout << "6. Coordernadas Predeterminadas\n" << std::endl;

        std::cout << "0. Salir \n" << std::endl;
        std::cout << "=====================================\n" << std::endl;


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
        case 3:
            aplicacionInclinacionBasica();
            break;
        case 4:

            //limpiar pantalla
            system("cls");

            std::cout << "=====================================\n";
            std::cout << "           PARAMETRO Y_REF\n";
            std::cout << "=====================================\n\n";
            std::cout << "Ingrese Y_REF: ";
            std::cin >> yRef;

            //limpiar pantalla
            system("cls");
            aplicarInclinacionConYref(yRef);
            break;

        case 5: 
            //limpiar pantalla
            system("cls");

            std::cout << "=====================================\n";
            std::cout << "           PARAMETRO X_REF\n";
            std::cout << "=====================================\n\n";

            std::cout << "Ingrese X_REF: ";
            std::cin >> xRef;

            //limpiar pantalla
            system("cls");
            aplicarInclinacionConXref(xRef);
                break;
        case 6:
            aplicacionCoordenadasIniciales();
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
