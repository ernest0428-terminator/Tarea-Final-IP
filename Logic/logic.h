#include<stdbool.h>
#include<Logic/dats.h>

bool validarNombreUnico(Tienda tiendas[], int cantidad, const char nombre[]);
bool validarNombreSinNumeros(const char nombre[]);
float calcularTotalAnual(Tienda tienda);
void encontrarTiendasMenoresVentas(Tienda tiendas[], int cantidad, int indices[], int *numIndices);
void encontrarTiendasMayoresVentas(Tienda tiendas[], int cantidad, int indices[], int *numIndices);
float calcularTotalCadena(Tienda tiendas[], int cantidad);
float calcularPorcentajeCumplimiento(float ventas, float plan);

