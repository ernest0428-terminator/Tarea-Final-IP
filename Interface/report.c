#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<Interface/interface.h>
#include<Logic/dats.h>
#include<Logic/colors.h>
#include<Logic/logic.h>

//Funciones de Reportes

//Inciso a
void mostrarCumplimiento(Tienda tiendas[], int cantidad){
    char* allMeses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun",
                     "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    int i;
    int mes;

    system("cls");
    printf("Reporte de cumplimiento\n\n");

    // Encabezado de la tabla
        printf("%-20s", "Tienda");
        for(mes=0; mes<meses; mes++){
            printf(" | %-4s", allMeses[mes]);
        }
        printf(" | Total\n");
        lineaDivision

        // Datos de cada tienda
        for(i=0; i<cantidad; i++) {
            printf("%-20s", tiendas[i].nombre);

            for(mes=0; mes<meses; mes++){
                float porcentaje = calcularPorcentajeCumplimiento(
                    tiendas[i].ventas[mes], tiendas[i].plan[mes]);

                if(porcentaje>=100.0){
                    printf(green " | %3.0f%%" reset, porcentaje); // Verde para cumplido
                }else{
                    printf(red " | %3.0f%%" reset, porcentaje); // Rojo para no cumplido
                }
            }

            // Porcentaje total anual
            float promedioAnual=calcularPorcentajeCumplimiento(
                tiendas[i].totalVentas, tiendas[i].totalPlan);

            if(promedioAnual >= 100.0){
                printf(green " | %7.1f%%" reset, promedioAnual);
            }else{
                printf(red " | %7.1f%%" reset, promedioAnual);
            }

            saltoLinea
        }
        lineaDivision
        printf("Leyenda: ");
        printf(green "Cumplido" reset);
        printf(" | ");
        printf(red "No cumplido \n" reset);
        saltoLinea
}

//Inciso b
void mostrarExtremas(Tienda tiendas[], int cantidad){
    int indicesMenores[tiendaMaxima];
    int indicesMayores[tiendaMaxima];
    int numMenores=0;
    int numMayores=0;
    int i;

    // Encontrar todas las tiendas con menor y mayor venta
    encontrarTiendasMenoresVentas(tiendas, cantidad, indicesMenores, &numMenores);
    encontrarTiendasMayoresVentas(tiendas, cantidad, indicesMayores, &numMayores);

    system("cls");
    printf("Tiendas con menor y mayor ventas\n\n");

    printf("%-14s | %-15s | %-14s\n", "Tipo", "Nombre", "Ventas totales");
    lineaDivision



    if(numMenores>0){
        printf("Menores ventas (%d tienda%s):\n", numMenores, (numMenores>1 ? "s" : ""));
        for(i=0; i<numMenores; i++) {
            printf("  %-12s | %-15s | $%10.2f\n",
                   (i==0 ? "" : ""),
                   tiendas[indicesMenores[i]].nombre,
                   tiendas[indicesMenores[i]].totalVentas);
        }
    }

    // Mostrar todas las tiendas con mayor venta
    if(numMayores>0){
        printf("Mayores ventas (%d tienda%s):\n", numMayores, (numMayores>1 ? "s" : ""));
        for(i=0; i<numMayores; i++){
            printf("  %-12s | %-15s | $%10.2f\n",
                   (i==0 ? "" : ""),
                   tiendas[indicesMayores[i]].nombre,
                   tiendas[indicesMayores[i]].totalVentas);
        }
    }

    saltoLinea
}

//Inciso c - Modificada para usar totalGeneralVentas
void mostrarVentas(Tienda tiendas[], int cantidad){
    float total=0.0;
    float totalPlan=0.0;
    int i;

    // Calcular totales generales
    for(i=0; i<cantidad; i++){
        total += tiendas[i].totalVentas;
        totalPlan += tiendas[i].totalPlan;
    }

    system("cls");
    printf("Ventas totales de la cadena\n\n");

    printf("%-30s $%10.2f\n", "Total de ventas realizadas:", total);
    printf("%-30s $%10.2f\n", "Total del plan de ventas:", totalPlan);
    printf("%-30s $%10.2f\n", "Promedio por tienda:", total / cantidad);

    float porcentajeTotal=calcularPorcentajeCumplimiento(total, totalPlan);
    printf("%-30s %6.1f%%\n", "Cumplimiento total:", porcentajeTotal);
    saltoLinea
}

//Inciso d
void mostrarBajo50Diciembre(Tienda tiendas[], int cantidad){
    system("cls");
    printf("Tiendas que no alcanzaron a cumplir el 50%% del plan de ventas en diciembre\n\n");

    printf("%-20s | %-10s | %-10s | %-10s\n", "Nombre", "Plan", "Ventas", "Cumplimiento");
    lineaDivision

    int i;
    bool encontrada=false;

    for(i=0; i<cantidad; i++) {
        float porcentaje=calcularPorcentajeCumplimiento(
            tiendas[i].ventas[11], tiendas[i].plan[11]);

        if(porcentaje<50.0){
            printf("%-20s | $%-10.2f | $%-10.2f | %6.1f%%\n",
                   tiendas[i].nombre,
                   tiendas[i].plan[11],
                   tiendas[i].ventas[11],
                   porcentaje);
            encontrada = true;
        }
    }

    if(!encontrada) {
        printf("\nNinguna tienda tuvo menos del 50%% del plan en diciembre\n");
    }
    saltoLinea
}

//Inciso e
void mostrarSuperior40(Tienda tiendas[], int cantidad){
    char* allMeses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                     "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    system("cls");
    printf("Meses con ventas superiores al 40%% sobre el plan\n\n");

    printf("%-12s | %-12s | %-10s | %-6s\n",
           "Mes", "Plan total", "Ventas", "Cumplimiento");
    lineaDivision

    int mes;
    int i;
    bool encontrado=false;

    for(mes=0; mes<meses; mes++){
        float totalPlan = 0.0;
        float totalVentas = 0.0;

        for(i=0; i<cantidad; i++){
            totalPlan += tiendas[i].plan[mes];
            totalVentas += tiendas[i].ventas[mes];
        }

        if(totalPlan>0){
            float porcentaje=calcularPorcentajeCumplimiento(totalVentas, totalPlan);
            if(porcentaje>140.0) { // Más del 40% sobre el plan
                printf("%-12s | $%10.2f | $%10.2f | %6.1f%%\n",
                       allMeses[mes], totalPlan, totalVentas, porcentaje);
                encontrado = true;
            }
        }
    }

    if(!encontrado) {
        printf("\nNo hay meses con m\240s del 40%% sobre el plan total.\n");
    }
    saltoLinea
}
