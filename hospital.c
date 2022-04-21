
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
// gcc -o crud hospital.c -I /usr/include/postgresql/ -lpq
// ./hospital

/*conectaar con postgres 
--sudo -i -u postgres
--psql
*/

PGconn *conex; 
PGresult *resultado;
PGresult *ress;

//Metodos para el menu de la secretaria --------------------------------------------------------------------------------------------
void Alta_Paciente()    
{

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

//Metodos de los menus---------------------------------------------------------------------------
void MenuSecretaria()
{
    //variables
    int opcS, opcC, opcP, opcR;
    int opcPac, opcCita, opcCons, opcExp, opcMed, opcDiag;

    do
    {
        printf("\nBienvenido al menu de secretarios\n");
        printf("\n 1.- Catalogos \n 2.- procesos \n 3.- Reportes \n 4.- Salir \n");
        printf("Elija una opcion: ");
        scanf("%i", &opcS);

        switch(opcS)
        {
            case 1: //opcion catalogos secretaria

                do
                {
                    printf("\n Bienvenido a Catalogos \n");
                    printf("\n 1.- Paciente \n 2.- Cita \n 3.- Consulta \n 4.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcC);

                    switch(opcC)
                    {
                        case 1:
                            do
                            {
                                printf("\n-----Pacientes-----\n");
                                printf("\n 1.- Alta paciente \n 2.- Baja paciente \n 3.- Modificar pacientes \n 4.- Consultar pacientes \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcPac);

                                switch(opcPac)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        //Metodo
                                    break;

                                    case 4:
                                        //Metodo
                                    break;

                                    case 5:
                                        printf("\n Saliendo de paciente...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion valida... \n");
                                }//Fin del switch pacientes

                            }while(opcPac!=5);//Fin del while pacientes
                            
                        break;

                        case 2:

                            do
                            {
                                printf("\n-----Citas-----\n");
                                printf("\n 1.- Alta cita \n 2.- Baja cita \n 3.- Modificar cita \n 4.- Consultar citas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCita);

                                switch(opcCita)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        //Metodo
                                    break;

                                    case 4:
                                        //Metodo
                                    break;

                                    case 5:
                                        printf("\n Saliendo de citas...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion valida... \n");
                                }//Fin del switch citas

                            }while(opcCita!=5);//Fin del while citas
                        break;

                        case 3:

                            do
                            {
                                printf("\n-----Consultas-----\n");
                                printf("\n 1.- Alta consulta \n 2.- Baja consulta \n 3.- Modificar consulta \n 4.- Consultar cconsultas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCons);

                                switch(opcCons)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        //Metodo
                                    break;

                                    case 4:
                                        //Metodo
                                    break;

                                    case 5:
                                        printf("\n Saliendo de consultas...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion valida... \n");
                                }//Fin del switch consultas

                            }while(opcCons!=5);//Fin del while consultas

                        break;

                        case 4:
                            printf("\n Saliendo de catalogos...\n");
                        break;

                        default:
                            printf("\n Digite una opcion correcta...\n");

                    }//Fin del switch opcC

                }while(opcC!=4);
                
            break;

            case 2: //opcion procesos secretaria

                do
                {
                    printf("\n Bienvenido a Procesos \n");
                    printf("\n 1.- Expedientes \n 2.- Medico \n 3.- Diagnosticos \n 4.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcP);

                    switch(opcP)
                    {
                        case 1:
                            
                            do
                            {
                                printf("\n-----Expedientes-----\n");
                                printf("\n 1.- Ver expediente \n 2.- Borrar expediente \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcExp);

                                switch(opcExp)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        printf("\n Saliendo de expedientes...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }//Fin del switch expediente

                            }while(opcExp); //Fin while de expediente
                            
                        break;

                        case 2:

                            do
                            {
                                printf("\n-----Medicos-----\n");
                                printf("\n 1.- Ver medicos \n 2.- Especialidad de medicos \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcMed);

                                switch(opcMed)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        printf("\n Saliendo de medicos...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }//Fin del switch de medicos
                                
                            }while(opcMed!=3);//Fin while medicos en menu secretaria
                            
                        break;

                        case 3:

                            do
                            {
                                printf("\n-----Diagnosticos-----\n");
                                printf("\n 1.- Ver diagnosticos \n 2.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcDiag);

                                switch(opcDiag)
                                {
                                    case 1:
                                        //Metodo
                                    break;

                                    case 2:
                                        printf("\n Saliendo de diagnosticos...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }//Fin switch diagnostico

                            }while(opcDiag!=2);//Fin del while diagnosticos secretaria
                            
                        break;
                        
                        case 4:
                            printf("\n Saliendo de procesos...\n");
                        break;

                        default:
                            printf("\n Digite una opcion correcta...\n");

                    }//Fin del switch opcP

                }while(opcP!=4);

            break;

            case 3://opcion reportes secretaria

                do
                {
                    printf("\n Bienvenido a Reportes \n");
                    printf("\n B) Paciente y medico con mas edad \n C) Promedio de edades de pacientes y medicos \n E) Numero de consultas al dia por medico \n 4.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcR);

                    switch(opcR)
                    {
                        case 1:
                            //Metodo
                        break;

                        case 2:
                            //Metodo
                        break;

                        case 3:
                            //Metodo
                        break;

                        case 4:
                            printf("\n Saliendo de reportes...\n");
                        break;

                        default:
                            printf("\n Digite una opcion corretca...\n");

                    }//Fin del switch opcR

                }while(opcR!=4);

            break;

            case 4:
                printf("\n Saliendo del menu de secretarios...\n");
            break;

            default:
                printf("\n Seleccione una opcion valida secretaria...\n");
        }

    }while(opcS!=4);//Fin del ciclo secretaria

}//Fin de menusecretaria


void MenuMedico()
{
    int opcM;

    do
    {
        printf("\nBienvenido al menu de medicos\n");
        printf("\n 1.- Catalogos \n 2.- procesos \n 3.- Reportes \n 4.- Salir \n");
        printf("Elija una opcion: ");
        scanf("%i", &opcM);

        switch(opcM)
        {
            case 1: //opcion catalogos medico

            break;

            case 2: //opcion procesos medico

            break;

            case 3://opcion reportes medico

            break;

            case 4:
                printf("\n Saliendo del menu de medicos...\n");
            break;

            default:
                printf("\n Seleccione una opcion valida medico...\n");
        }

    }while(opcM!=4);//Fin del ciclo secretaria

}//Fin de menu medico


//main
int main(int argc, char *argv[])
{
    int opcUsuario;
    char host[15] = "localhost";
    char puerto[5] = "5432";
    char BD[15] = "hospital";
    char usuario[20];
    char password[20];

    do
    {
        printf("\nBienvenido al hospital 'Sal vivo si puedes'\n");
        printf("\n 1.- Secretaria \n 2.- Medico \n 3.- Salir \n ");
        printf("Elija su opcion: ");
        scanf("%opcUsuario", &opcUsuario);

        switch(opcUsuario)
        {
            case 1: //Secretaria

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
                printf("\n Saliendo del programa principal...\n");
            break;

            default:
                printf("\n Digite una opcion correcta...\n");

        }//Fin del switch principal

    } while (opcUsuario!=3);

}//Fin del Main