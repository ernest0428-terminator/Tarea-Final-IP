#include<stdbool.h>
#include<Logic/dats.h>

void bienvenida();
void pausa();

//Lectura de datos
int leerCadenaOpcion(const char *mensaje);
void leerCadenaTexto(const char *mensaje, char cadena[], int max);
float leerFlotante(const char *mensaje,float min, float max);

//Ingreso y validación
float validarValorTienda(const char *nombreMes, const char *tipoDeCaso, float min, float max);
bool validarNombreCompleto(Tienda tiendas[], int cantidad, const char nombre[], char mensajeError[]);


int ingresarNombreTienda(Tienda tiendas[], int cantidad);
void ingresarPlanTienda(Tienda tiendas[], int cantidad);
int ingresarVentasTienda(Tienda tiendas[], int cantidad);
int inicializarDatosPrueba(Tienda tiendas[], int cantidad);

//Funciones de Reportes
void mostrarTiendas(Tienda tiendas[], int cantidad);
void mostrarCumplimiento(Tienda tiendas[], int cantidad);
void mostrarExtremas(Tienda tiendas[], int cantidad);
void mostrarVentas(Tienda tiendas[], int cantidad);
void mostrarBajo50Diciembre(Tienda tiendas[], int cantidad);
void mostrarSuperior40(Tienda tiendas[], int cantidad);


