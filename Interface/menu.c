#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<Interface/interface.h>
#include<Interface/report.h>
#include<Logic/dats.h>
#include<Logic/colors.h>
#include<Logic/logic.h>

int menuEntradaDatos(Tienda tiendas[], int cantidad, bool *datosGenerados){
    int opcion;
    bool continuar=true;
    int nuevaCantidad=0;
    do{
        system("cls");
        printf(" %15s\n", "\250C\242mo desea ingresar los datos?");
        printf(gray "1. Ingresar tienda manualmente\n" reset);
        printf(gray "2. Generar datos de prueba (%d tiendas)\n" reset, datosPrueba);
        printf(gray "3. Volver al men\243 principal\n" reset);

        bool generados=*datosGenerados;
        opcion =leerCadenaOpcion("Seleccione una opcion");
        switch(opcion){
            case 1:
                nuevaCantidad=ingresarNombreTienda(tiendas, cantidad);
                if(nuevaCantidad>cantidad) {
                    cantidad=nuevaCantidad;
                    printf(green "\n\41Tienda agregada exitosamente!\n" reset);
                }
                pausa();
                break;
            case 2:
                if(generados){
                    printf(orange "\n\41Error! Los datos de prueba ya fueron generados.\n" reset);
                    printf(yellow "No se pueden generar nuevamente para evitar nombres repetidos.\n" reset);
                }else if(cantidad+datosPrueba>tiendaMaxima){
                    printf(red "\n\41Error! No hay espacio para %d tiendas m\240s.\n" reset,datosPrueba);
                    printf("Espacio disponible: %d\n", tiendaMaxima-cantidad);
                }else{
                    cantidad=inicializarDatosPrueba(tiendas, cantidad);
                    *datosGenerados=true;
                    printf(green "\n\41Se han generado %d tiendas de prueba!\n" reset, datosPrueba);
                    printf(lightGreen "Esta opci\242n no se puede usar nuevamente.\n" reset);
                }
                pausa();
                break;
            case 3:
                continuar=false;
                break;
            default:
                printf(orange "Opci\242n err\242nea. Intente nuevamente.\n" reset);
                pausa();
                break;
        }
    }while(continuar);
    return cantidad;
}

//Funcion de la opcion 3
void mostrarReportes(Tienda tiendas[], int cantidad){
    int opcion;
    bool continuar=true;
    do{
        system("cls");
        printf(" %15s\n","Men\243 de reportes");
        printf(gray "1. Tiendas que cumplieron el plan mensual\n" reset);
        printf(gray "2. Tiendas que tuvieron la menor y la mayor venta\n" reset);
        printf(gray "3. Ventas totales de la cadena\n" reset);
        printf(gray "4. Tiendas que no alcanzaron a cumplir el 50%% del plan de ventas en diciembre\n" reset);
        printf(gray "5. Meses con ventas mayor al 40%% sobre el plan\n" reset);
        printf(gray "6. Volver al men\243 principal\n" reset);

        opcion = leerCadenaOpcion("Seleccione un reporte");
        switch(opcion){
            case 1:
                mostrarCumplimiento(tiendas, cantidad);
                pausa();
                break;
            case 2:
                mostrarExtremas(tiendas, cantidad);
                pausa();
                break;
            case 3:
                mostrarVentas(tiendas, cantidad);
                pausa();
                break;
            case 4:
                mostrarBajo50Diciembre(tiendas, cantidad);
                pausa();
                break;
            case 5:
                mostrarSuperior40(tiendas, cantidad);
                pausa();
                break;
            case 6:
                continuar=false;
                break;
            default:
                printf(orange "Opci\242n err\242nea. Intente nuevamente.\n" reset);
                pausa();
                break;
        }
    }while(continuar);
}

void flujoPrincipal(Tienda tiendas[], int *cantidad){
    int opcion;
    bool continuar=true;
    bool datosGenerados=false;

    do {
        system("cls");
        printf(" %15s\n", "Men\243 principal");
        printf(gray "1. Agregar tiendas\n" reset);
        printf(gray "2. Ver tiendas\n" reset);
        printf(gray "3. Ver reportes\n" reset);
        printf(gray "4. Salir\n" reset);
        opcion = leerCadenaOpcion("Seleccione una opci\242n");
        switch(opcion){
            case 1:
                *cantidad=menuEntradaDatos(tiendas, *cantidad, &datosGenerados);
                break;
            case 2:
                if(*cantidad>0){
                    mostrarTiendas(tiendas, *cantidad);
                }else{
                    printf(yellow "\n\41Error! No hay tiendas registradas.\n" reset);
                }
                pausa();
                break;
            case 3:
                if(*cantidad>0){
                    mostrarReportes(tiendas, *cantidad);
                }else{
                    printf(yellow "\n\41Error! No hay tiendas registradas.\n" reset);
                    pausa();
                }
                break;
            case 4:
                continuar=false;
                break;
            default:
                printf(orange "Opci\242n err\242nea. Intente nuevamente.\n" reset);
                pausa();
                break;
        }
    }while(continuar);
}
