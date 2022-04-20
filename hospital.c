
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
// gcc -o crud hospital.c -I /usr/include/postgresql/ -lpq
// ./hospital

//Metodos para el menu se la secretaria --------------------------------------------------------------------------------------------
void Alta_Paciente()    
{
printf("xd");
}

void Actualizar_Paciente()
{

}

void Eliminar_Paciente()
{

}

void Seleccionar_Paciente()
{


}

void MenuSecretaria()
{

}//Fin de menusecretaria

void MenuMedico()
{

}//Fin de menumedico


int main(int argc, char *argv[])
{
    int opcUsuario;

    do
    {
        printf("\nBienvenido al menu de usuarios\n");
        printf("\n 1.- Secretaria \n 2.- Medico \n 3.- Salir del menu \n ");
        printf("Elija su usuario: ");
        scanf("%opcUsuario", &opcUsuario);

        switch(opcUsuario)
        {
            case 1: //Secretaria
                PGconn *conex; 
                
                char host[15] = "localhost";
                char puerto[5] = "5432";
                char BD[15] = "aseguradora";
                char usuario[20], password[20];

                printf ("Ingrese su usuario: ");
                scanf ("%s",usuario);
                printf ("Ingrese la contraseña: ");
                scanf ("%s",password);
	
                conex = PQsetdbLogin(host, puerto, NULL, NULL, BD, usuario, password);

	            printf("\nProbando conexion con POSTGRESQL ...\n\n");

                if(PQstatus(conex) == CONNECTION_OK)
                { //Valida si la conexion fue exitosa
                    printf("Conexion exitosa\n"); 
                    MenuSecretaria(); //llamando al metodo MenuSecretaria
	            } else {
                    printf("Usuario o contraseña incorrectos\n");
	            } //Fin de la validacion de conexion a la BD

            break;

            case 2: //Medicos
                PGconn *conex; 
                
                char host[15] = "localhost";
                char puerto[5] = "5432";
                char BD[15] = "aseguradora";
                char usuario[20], password[20];

                printf ("Ingrese el usuario medico: ");
                scanf ("%s",usuario);
                printf ("Ingrese la contraseña: ");
                scanf ("%s",password);
	
                conex = PQsetdbLogin(host, puerto, NULL, NULL, BD, usuario, password);

	            printf("\nProbando conexion con POSTGRESQL ...\n\n");

                if(PQstatus(conex) == CONNECTION_OK)
                { //Valida si la conexion fue exitosa
                    printf("Conexion exitosa\n"); 
                    MenuMedico(); //llamando al metodo de medicos
	            } else {
                    printf("Usuario o contraseña incorrectos\n");
	            } //Fin de la validacion de conexion a la BD

            break;
                
            case 3:
                printf("Saliendo del programa principal...\n");
            break;

            default:
                printf("Digite una opcion correcta...\n");

        }//Fin del switch principal

    } while (opcUsuario!=3);
    

}//Fin del Main