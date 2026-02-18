#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<Logic/dats.h>

bool validarNombreUnico(Tienda tiendas[], int cantidad, const char nombre[]){
    int i;
    bool nombreUnico=true;
    for(i=0; i<cantidad && nombreUnico; i++){
        if(strcmp(tiendas[i].nombre, nombre)==0){
            nombreUnico=false;
        }
    }
    return nombreUnico;
}

bool validarNombreSinNumeros(const char nombre[]){
    int i;
    bool nombreSinNumeros=true;
    for(i=0; nombre[i] != '\0' && nombreSinNumeros; i++) {
        if(isdigit(nombre[i])){
            nombreSinNumeros=false;
        }
    }

    return nombreSinNumeros;
}

float calcularTotalAnual(Tienda tienda){
    int i;
    float total=0.0;
    for(i=0; i<meses; i++) {
        total += tienda.ventas[i];
    }
    return total;
}

void encontrarTiendasMenoresVentas(Tienda tiendas[], int cantidad, int indices[], int *numIndices){
    int i;
    float menorVenta;

    // Primero, crear una copia redondeada de los valores
    float ventasRedondeadas[tiendaMaxima];
    for(i=0; i < cantidad; i++){
        // Redondear a 2 decimales (centavos)
        ventasRedondeadas[i] = (float)((int)(tiendas[i].totalVentas * 100 + 0.5)) / 100.0;
        // Encontrar el valor mínimo en los valores redondeados
        menorVenta = ventasRedondeadas[0];

        if(ventasRedondeadas[i] < menorVenta){
            menorVenta = ventasRedondeadas[i];
        }
    }

    // Contar cuántas tiendas tienen ese valor mínimo redondeado
    *numIndices = 0;
    for(i=0; i<cantidad; i++){
        if(ventasRedondeadas[i] == menorVenta){
            indices[*numIndices] = i;
            (*numIndices)++;
        }
    }
}

void encontrarTiendasMayoresVentas(Tienda tiendas[], int cantidad, int indices[], int *numIndices){
    int i;
    float mayorVenta;

    // Primero, crear una copia redondeada de los valores
    float ventasRedondeadas[tiendaMaxima];
    for(i=0; i<cantidad; i++) {
        // Redondear a 2 decimales (centavos)
        ventasRedondeadas[i] = (float)((int)(tiendas[i].totalVentas * 100 + 0.5)) / 100.0;
        // Encontrar el valor máximo en los valores redondeados
        mayorVenta = ventasRedondeadas[0];

        if(ventasRedondeadas[i] > mayorVenta){
            mayorVenta = ventasRedondeadas[i];
        }
    }

    // Contar cuántas tiendas tienen ese valor máximo redondeado
    *numIndices = 0;
    for(i=0; i<cantidad; i++){
        if(ventasRedondeadas[i] == mayorVenta){
            indices[*numIndices] = i;
            (*numIndices)++;
        }
    }
}

float calcularTotalCadena(Tienda tiendas[], int cantidad){
    float total = 0.0;
    int i;
    for(i=0; i<cantidad; i++){
        total += tiendas[i].totalVentas;
    }
    return total;
}

float calcularPorcentajeCumplimiento(float ventas, float plan){
    float porcentaje=0;
    if(plan==0.0){
        porcentaje=0.0;
    }else{
        porcentaje=(ventas*100.0)/plan;
    }
    return porcentaje;
}
