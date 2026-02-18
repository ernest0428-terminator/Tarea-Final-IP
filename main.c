#include<stdio.h>
#include<Interface/interface.h>
#include<Interface/report.h>
#include<Interface/menu.h>
#include<Logic/dats.h>
#include<Logic/colors.h>
#include<Logic/logic.h>

int main(void){
    Tienda tiendas[tiendaMaxima];
    int cantidad=0;
    bienvenida();
    flujoPrincipal(tiendas, &cantidad);
    printf(lightGreen "\nPrograma finalizado. \41Gracias por usar!\n" reset);
    pausa();
    return 0;
}
