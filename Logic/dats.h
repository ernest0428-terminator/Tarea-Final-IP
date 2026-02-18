//Constantes
#define tiendaMaxima 100
#define nombreMaximo 50
#define meses 12
#define datosPrueba 10
#define saltoLinea printf("\n");
#define lineaDivision printf("---------------------------------------------------------------\n");

//Estrucutra de la tienda
#ifndef DATOS_H
#define DATOS_H
struct datosTienda{
    char nombre[nombreMaximo]; // ¡Cambié 100 por nombreMaximo!
    float plan[meses];
    float ventas[meses];
    float totalPlan;
    float totalVentas;
};
typedef struct datosTienda Tienda;

#endif
