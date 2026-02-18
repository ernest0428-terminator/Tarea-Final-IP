#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>
#include<Logic/dats.h>
#include<Logic/colors.h>
#include<Logic/logic.h>

void pausa(){
    system("pause");
    system("cls");
}

void bienvenida(){
    char* mensaje[]={"Bienvenido, este programa se encargar\240 de realizar el reporte de ventas\n",
                      "de una cadena de tiendas, a partir de su plan de ventas y las ventas realizadas en cada mes\n\n"
    };
    int i;
    int j;
    for(i=0; i<2; i++){
        for(j=0; mensaje[i][j] != '\0'; j++){
            printf("%c", mensaje[i][j]);
            fflush(stdout);
            Sleep(25);
        }
    }
    pausa();
}

//Funciones de lectura de datos
int leerCadenaOpcion(const char *mensaje){
    char entrada[5];
    int opcion = -1;
    int i;
    bool esNumeroValido = true;

    printf("%s: ", mensaje);
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    // Validar que todos los caracteres sean dígitos y no haya punto
    esNumeroValido = true;
    for(i=0; entrada[i] != '\0' && esNumeroValido; i++){
        if(!isdigit(entrada[i])) {
            esNumeroValido = false;
        }
    }

    // También validar que no esté vacío
    if(entrada[0] != '\0' && esNumeroValido){
        opcion = atoi(entrada);
    }else{
        opcion = -1; // Valor inválido
    }

    return opcion;
}

void leerCadenaTexto(const char *mensaje, char cadena[], int max){
    bool cadenaValida=false;
    int i;
    bool tieneCaracter=false;

    do {
        printf("%s: ", mensaje);
        fgets(cadena, max, stdin);
        cadena[strcspn(cadena, "\n")] = '\0';

        // Verificar si tiene al menos un carácter que no sea espacio
        tieneCaracter=false;
        for(i=0; cadena[i] != '\0'; i++){
            if(isalpha(cadena[i])){
                tieneCaracter=true;
            }
        }

        if(!tieneCaracter){
            printf(orange "\41Error! Debe ingresar alg\243n texto v\240lido (no solo espacios).\n" reset);
            pausa();
        }else{
            cadenaValida=true;
        }

    } while(!cadenaValida);
}

float leerFlotante(const char *mensaje, float min, float max){
    char entrada[10];
    float valor=-1.0;
    int i;
    int cantPuntos = 0;
    bool formatoValido = true;
    bool tieneDigito = false;
    bool tieneEspacio = false;

    printf("%s ($%.2f-$%.2f): $", mensaje, min, max);
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    // Procesar cadena
    for(i = 0; entrada[i] != '\0'; i++) {
        if(entrada[i] != ' ') {
            tieneEspacio=true;
        }

        if(formatoValido){
            if(isdigit(entrada[i])) {
                tieneDigito = true;
            }else if(entrada[i] == '.') {
                cantPuntos++;
                if(cantPuntos>1){
                    formatoValido = false;
                }
            }else if(!(i == 0 && entrada[i] == '-')) {
                formatoValido = false;
            }
        }
    }

    if(entrada[0] != '\0'){
        if(!tieneEspacio){
            valor=-1.0;
        }else if(!formatoValido || !tieneDigito){
            valor=-2.0f;
        }else{
            valor=atof(entrada);
        }
    }

    return valor;
}

//Funciones de validación
float validarValorTienda(const char *nombreMes, const char *tipoDeCaso, float min, float max){
    char mensaje[20];
    float valor;
    bool valorValido = false;

    do{
        sprintf(mensaje, "%s %s", tipoDeCaso, nombreMes);
        valor=leerFlotante(mensaje,min,max);
        if(valor==-1.0){
            printf(orange "\41Error! Formato inv\240lido.\n" reset);
            printf(orange "Los datos no pueden contener espacios.\n" reset);
            printf(yellow "Intente nuevamente.\n" reset);
            pausa();
        }else if(valor==-2.0){
            printf(orange "\41Error! Formato inv\240lido.\n" reset);
            printf(orange "Los datos no pueden contener letras, ni m\240s de un punto decimal.\n" reset);
            printf(yellow "Intente nuevamente.\n" reset);
            pausa();
        }else if(valor<=min || valor>max){
            printf(orange "\41Error! Debe ser entre $%.2f y $%.2f\n" reset, min, max);
            printf(yellow "Intente nuevamente.\n" reset);
            pausa();
        }else{
            valorValido = true;
        }
        fflush(stdin);

    } while(!valorValido);

    return valor;
}

bool validarNombreCompleto(Tienda tiendas[], int cantidad, const char nombre[], char mensajeError[]){
    bool nombreValido = true;
    int i;

    // Inicializar mensaje de error vacío
    mensajeError[0] = '\0';

    // 1. Validar que no esté vacío
    if(strlen(nombre) == 0) {
        strcpy(mensajeError, "El nombre no puede estar vac\241o");
        nombreValido = false;
    }
    // 2. Validar que no tenga números
    else if(!validarNombreSinNumeros(nombre)) {
        strcpy(mensajeError, "El nombre no debe contener n\243meros");
        nombreValido = false;
    }
    // 3. Validar que no tenga caracteres especiales (solo letras y espacios)
    else {
        for(i = 0; nombre[i] != '\0' && nombreValido; i++) {
            if(!isalpha(nombre[i]) && nombre[i] != ' '){
                strcpy(mensajeError, "El nombre solo puede contener letras y espacios");
                nombreValido = false;
            }
        }
    }
    // 4. Validar que sea único (si pasó las validaciones anteriores)
    if(nombreValido && !validarNombreUnico(tiendas, cantidad, nombre)) {
        strcpy(mensajeError, "Ya existe una tienda con ese nombre");
        nombreValido = false;
    }

    return nombreValido;
}

//Funciones de ingreso de datos
void ingresarPlanTienda(Tienda tiendas[], int cantidad){
    char* allMeses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                     "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    system("cls");
    printf("Plan de ventas\n");

    int i;
    tiendas[cantidad].totalPlan = 0.0; // Inicializar total
    for(i=0; i<meses; i++){
        tiendas[cantidad].plan[i]=validarValorTienda(allMeses[i], "Plan de", 0.0, 1000000.0);
        tiendas[cantidad].totalPlan += tiendas[cantidad].plan[i]; // Acumular
    }
}

int ingresarVentasTienda(Tienda tiendas[], int cantidad){
    char* allMeses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                     "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    system("cls");
    printf("Ventas realizadas\n");

    int i;
    tiendas[cantidad].totalVentas = 0.0; // Inicializar total
    for(i=0; i<meses; i++){
        tiendas[cantidad].ventas[i]=validarValorTienda(allMeses[i], "Ventas de", 0.0, 1000000.0);
        tiendas[cantidad].totalVentas += tiendas[cantidad].ventas[i]; // Acumular
    }

    return cantidad + 1;
}

int ingresarNombreTienda(Tienda tiendas[], int cantidad){

    // Verificar límite
    if(cantidad>=tiendaMaxima) {
        printf(orange "\n\41Error! L\241mite de tiendas alcanzado (%d)\n" reset, tiendaMaxima);
        pausa();
    }else{
        char nombre[nombreMaximo];
        bool nombreValido = false;
        char mensajeError[100];
        do {
            system("cls");
            printf("Nueva tienda\n");
            leerCadenaTexto("Nombre de la tienda", nombre, nombreMaximo);
            if(validarNombreCompleto(tiendas, cantidad, nombre, mensajeError)) {
                nombreValido = true;
            }else{
                printf(red "Error: %s\n" reset, mensajeError);
                printf(orange "Por favor, ingrese un nombre v\240lido.\n\n" reset);
                pausa();
            }
        } while(!nombreValido);

        // Si llegamos aquí, el nombre es válido
        strcpy(tiendas[cantidad].nombre, nombre);
        ingresarPlanTienda(tiendas, cantidad);
        cantidad=ingresarVentasTienda(tiendas, cantidad);
    }

    return cantidad;
}

int inicializarDatosPrueba(Tienda tiendas[], int cantidad){
    srand(time(NULL));

    // Nombres de tiendas de prueba
    char* nombresPrueba[] = {
        "Electro Center", "Moda Express", "Tecnomundo",
        "DeportesMax", "FarmaSalud", "Jugueter\241a Fazbear",
        "Muebles-Hogar", "Florer\241a L\242pez", "Zapater\241a Dave",
        "Belleza total",
    };

    int i;
    int mes;
    int indiceNombre=0;

    for(i=cantidad; i<cantidad+datosPrueba; i++){
        strcpy(tiendas[i].nombre, nombresPrueba[indiceNombre]);
        indiceNombre++;

        // Generar datos aleatorios para cada mes
        tiendas[i].totalPlan = 0.0;
        tiendas[i].totalVentas = 0.0;

        for(mes=0; mes<meses; mes++){
            // Plan: entre 1000 y 20000
            float plan = 1000 + rand() % 8001;
            tiendas[i].plan[mes] = plan;
            tiendas[i].totalPlan += plan;

            // Para los primeros 11 meses: ventas entre 80% y 150%
            float factor;

            if(mes < 11){ // Enero a Noviembre
                factor = 0.8 + (rand() % 131) / 100.0; // 0.8 a 2.1
            }else{ // Diciembre (mes 11)
                // Para diciembre, generar algunos casos con <50%
                int randomDic = rand() % 100;
                if(randomDic < 30){ // 30% de tiendas con <50% en diciembre
                    factor = 0.1 + (rand() % 40) / 100.0; // 0.1 a 0.5
                }else{ // 70% con rendimiento normal
                    factor = 0.8 + (rand() % 131) / 100.0; // 0.8 a 2.1
                }
            }
            float venta=plan*factor;
            tiendas[i].ventas[mes] = venta;
            tiendas[i].totalVentas += venta;
        }
    }

    return cantidad+datosPrueba;
}

//Funcion de la opcion 2 del menú principal
void mostrarTiendas(Tienda tiendas[], int cantidad){
    int i;
    system("cls");
    printf("Listado de ventas\n\n");
    printf("%-20s | %-11s | %-11s | %-10s\n",
           "Nombre", "Plan", "Ventas", "Cumplimiento");
    lineaDivision

    for(i=0; i<cantidad; i++){
        float porcentaje=calcularPorcentajeCumplimiento(
            tiendas[i].totalVentas, tiendas[i].totalPlan);

        printf("%-20s | $%-10.2f | $%-10.2f | %10.2f%%\n",
               tiendas[i].nombre,
               tiendas[i].totalPlan,
               tiendas[i].totalVentas,
               porcentaje);
    }
    lineaDivision
    saltoLinea
}
