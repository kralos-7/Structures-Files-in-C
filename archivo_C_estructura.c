#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura alumno
struct alumno{
     char matricula[11];
     char nombre[30];
     char apellido_M[45];
     char apellido_P[45];
     float estatura;
     int edad;
     struct alumno *siguiente;
};

struct alumno *estudiante = NULL;
struct alumno *lista = NULL;

int n_alumnos;

FILE *archivo;

void cargar_Archivo(){	 	

	char aux_matricula[11];
    char aux_nombre[30];
    char aux_apellido_M[45];
    char aux_apellido_P[45];
    float aux_estatura;
    int aux_edad,i;
    
    struct alumno *aux = NULL;
	
 	archivo = fopen ( "fichero.txt", "r" );
 	
 	if (archivo == NULL)
 	{
		printf("El archivo no existe\n");
		n_alumnos = 0;
	}
 	else {
		fscanf(archivo,"%d\n",&n_alumnos);		
		printf("Hay %d alumnos\n",n_alumnos);
		
		while (fscanf(archivo, "%d | %s | %s | %s | %s | %d | %f \n", 
							&i, 
							&aux_matricula,
							&aux_nombre,
							&aux_apellido_M,
							&aux_apellido_P,
							&aux_edad,
							&aux_estatura ) == 7){			
			
			estudiante = (struct alumno*)malloc(sizeof(struct alumno));	
			
			strcpy(estudiante->matricula , aux_matricula);
			strcpy(estudiante->nombre , aux_nombre);
			strcpy(estudiante->apellido_P , aux_apellido_M);
			strcpy(estudiante->apellido_M , aux_apellido_P);
			estudiante->edad = aux_edad;
			estudiante->estatura = aux_estatura;

			if(lista == NULL)
			{
				lista=estudiante;
				estudiante->siguiente = NULL;
			}
			else
			{
				aux = lista;
				while(aux->siguiente != NULL)
				{
					aux = aux->siguiente;
				}
				aux->siguiente = estudiante;
				estudiante->siguiente = NULL;
			}      	
						
		} 			
		fclose(archivo); 	
	}	
}

int menu(){
	int  op = -1;
	printf("MENU\n");
	printf("1.- Agregar alumno\n");
	printf("2.- Mostar alumnos\n");
	printf("0.- Salir\n");
	printf("> ");
	scanf("%d",&op);
	return op;
}

void agrega(){		
	fflush(stdin);
    struct alumno *aux = NULL;
    estudiante = (struct alumno*)malloc(sizeof(struct alumno));	
	
	getchar(); 				
	
	printf("Esriba la matrícula del alumno: ");				
	gets(estudiante->matricula);
	printf("Esriba el nombre del alumno: ");
	gets(estudiante->nombre);
	printf("Esriba el apellido paterno del alumno: ");
	gets(estudiante->apellido_P);
	printf("Esriba el apellido materno del alumno: ");
	gets(estudiante->apellido_M);
	printf("Esriba la edad del alumno: ");
	scanf("%d",&(estudiante->edad));
	printf("Esriba la estatura del alumno: ");
	scanf("%f",&(estudiante->estatura));
	
	if(lista == NULL)
    {
		lista=estudiante;
        estudiante->siguiente = NULL;
    }
    else
    {
		aux = lista;
        while(aux->siguiente != NULL)
        {
			aux = aux->siguiente;
        }
        aux->siguiente = estudiante;
        estudiante->siguiente = NULL;
    }      	
	
}

void guarda(){
	archivo = fopen ("fichero.txt","w+");

	printf("Registros a guardar %d\n", n_alumnos);

 	if (archivo == NULL)
 	{
		printf("El archivo no se puede crear o abrir\n");
	}
 	else {

		struct alumno *aux = NULL;
		int i=0;

		fprintf(archivo, "%d \n", n_alumnos);

		for(aux=lista;aux!=NULL;aux=aux->siguiente)
		{
			fprintf(archivo, "%d | ", i);
			fprintf(archivo, "%s | ", aux->matricula);
			fprintf(archivo, "%s | ", aux->nombre);
			fprintf(archivo, "%s | ", aux->apellido_P);
			fprintf(archivo, "%s | ", aux->apellido_M);
			fprintf(archivo, "%d | ", aux->edad);
			fprintf(archivo, "%.2f \n", aux->estatura);
			i++;
		}
		fclose(archivo);
	}	 	
}

void listar(){
	if(lista == NULL)
    {
		printf("\nNo hay estudiantes en la lista\n\n"); 
        return;          
    }else
    {      
		struct alumno *aux = NULL;
		int i=0;
            
		for(aux=lista;aux!=NULL;aux=aux->siguiente)
		{                 
			printf("No. #%d\n", i);
			printf("Matrícula: %s\n", aux->matricula);
			printf("Nombre: %s\n", aux->nombre);
			printf("Apellido paterno: %s\n", aux->apellido_P);
			printf("Apellido materno: %s\n", aux->apellido_M);
			printf("Edad: %d\n", aux->edad);
			printf("Estatura: %.2f\n", aux->estatura);		
			i++;
		} 
	} 	
}

int main(){		
	int opcion;
	
	cargar_Archivo();
	
	do{
		opcion = menu();
		switch(opcion){
			case 0:
				printf("Salir\n");
			break;
			case 1:
				agrega();
				n_alumnos++;
				guarda();
				printf("Se agrego un alumno\n");
			break;
			case 2:
				listar();
			break;
			default:
				printf("Error: opción no existe\n");
			break;
		}
	}while(opcion!=0);
	return 0;
}
