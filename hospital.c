#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
#include "mpi.h"

// mpicc -o crud hospital.c -I /usr/include/postgresql/ -lpq
// ./crud

/*conectar con postgres
--sudo -i -u postgres
--psql
*/

PGconn *bd;
PGresult *resultado;
PGresult *ress;
PGresult *ressu;
PGresult *resu;
PGresult *resule;
PGresult *in;

int id;       /*IDENTIFICADOR DEL PROCESO*/
int numprocs; /*NUMERO DE PROCESOS*/

// tiempos de los procesos del menu principal y general
double tmpinic = 0.0; /*TIEMPO INICIO DE LA EJECUCION*/
double tmpfin;        /*TIEMPO FINAL DE LA EJECUCION*/
double tmp1s = 0.0;
double tmp1fs;
double tmp2s = 0.0;
double tmp2fs;
double tmp3m = 0.0;
double tmp3fm;

// tiempo de la secretaria
double tmp1sc = 0.0;
double tmp1fsc;
double tmp2sp = 0.0;
double tmp2fsp;
double tmp3sr = 0.0;
double tmp3fsr;

// tiempos del medico
double tmp1mc = 0.0;
double tmp1fmc;
double tmp2mp = 0.0;
double tmp2fmp;
double tmp3mr = 0.0;
double tmp3fmr;

// metodo para limpiar el buffer
void empty_stdin()
{
    int s;
    do
    {
        s = getchar();
    } while (s != '\n' && s != EOF);
}

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀█ ─█▀▀█ ░█▀▀█ ▀█▀ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ ░█▀▀▀
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█▄▄█ ░█▄▄█ ░█─── ░█─ ░█▀▀▀ ░█░█░█ ─░█── ░█▀▀▀
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█─── ░█─░█ ░█▄▄█ ▄█▄ ░█▄▄▄ ░█──▀█ ─░█── ░█▄▄▄

void Alta_Paciente()
{ 
    int num_paciente, edad_p, respAddP, opcRep, c, d, aFila, aColumna;
    char nombre_p[50], appat_p[50], apmat_p[50], direccion_p[60], addPaciente[700];
    setbuf(stdin, NULL);

<<<<<<< HEAD
    printf(" || Listado de pacientes ||\n");
    sprintf(addPaciente, "select * from Paciente");
    resultado = PQexec(bd, addPaciente);
    printf("Opcion SQL antes de ejecutarse: %s\n\n", addPaciente);
    if (resultado != NULL)
    {                    
        aFila = PQntuples(resultado);
        aColumna = PQnfields(resultado);
        printf(" NUM_PACIENTE  |           NOMBRE COMPELTO         |     EDAD      |   DIRECCION    |\n\n");
        for (c = 0; c < aFila; c++)
        {            
            for ( d = 0; d < aColumna; d++)
            {
                printf("%s\t | \t ", PQgetvalue(resultado, c, d));
            }//fin del for bColumna
            printf("\n");
        }//fin del for bFila                            
    }//fin del if-null
=======
    printf("Listado de pacientes: \n\n");

    sprintf(addPaciente, "select num_paciente, nombre_p from Paciente");
    resultado = PQexec(bd, addPaciente);
    printf("Opcion SQL antes de ejecutarse: %s\n\n", addPaciente);

    if (resultado != NULL)
    {

        aFila = PQntuples(resultado);
        aColumna = PQnfields(resultado);

        for (c = 0; c < aFila; c++)
        {
            for (d = 0; d < aColumna; d++)
            {
                printf("%s\t | \t ", PQgetvalue(resultado, c, d));
            } // fin del for bColumna
            printf("\n");
        } // fin del for bFila
        printf(" NUM_PACIENTE  |  NOMBRE \n\n");
    } // fin del if-null
>>>>>>> origin/master

    do
    {
        printf("\nIngresar el nombre del paciente: ");
        scanf("%s", nombre_p);
        printf("Ingresar el apellido paterno del paciente: ");
        scanf("%s", appat_p);
        printf("Ingresar el apellido materno del paciente: ");
        scanf("%s", apmat_p);
        setbuf(stdin, NULL);
<<<<<<< HEAD
        printf ("ban0\n");
        sprintf (addPaciente, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s';", nombre_p, appat_p, apmat_p);//busca si ya existe el paciente en nustra bdd
        resultado = PQexec(bd, addPaciente); //Ejecuta linea postgres
        printf ("ban1\n");
        //Si es uno quiere decir que si lo encontro, por lo tanto ya no se piden los demás datos
        if (PQntuples (resultado) == 1)
        {
            printf("ban 2\n");
=======
        sprintf(addPaciente, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre_p, appat_p, apmat_p); // busca si ya existe el cliente en nustra bdd
        resultado = PQexec(bd, addPaciente);                                                                                                               // Ejecuta linea postgres
        // Si es uno quiere decir que si lo encontro, por lo tanto ya no se piden los demás datos
        if (PQntuples(resultado) == 1)
        {
>>>>>>> origin/master
            printf("\nPaciente encontrado\n");
            printf("\nIngrese otro paciente!\n\n");
        }
        else
        {
<<<<<<< HEAD
            printf("ban 2.0n");
            printf("\nPaciente NO encontrado. Complete los datos\n");
            printf("Ingresar la edad del paciente: ");
            scanf("%i", &edad_p);
            printf("Ingresar la direccion del cliente: ");
=======

            printf("Ingresar la edad del paciente: \n");
            scanf("%i", &edad_p);
            empty_stdin();
            printf("Ingresar la direccion del cliente: \n");
>>>>>>> origin/master
            scanf("%s", direccion_p);
            empty_stdin();

            sprintf(addPaciente, "insert into Paciente ( nombre_p, appat_p, apmat_p, edad_p, direccion) values ( '%s', '%s', '%s', %i, '%s')", nombre_p, appat_p, apmat_p, edad_p, direccion_p);
            printf("Instruccion SQL antes de ejecutarse: %s", addPaciente);
            resultado = PQexec(bd, addPaciente);

            if (PQresultStatus(resultado) == PGRES_COMMAND_OK) 
            {
                printf("\n\nInserccion exitosa!\n\n");
            }
            else
            {
                printf("Inserccion sin exito! \n\n");
            }
        } // fin de la validacion
        do
        {
<<<<<<< HEAD
            printf ("\n¿Desea agregar otro Paciente?\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &respAddP);
            setbuf(stdin, NULL); //Limpiar el buffer
        }while  (respAddP != 1 && respAddP != 2);
    } while (respAddP == 1 );
=======
            printf("\n¿Desea agregar otro Paciente?\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &respAddP);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (respAddP != 1 && respAddP != 2);
    } while (opcRep == 1);
>>>>>>> origin/master
}

void Actualizar_Paciente()
{
    setbuf(stdin, NULL); // Limpiar el buffer
    int opcContinuar, opcModi, edad_p, edad_pNew, bFila, bColumna, a, b, c, d, num_paciente;
    char actPaciente[700];
    char nombre_paciente[50], appat_p[50], apmat_p[50], direccion[50];                             // guardan los anteriores datos
    char nombre_pacienteNew[50], appat_pNew[50], apmat_pNew[50], direccionNew[50], buscarPac[200]; // guardan los nuevos datos

    do
    {

        setbuf(stdin, NULL); // Limpiar el buffer
        sprintf(buscarPac, "select num_paciente, nombre_p from Paciente");
        resultado = PQexec(bd, buscarPac);
        printf("Opcion SQL antes de ejecutarse: %s\n\n", buscarPac);

        if (resultado != NULL)
        {

            bFila = PQntuples(resultado);
            bColumna = PQnfields(resultado);

            for (c = 0; c < bFila; c++)
            {
                for (d = 0; d < bColumna; d++)
                {
                    printf("%s\t | \t ", PQgetvalue(resultado, c, d));
                } // fin del for bColumna
                printf("\n");
            } // fin del for bFila
            printf(" NUM_PACIENTE  |  NOMBRE \n\n");
        } // fin del if-null

        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingresar  el numero del paciente el cual desea actualizar:\n");
        scanf("%i", &num_paciente);
        sprintf(buscarPac, "Select * from paciente where num_paciente=%i;", num_paciente);
        resultado = PQexec(bd, buscarPac);
        if (PQntuples(resultado) == 1)
        {

            if (resultado != NULL)
            {

                bFila = PQntuples(resultado);
                bColumna = PQnfields(resultado);

                for (a = 0; a < bFila; a++)
                {
                    for (b = 0; b < bColumna; b++)
                    {
                        printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                    } // fin del for bColumna
                    printf("\n\n");
                } // fin del for bFila
            }

            printf("Opciones ofrecidas para modificar: \n\n 1.-Nombre del paciente \n 2.- Apellido paterno del paciente \n 3.- Apellido materno del paciente \n 4.- Edad del paciente \n 5.- Direccion del paciente \n\n");
            printf("Ingrese una opcion:");
            scanf("%i", &opcModi);
            switch (opcModi)
            {
            case 1:                  // nombre
                setbuf(stdin, NULL); // Limpiar el buffer
                printf("Ingresar  el nombre anteriormente guardado:\n");
                scanf("%s", nombre_paciente);
                printf("Ingresar  el nombre nuevo a guardar\n");
                scanf("%s", nombre_pacienteNew);
                sprintf(actPaciente, "update Paciente set nombre_p = '%s' where nombre_p = '%s';", nombre_pacienteNew, nombre_paciente);
                resultado = PQexec(bd, actPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n\nActualizacion exitosa!\n\n");
                }
                else
                {
                    printf("Actualizacion sin exito! \n\n");
                }
                break;

            case 2:                  // appat_p
                setbuf(stdin, NULL); // Limpiar el buffer
                printf("Ingresar  el apellido paterno anteriormente guardado:\n");
                scanf("%s", appat_p);
                printf("Ingresar  el apellido paterno nuevo a guardar\n");
                scanf("%s", appat_pNew);
                sprintf(actPaciente, "update Paciente set appat_p = '%s' where appat_p = '%s';", appat_pNew, appat_p);
                resultado = PQexec(bd, actPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n\nActualizacion exitosa!\n\n");
                }
                else
                {
                    printf("Actualizacion sin exito! \n\n");
                }
                break;

            case 3:                  // apmat_p
                setbuf(stdin, NULL); // Limpiar el buffer
                printf("Ingresar  el apellido materno anteriormente guardado:\n");
                scanf("%s", apmat_p);
                printf("Ingresar  el apellido materno nuevo a guardar\n");
                scanf("%s", apmat_pNew);
                sprintf(actPaciente, "update Paciente set apmat_p = '%s' where apmat_p = '%s';", apmat_pNew, apmat_p);
                resultado = PQexec(bd, actPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n\nActualizacion exitosa!\n\n");
                }
                else
                {
                    printf("Actualizacion sin exito! \n\n");
                }
                break;

            case 4:                  // edad_p
                setbuf(stdin, NULL); // Limpiar el buffer
                printf("Ingresar  la edad anteriormente guardado:\n");
                scanf("%i", &edad_p);
                printf("Ingresar  la edad nueva a guardar\n");
                scanf("%i", &edad_pNew);
                sprintf(actPaciente, "update Paciente set edad_p = '%i' where edad_p = '%i';", edad_pNew, edad_p);
                resultado = PQexec(bd, actPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n\nActualizacion exitosa!\n\n");
                }
                else
                {
                    printf("Actualizacion sin exito! \n\n");
                }
                break;

            case 5:                  // direccion
                setbuf(stdin, NULL); // Limpiar el buffer
                printf("Ingresar  la direccion anteriormente guardado:\n");
                empty_stdin();
                scanf("%s", direccion);
                empty_stdin();
                printf("Ingresar  la direccion nueva a guardar\n");
                scanf("%s", direccionNew);
                sprintf(actPaciente, "update Paciente set direccion = '%s' where direccion = '%s';", direccionNew, direccion);
                resultado = PQexec(bd, actPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n\nActualizacion exitosa!\n\n");
                }
                else
                {
                    printf("Actualizacion sin exito! \n\n");
                }
                break;

            default:
                printf("Ingresar una opcion valida, \n\n");
                break;
            }
        }
        else
        {
            printf("Paciente no registrado en la BD\n\n");
        }

        do
        {
            setbuf(stdin, NULL); // Limpiar el buffer
            printf("Desea actualizar otro dato?\n\n 1.- Si\n 2.- No\n\n");
            printf("Ingrese una opcion:");
            scanf("%i", &opcContinuar);
        } while (opcContinuar != 1 && opcContinuar != 2);
    } while (opcContinuar == 1);
}

void Eliminar_Paciente()
{
    setbuf(stdin, NULL); // Limpiar el buffer
    char elimPaciente[500], buscarPac[250];
    int num_paciente, bFila, bColumna, opcSeguir;
    bFila = PQntuples(resultado);

    do
    {
        setbuf(stdin, NULL); // Limpiar el buffer
        sprintf(buscarPac, "select num_paciente, nombre_p from Paciente");
        resultado = PQexec(bd, buscarPac);
        printf("Opcion SQL antes de ejecutarse: %s\n\n", buscarPac);

        if (resultado != NULL)
        {

            bFila = PQntuples(resultado);
            bColumna = PQnfields(resultado);

            for (int c = 0; c < bFila; c++)
            {
                for (int d = 0; d < bColumna; d++)
                {
                    printf("%s\t | \t ", PQgetvalue(resultado, c, d));
                } // fin del for bColumna
                printf("\n");
            } // fin del for bFila
            printf(" NUM_PACIENTE  |  NOMBRE \n\n");
        } // fin del if-null

        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingresar  el numero del paciente el cual desea eliminar:\n");
        scanf("%i", &num_paciente);
        sprintf(buscarPac, "Select * from paciente where num_paciente=%i;", num_paciente);
        resultado = PQexec(bd, buscarPac);
        if (PQntuples(resultado) == 1)
        {
            printf("Pacientes encontrado! \n\n\n");
            sprintf(elimPaciente, "delete from Paciente where num_paciente = %i", num_paciente);
            printf("Opcion SQL antes de ejecutarse: %s\n\n", elimPaciente);
            resultado = PQexec(bd, elimPaciente);
            if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
            {
                printf("\n\nEliminacion exitosa!\n\n");
            }
            else
            {
                printf("Eliminacion sin exito! \n\n");
            }
        }
        else
        {
            printf("Paciente no registrado en la BD\n");
        }

        do
        {
            setbuf(stdin, NULL); // Limpiar el buffer
            printf("Desea eliminar otro paciente?\n\n 1.- Si\n 2.- No\n\n");
            scanf("%i", &opcSeguir);
        } while (opcSeguir != 1 && opcSeguir != 2);
    } while (opcSeguir == 1);
}

void Seleccionar_Paciente()
{
    setbuf(stdin, NULL);
    char selecPaciente[500];
    int opcSelecPac = 0, respConsP, bNum_Paciente, bFila, bColumna, a, b, opcVer;
    printf("Seleccionar una de las opciones ofrecidas: \n");
    do
    {

        do
        {
            printf("\n\n 1.- Selecionar todos los datos de un paciente en especifico \n\n 2.- Seleccionar un dato en especifico que desea ver de un paciente en especifico \n\n 3.- Ver los datos de todos los pacientes\n\n 4.- Salir\n\n");
            scanf("%i", &opcSelecPac);
            printf("Opcion: ");
            switch (opcSelecPac)
            {
            case 1: // caso para selecionar todos los datos de un paciente en especifico

                printf("\n\nOpcion uno:\n\n");
                printf("Ingresar  el numero del paciente deseado del cual desea ver todos los datos: \n");
                scanf("%i", &bNum_Paciente);
                sprintf(selecPaciente, "select * from Paciente where num_paciente = %i", bNum_Paciente);
                resultado = PQexec(bd, selecPaciente);
                printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                if (PQntuples(resultado) == 1)
                {
                    printf("Pacientes encontrado! \n\n\n");
                    printf("Mostrando resultado del punto 1: \n\n\n");
                    if (resultado != NULL)
                    {

                        bFila = PQntuples(resultado);
                        bColumna = PQnfields(resultado);

                        for (a = 0; a < bFila; a++)
                        {
                            for (b = 0; b < bColumna; b++)
                            {
                                printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                            } // fin del for bColumna
                            printf("\n\n");
                        } // fin del for bFila
                    }     // fin del if-null
                }
                else
                {

                    printf("Paciente no encontrado! \n\n");
                }

                break;

            case 2: // opcion para ver un dato en especifico de un cliente en especifico

                setbuf(stdin, NULL);
                printf("Opcion dos:\n\n");
                printf("Ingresar  el numero del paciente deseado del cual desea ver un dato en especifico: \n");
                scanf("%i", &bNum_Paciente);
                sprintf(selecPaciente, "select * from Paciente where num_paciente = %i", bNum_Paciente);
                resultado = PQexec(bd, selecPaciente);

                if (PQntuples(resultado) == 1) // valida si encuntra el paciente
                {
                    printf("Pacientes encontrado! \n\n\n\n");

                    printf("Seleccionar una de las opciones ofertadas: \n");
                    printf(" 1.- Nombre \n 2.- Apellidos \n 3.- Edad \n 4.- Direccion \n\n");
                    scanf("%i", &opcVer);
                    switch (opcVer)
                    {
                    case 1: // caso para el nombre
                        setbuf(stdin, NULL);
                        printf("Ingresar  el numero del paciente deseado del cual desea ver el dato: \n");
                        scanf("%i", &bNum_Paciente);
                        setbuf(stdin, NULL);
                        sprintf(selecPaciente, "select nombre_p from Paciente where num_paciente = %i", bNum_Paciente);
                        resultado = PQexec(bd, selecPaciente);
                        printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);

                        if (resultado != NULL)
                        {

                            bFila = PQntuples(resultado);
                            bColumna = PQnfields(resultado);

                            for (a = 0; a < bFila; a++)
                            {
                                for (b = 0; b < bColumna; b++)
                                {
                                    printf("El nombre del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                } // fin del for bColumna
                                printf("\n\n");
                            } // fin del for bFila
                        }     // fin del if-null
                        break;

                    case 2: // caso para los apellidos
                        setbuf(stdin, NULL);
                        printf("Ingresar  el numero del paciente deseado del cual desea ver el dato: \n");
                        scanf("%i", &bNum_Paciente);
                        setbuf(stdin, NULL);
                        sprintf(selecPaciente, "select appat_p, apmat_p from Paciente where num_paciente = %i", bNum_Paciente);
                        resultado = PQexec(bd, selecPaciente);
                        printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                        if (PQntuples(resultado) == 1)
                        {
                            printf("Pacientes encontrado! \n\n");

                            if (resultado != NULL)
                            {

                                bFila = PQntuples(resultado);
                                bColumna = PQnfields(resultado);
                                printf("Los apellidos del paciente son: \n");
                                for (a = 0; a < bFila; a++)
                                {
                                    for (b = 0; b < bColumna; b++)
                                    {
                                        printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                                    } // fin del for bColumna
                                    printf("\n\n");
                                } // fin del for bFila
                            }     // fin del if-null
                        }
                        else
                        {
                            printf("Paciente no encontrado! \n\n");
                        }
                        break; // break case 2

                    case 3: // case 3 para la edad
                        setbuf(stdin, NULL);
                        printf("Ingresar  el numero del paciente deseado del cual desea ver el dato: \n");
                        scanf("%i", &bNum_Paciente);
                        setbuf(stdin, NULL);
                        sprintf(selecPaciente, "select edad_p from Paciente where num_paciente = %i", bNum_Paciente);
                        resultado = PQexec(bd, selecPaciente);
                        printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                        if (PQntuples(resultado) == 1)
                        {
                            printf("Pacientes encontrado! \n\n");

                            if (resultado != NULL)
                            {

                                bFila = PQntuples(resultado);
                                bColumna = PQnfields(resultado);

                                for (a = 0; a < bFila; a++)
                                {
                                    for (b = 0; b < bColumna; b++)
                                    {
                                        printf("La edad del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                    } // fin del for bColumna
                                    printf("\n\n");
                                } // fin del for bFila
                            }     // fin del if-null
                        }
                        else
                        {
                            printf("Paciente no encontrado! \n\n");
                        }

                        break;

                    case 4: // case 4 para la direccion
                        setbuf(stdin, NULL);
                        printf("Ingresar  el numero del paciente deseado del cual desea ver el dato: \n");
                        scanf("%i", &bNum_Paciente);
                        sprintf(selecPaciente, "select direccion from Paciente where num_paciente = %i", bNum_Paciente);
                        resultado = PQexec(bd, selecPaciente);
                        printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                        if (PQntuples(resultado) == 1)
                        {
                            printf("Pacientes encontrado! \n\n");

                            if (resultado != NULL)
                            {

                                bFila = PQntuples(resultado);
                                bColumna = PQnfields(resultado);

                                for (a = 0; a < bFila; a++)
                                {
                                    for (b = 0; b < bColumna; b++)
                                    {
                                        printf("La direccion del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                    } // fin del for bColumna
                                    printf("\n\n");
                                } // fin del for bFila
                            }     // fin del if-null
                        }
                        else
                        {
                            printf("Paciente no encontrado! \n\n");
                        }

                        break;

                    default:
                        printf("\n\nElegir una de las opciones ofrecidas!\n\n");
                        break;
                    }
                }
                else
                { // else paciente no encontrado
                    printf("Paciente no encontrado! \n\n");
                }

                break;

            case 3:
                // opcion de ver los datos de todos los pacientes

                sprintf(selecPaciente, "select * from Paciente");
                resultado = PQexec(bd, selecPaciente);
                printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);

                if (resultado != NULL)
                {

                    bFila = PQntuples(resultado);
                    bColumna = PQnfields(resultado);

                    for (a = 0; a < bFila; a++)
                    {
                        for (b = 0; b < bColumna; b++)
                        {
                            printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                        } // fin del for bColumna
                        printf("\n\n");
                    } // fin del for bFila
                }     // fin del if-null

                break;

            case 4:
                printf("\n\n");
                break;

            default:
                printf("\n\nIngrsar una copcion valida\n\n");
                break;
            }

        } while (opcSelecPac != 4);

        printf("\n¿Desea usar otra funcion?\n");
        printf("1.- Si \n2.- No");
        printf("\nOpcion: ");
        scanf("%i", &respConsP);
        setbuf(stdin, NULL); // Limpiar el buffer
    } while (respConsP != 1 && respConsP != 2);
}

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀▀ ▀▄░▄▀ ░█▀▀█ ░█▀▀▀ ░█▀▀▄ ▀█▀ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ ░█▀▀▀
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█▀▀▀ ─░█── ░█▄▄█ ░█▀▀▀ ░█─░█ ░█─ ░█▀▀▀ ░█░█░█ ─░█── ░█▀▀▀
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█▄▄▄ ▄▀░▀▄ ░█─── ░█▄▄▄ ░█▄▄▀ ▄█▄ ░█▄▄▄ ░█──▀█ ─░█── ░█▄▄▄

void alta_expediente()
{
    int nump;
    char datos[500], busp[100], buspe[100], inser[600];

    printf("\ningrese el id del paciente: ");
    scanf("%d", &nump);
    sprintf(busp, "select num_paciente from Paciente where num_paciente = %d", nump);
    resule = PQexec(bd, busp);

    if (PQntuples(resule) != 0)
    {
        sprintf(buspe, "select num_paciente from expediente where num_paciente = %d", nump);
        resule = PQexec(bd, buspe);
        if (PQntuples(resule) == 0)
        {
            printf("\ninserte alergias: padecimientos, sindromes etc: ");
            empty_stdin();
            scanf("%s", datos);
            empty_stdin();
            sprintf(inser, "insert into Expediente(num_paciente, alergias) values ('%d' , '%s');", nump, datos);
            printf("\nInstruccion SQL antes de ejecutarse: %s\n", inser);
            in = PQexec(bd, inser);
            if (PQresultStatus(in) == PGRES_COMMAND_OK)
            {
                printf("\n\nInserccion exitosa!\n\n");
            }
            else
            {
                printf("Inserccion sin exito! \n\n");
            }
        }
        else
        {
            printf("\nese paciente ya tiene expediente\n");
        }
    }
    else
    {
        printf("\nNo existe ese id\n");
    }
}

void borrar_expediente()
{
    int numpb;
    char busp[100], delete[100];

    printf("\ningrese el id del paciente al que le borrara el expediente: ");
    scanf("%d", &numpb);
    sprintf(busp, "select num_paciente from Expediente where num_paciente = %d", numpb);
    resu = PQexec(bd, busp);

    if (PQntuples(resu) != 0)
    {
        sprintf(delete, "delete from expediente where num_paciente = %d;", numpb);
        printf("\nInstruccion SQL antes de ejecutarse: %s\n", delete);
        resu = PQexec(bd, delete);
        if (PQresultStatus(resu) == PGRES_COMMAND_OK)
        {
            printf("\n\nEliminacion exitosa!\n\n");
        }
        else
        {
            printf("\n\nEliminacion sin exito! \n\n");
        }
    }
    else
    {
        printf("\nNo existe ese Expediente\n");
    }
}

void modificar_expediente()
{
    int numpb;
    char busp[100], ndatos[1000], update[1100];

    printf("\ningrese el id del paciente al que le modificara el expediente: ");
    scanf("%d", &numpb);
    sprintf(busp, "select num_paciente from Expediente where num_paciente = %d", numpb);
    printf("\n\n usted solo podra modificar sus alergias, padecimientos, etc...\n\n");
    resu = PQexec(bd, busp);

    if (PQntuples(resu) != 0)
    {
        printf("\ninserte nuevas alergias: padecimientos, sindromes etc: ");
        empty_stdin();
        scanf("%s", ndatos);
        empty_stdin();
        sprintf(update, "update Expediente set alergias = '%s' where num_paciente = '%d';", ndatos, numpb);
        printf("\nInstruccion SQL antes de ejecutarse: %s\n", update);
        resu = PQexec(bd, update);
        if (PQresultStatus(resu) == PGRES_COMMAND_OK)
        {
            printf("\n\nActualizacion exitosa!\n\n");
        }
        else
        {
            printf("\n\nEActualizacion sin exito! \n\n");
        }
    }
    else
    {
        printf("\nNo existe ese Expediente\n");
    }
}

void mostrar_expediente()
{
    char tab[50], cad[100];
    int i, j, fila, columna;

    // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad, "select * from Expediente order by num_exp");
    printf("Instruccion SQL antes de ejecutarse: %s \n", cad); // Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec(bd, cad); // Ejecuta linea postgres

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("---------------------------------------------------------------------------\n");
        printf("| Num_exp | Num_paciente  |    Alergias     |\n");
        for (i = 0; i < fila; i++)
        {
            printf("---------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {

                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀█ ▀█▀ ▀▀█▀▀ ─█▀▀█ 　 █──█ 　 ░█▀▀█ ░█▀▀▀█ ░█▄─░█ ░█▀▀▀█ ░█─░█ ░█─── ▀▀█▀▀ ─█▀▀█
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█─── ░█─ ─░█── ░█▄▄█ 　 █▄▄█ 　 ░█─── ░█──░█ ░█░█░█ ─▀▀▀▄▄ ░█─░█ ░█─── ─░█── ░█▄▄█
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█▄▄█ ▄█▄ ─░█── ░█─░█ 　 ▄▄▄█ 　 ░█▄▄█ ░█▄▄▄█ ░█──▀█ ░█▄▄▄█ ─▀▄▄▀ ░█▄▄█ ─░█── ░█─░█

void GuardarCita()
{
    int num_paciente, resp, prespl;
    char presplc[100], consultorio[10], fechac[20], hora[20], nombre[20], appat[20], apmat[20], buspac[200], alta[200];

    time_t t;
    char fecha[100];
    t = time(NULL);
    char *ch;
    ch = ctime(&t);
    strcpy(fecha, ch);
    // printf("%s",fecha);

    do
    {
        // Buscar el cliente por nombre completo
        printf("\n===============");
        printf("|AGENDAR UNA CITA|");
        printf("===============\n");
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("\nIngrese el nombre del paciente: ");
        scanf("%[^\n]", nombre);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
        scanf("%[^\n]", appat);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido materno del paciente: ");
        scanf("%[^\n]", apmat);
        setbuf(stdin, NULL); // Limpiar el buffer

        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre, appat, apmat);
        resultado = PQexec(bd, buspac); // Ejecuta linea postgres
        // Si es uno quiere decir que si lo encontro
        if (PQntuples(resultado) == 1)
        {
            printf("\nPaciente encontrado. Agende la cita\n");
            // Obtener el numero del paciente de la consulta
            // El numero del paciente se puede dar por defecto con buscar el paciente
            num_paciente = strtol(PQgetvalue(resultado, 0, 0), NULL, 10);
            printf("\n");
            printf("\t Agendar una nueva cita");
            // Pedir que el usuario ingrese los datos
            printf("\nIngrese el consultorio: ");
            scanf("%[^\n]", consultorio);
            setbuf(stdin, NULL); // Limpiar el buffer
            printf("Ingrese fecha de la cita (DD-MM-AAAA): ");
            scanf("%s", fechac);
            setbuf(stdin, NULL); // Limpiar el buffer
            printf("Ingrese hora de la cita (HH:MM:SS): ");
            scanf("%s", hora);
            setbuf(stdin, NULL); // Limpiar el buffer

            // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
            sprintf(alta, "Call AgendarCita (%i, '%s', '%s', '%s', NULL);", num_paciente, consultorio, fechac, hora);
            printf("\nInstruccion SQL antes de ejecutarse: %s \n", alta); // Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, alta); // Ejecuta linea postgres
            prespl = strtol(PQgetvalue(resultado, 0, 0), NULL, 10);
            // printf ("\nEl valor de retorno es: %i", prespl);
            if (prespl == 0)
            {
                printf("ATENCION: Error al agendar la cita\n");
            }
            else
            {
                printf("¡La cita ha sido agendada!\n");
            }

            // fin del else del if PQntuples donde se busca el paciente
        }
        else
        {
            printf("\nATENCION: El paciente no ha sido registrado \n");
        }
        // Validar si desea eliminar otro registro
        do
        {
            printf("\n¿Desea agendar otra cita\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &resp);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (resp != 1 && resp != 2);
    } while (resp == 1);
}

// Funcion para modificar datos de la cita
void ModificarCita()
{
    int resp, mod, modcita, num_paciente, i, j, columna, fila;
    char edit[500], buspac[300], nombre[20], appat[20], apmat[20], fecha[30], hora[20], consultorio[10], busnumpac[200], buspacit[200], busnum[200];
    do
    {
        // Buscar el cliente por nombre completo
        printf("\n===============");
        printf("|MODIFICAR UNA CITA|");
        printf("===============\n");
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("\nIngrese el nombre del paciente: ");
        scanf("%[^\n]", nombre);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
        scanf("%[^\n]", appat);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido materno del paciente: ");
        scanf("%[^\n]", apmat);
        setbuf(stdin, NULL); // Limpiar el buffer

        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre, appat, apmat);
        ressu = PQexec(bd, buspac); // Ejecuta linea postgres

        // Pedir que se ingrese los datos del usuario que se desea editar
        // Si es uno quiere decir que si lo encontro
        if (PQntuples(ressu) == 1)
        {

            printf("\nPaciente encontrado.\n");
            // Obtener el numero del paciente de la consulta
            // buscar el numero del paciente obtenido en la consulta anterior
            num_paciente = strtol(PQgetvalue(ressu, 0, 0), NULL, 10);

            sprintf(buspacit, "select * from cita where num_paciente = %i", num_paciente);
            ress = PQexec(bd, buspacit); // Ejecuta linea postgres
            // extraer el id de la cita
            // idcita = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
            // Evaluar si se ha encontrado citas para este paciente
            if (PQntuples(ress) == 0)
            {
                printf("\n ATENCION: este paciente NO cuenta con citas agendadas.\n");
            }
            else
            {
                printf("\nCitas del paciente encontradas.\n");
                // Imprimir todas las citas del paciente
                fila = PQntuples(ress); // filas de la tabla
                if (fila == 0)
                {
                    printf("ATENCION: La tabla está vacía\n");
                }
                else
                {
                    columna = PQnfields(ress); // Columnas de la tabla
                    printf("---------------------------------------------------------------------------\n");
                    printf("|id_cita | Paciente  |    Consultorio     |             Fecha/Hora         |\n");
                    for (i = 0; i < fila; i++)
                    {
                        printf("---------------------------------------------------------------------------\n");
                        for (j = 0; j < columna; j++)
                        {
                            printf("|    %s\t", PQgetvalue(ress, i, j)); // Resultado fila y columna de la consulta
                        }
                        printf("\n");
                    }
                }

                // Preguntar cual es la cita que desea modificar
                printf("\nIngrese la cita que desea modificar: ");
                scanf("%i", &modcita);

                do
                {
                    printf("Elija el dato que desea editar\n");
                    printf("\n 1.- Consultorio\n 2.- Fecha \n 3.- Hora \n 4.- Regresar\n");
                    printf("Opcion: ");
                    scanf("%i", &mod);
                    setbuf(stdin, NULL); // Limpiar el buffer
                    switch (mod)
                    {
                    case 1:
                        // Agregar dato modificado el consultorio
                        printf("\nIngrese el nuevo consultorio: ");
                        scanf("%s", consultorio);
                        sprintf(edit, "UPDATE Cita set consultorio = '%s' where id_cita = %i", consultorio, modcita);
                        printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, edit); // Ejecuta linea postgres
                        break;

                    case 2:
                        // Agregar dato modificado la fecha
                        printf("\nIngrese la nueva fecha (DD-MM-AAAA): ");
                        scanf("%s", fecha);
                        sprintf(edit, "UPDATE Cita set fecha = '%s' where id_cita = %i", fecha, modcita);
                        printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, edit); // Ejecuta linea postgres
                        break;

                    case 3:
                        // Agregar dato modificado la hora
                        printf("\nIngrese la nueva hora: ");
                        scanf("%s", hora);
                        sprintf(edit, "UPDATE Cita set hora = '%s' where id_cita = %i", hora, modcita);
                        printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, edit); // Ejecuta linea postgres
                        break;

                    case 4:
                        printf("\nRegresando...\n");
                        break;

                    default:
                        printf("\nIngrese una opcion correcta\n");
                    } // Fin del switch
                } while (mod != 4);
            } // fin del if - else para saber si el paciente tiene cita

        } // fin del if para saber si el paciente existe
        else
        {
            printf("\n ATENCION: este paciente NO ha sido ingresado.\n");
        }

        // Validar si el usuario quiere modificar otro registro
        do
        {
            printf("\n¿Desea modificar otro cliente\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &resp);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (resp != 1 && resp != 2);
    } while (resp == 1);
}

// Funcion para eliminar una cita
void EliminarCita()
{
    int resp, num_pac;
    char nombre[20], appat[20], apmat[20], elim[100], buspac[200];
    do
    {
        // Buscar el paciente por nombre completo
        printf("\n===============");
        printf("|ELIMINAR UNA CITA|");
        printf("===============\n");
        printf("\nIngrese el nombre del paciente: ");
        scanf("%s", nombre);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
        scanf("%s", appat);
        printf("Ingrese el apellido materno del paciente: ");
        scanf("%s", apmat);
        setbuf(stdin, NULL); // Limpiar el buffer
        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s';", nombre, appat, apmat);
        ress = PQexec(bd, buspac); // Ejecuta linea postgres

        if (PQntuples(ress) == 0)
        {
            // Entra si el cliente no se encuentra registrado
            printf("Error al eliminar la cita. Registro no encontrado\n\n");
        }
        else
        {
            printf("Registro encontrado\n\n");
            // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
            num_pac = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
            sprintf(elim, "delete from cita where num_paciente = %i;", num_pac);
            // fflush (stdin);
            printf("\nInstruccion SQL antes de ejecutarse: %s \n", elim); // Mostrar instruccion SQL
            printf("\n");
            ress = PQexec(bd, elim); // Ejecuta linea postgres
            printf("\n ¡La cita ha sido eliminada!\n");
        } // Fin del else if (PQntuples)
        // Validar si desea eliminar otro registro
        do
        {
            printf("\n¿Desea eliminar otra cita\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &resp);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (resp != 1 && resp != 2);
    } while (resp == 1);
}

// Funcion para consultar una cita
void ConsultarCita()
{
    char tab[50], cad[100];
    int i, j, fila, columna;
    // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad, "select * from cita order by id_cita");
    printf("Instruccion SQL antes de ejecutarse: %s \n", cad); // Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec(bd, cad); // Ejecuta linea postgres

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("---------------------------------------------------------------------------\n");
        printf("|id_cita | Paciente  |    Consultorio     |             Fecha/Hora         |\n");
        for (i = 0; i < fila; i++)
        {
            printf("---------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {

                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

// Funciones para el catalago de CONSULTA -----------------------------------------------------------------------------------------

// Funcion para modificar una consulta
void Guardar_Consulta()
{
    int res, id_cita;
    char nombre[30], ap[30], am[30], buscar[330], cedula[15], fecha[10], hora[10], consul[40], alta_c[500];
    do
    {
        // insertar insert into consulta(id_cita, cedula, fecha_con, hora_con, consultorio_con) values ();
        printf("\n|============================================|\n");
        printf("|             Guardar Consulta               |\n");
        printf("|============================================|\n");
        setbuf(stdin, NULL);
        printf("Ingrese el nombre del paciente:");
        scanf("%[^\n]", nombre);
        setbuf(stdin, NULL);
        printf("Ingrese el apellido peterno del paciente:");
        scanf("%[^\n]", ap);
        setbuf(stdin, NULL);
        printf("Ingrese el apellido materno del paciente:");
        scanf("%[^\n]", am);
        setbuf(stdin, NULL);
        sprintf(buscar, "select cd.id_cita,pa.nombre_p,pa.appat_p,pa.apmat_p from cita cd inner join paciente pa on cd.num_paciente = pa.num_paciente where pa.nombre_p='%s' and pa.appat_p='%s' and pa.apmat_p='%s';", nombre, ap, am);
        resultado = PQexec(bd, buscar); // Ejecuta linea postgres
        if (PQntuples(resultado) == 1)  // si da uno es que se encontro el dato
        {
            printf("Paciente con cita encontrado, Agende la consulta!!\n");
            id_cita = strtol(PQgetvalue(resultado, 0, 0), NULL, 10); // se obtiene por defecto el ide de la cita
            printf("\n\n.....Agendar consulta.....\n\n");
            printf("Ingrese la cedula del medico que va a atender:");
            scanf("%s", cedula);
            sprintf(buscar, "Select cedula from medico where cedula='%s'", cedula);
            ress = PQexec(bd, buscar); // Ejecuta linea postgres
            printf("\n");
            if (PQntuples(ress) == 1)
            {
                printf("Doctor encontrado siga con la alta!.\n");
                setbuf(stdin, NULL);
                printf("Ingrese la fecha de la consulta(DD-MM-AAAA):");
                scanf("%s", fecha);
                setbuf(stdin, NULL);
                printf("Ingrese la hora de la consulta:(HH:MM:SS): ");
                scanf("%s", hora);
                setbuf(stdin, NULL);
                printf("Ingrese el el consultorio:");
                scanf("%[^\n]", consul);
                setbuf(stdin, NULL);
                sprintf(alta_c, "insert into consulta (id_cita,cedula,fecha_con,hora_con,consultorio_con) values(%i,'%s','%s','%s','%s');", id_cita, cedula, fecha, hora, consul);
                resu = PQexec(bd, alta_c);
                printf("Instruccion SQL antes de ejecutarse: %s \n", alta_c);
                if (PQresultStatus(resu) == PGRES_COMMAND_OK)
                {
                    printf("\n La consulta ha sido guardado exitosamente\n");
                }
                else
                {
                    printf("\n Error al guardar La consulta\n");
                }
            }
            else
            {
                printf("\nADVERTENCIA: El doctor no ha sido registrado\n");
            }
        }
        else
        {
            printf("AVISO: El paciente NO ha sido registrado!!");
        }

        printf("\n¿Desea Guardar otra Consulta?:\n1.-Si\n2.-No\nOpcion:");
        scanf("%i", &res);
    } while (res != 2);
}

void ModificarConsulta()
{
    int resp, mod, modcita, num_paciente, i, j, columna, fila, idcita;
    char edit[500], busconsul[300], buspac[300], nombre[20], appat[20], apmat[20], fecha[30], hora[20], consultorio[10], cedula[10], busnumpac[200], buspacit[200], busnum[200];
    do
    {
        // Buscar el cliente por nombre completo
        printf("\n===============");
        printf("|MODIFICAR UNA CONSULTA|");
        printf("===============\n");
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("\nIngrese el nombre del paciente: ");
        scanf("%[^\n]", nombre);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
        scanf("%[^\n]", appat);
        setbuf(stdin, NULL); // Limpiar el buffer
        printf("Ingrese el apellido materno del paciente: ");
        scanf("%[^\n]", apmat);
        setbuf(stdin, NULL); // Limpiar el buffer

        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre, appat, apmat);
        ressu = PQexec(bd, buspac); // Ejecuta linea postgres

        // Pedir que se ingrese los datos del usuario que se desea editar
        // Si es uno quiere decir que si lo encontro
        if (PQntuples(ressu) == 1)
        {

            printf("\nPaciente encontrado.\n");
            // Obtener el numero del paciente cita
            // buscar el numero del paciente obtenido en la consulta anterior
            num_paciente = strtol(PQgetvalue(ressu, 0, 0), NULL, 10);

            sprintf(buspacit, "select id_cita from cita where num_paciente = %i", num_paciente);
            ress = PQexec(bd, buspacit); // Ejecuta linea postgres
            // extraer el id de la cita
            // idcita = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
            // Evaluar si se ha encontrado citas para este paciente
            if (PQntuples(ress) == 0)
            {
                printf("\n ATENCION: este paciente NO cuenta con citas agendadas.\n");
            }
            else
            {
                printf("\nEl paciente cuenta con citas. Buscando consultas...\n");
                idcita = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
                // selecciona todos los datos de la tabla de consulta
                sprintf(busconsul, "select * from consulta where id_cita = %i", idcita);
                resu = PQexec(bd, busconsul); // Ejecuta linea postgres

                if (PQntuples(resu) == 0)
                {
                    printf("\n ATENCION: este paciente NO cuenta con consultas agendadas.\n");
                }
                else
                {
                    // entra cuando encuentra consultas del paciente
                    printf("\nConsultas del paciente encontradas.\n");
                    // Imprimir todas las consultas del paciente
                    fila = PQntuples(resu); // filas de la tabla
                    if (fila == 0)
                    {
                        printf("ATENCION: La tabla está vacía\n");
                    }
                    else
                    {
                        columna = PQnfields(resu); // Columnas de la tabla
                        printf("---------------------------------------------------------------------------------------------\n");
                        printf("|id_consulta | id_cita  |    Cedula    |      Fecha     |      Hora      |    Consultorio   |\n");
                        for (i = 0; i < fila; i++)

                        {
                            printf("---------------------------------------------------------------------------------------------\n");
                            for (j = 0; j < columna; j++)
                            {
                                printf("|    %s\t", PQgetvalue(resu, i, j)); // Resultado fila y columna de la consulta
                            }
                            printf("\n");
                        }
                    }

                    // Preguntar cual es la cita que desea modificar
                    printf("\nIngrese la consulta que desea modificar: ");
                    scanf("%i", &modcita);

                    do
                    {
                        printf("\nElija el dato que desea editar\n");
                        printf("\n 1.- Cedula del medico\n 2.- Consultorio\n 3.- Fecha \n 4.- Hora \n 5.- Regresar\n");
                        printf("Opcion: ");
                        scanf("%i", &mod);
                        setbuf(stdin, NULL); // Limpiar el buffer
                        switch (mod)
                        {
                        case 1:
                            // Agregar dato modificado el consultorio
                            printf("\nIngrese la nueva cedula: ");
                            scanf("%s", cedula);
                            // buscar si la cedula existe
                            sprintf(buspacit, "select * from medico where cedula = '%s'", cedula);
                            ress = PQexec(bd, buspacit); // Ejecuta linea postgres
                            // entra si el medico no existe
                            if (PQntuples(ress) == 0)
                            {
                                printf("\n ATENCION: El medico no existe\n");
                            }
                            else
                            {
                                printf("\nEl medico ha sido encontrado. Guardando modificacion...\n");
                                sprintf(edit, "UPDATE Consulta set cedula = '%s' where id_consulta = %i", cedula, modcita);
                                printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                                printf("\n");
                                resultado = PQexec(bd, edit); // Ejecuta linea postgres
                            }
                            break;

                        case 2:
                            // Agregar dato modificado el consultorio
                            printf("\nIngrese el nuevo consultorio: ");
                            scanf("%s", consultorio);
                            sprintf(edit, "UPDATE consulta set consultorio_con = '%s' where id_consulta = %i", consultorio, modcita);
                            printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                            printf("\n");
                            resultado = PQexec(bd, edit); // Ejecuta linea postgres
                            break;

                        case 3:
                            // Agregar dato modificado la fecha
                            printf("\nIngrese la nueva fecha (DD-MM-AAAA): ");
                            scanf("%s", fecha);
                            sprintf(edit, "UPDATE consulta set fecha_con = '%s' where id_consulta = %i", fecha, modcita);
                            printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                            printf("\n");
                            resultado = PQexec(bd, edit); // Ejecuta linea postgres
                            break;

                        case 4:
                            // Agregar dato modificado la hora
                            printf("\nIngrese la nueva hora: ");
                            scanf("%s", hora);
                            sprintf(edit, "UPDATE consulta set hora_con = '%s' where id_consulta = %i", hora, modcita);
                            printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); // Mostrar instruccion SQL
                            printf("\n");
                            resultado = PQexec(bd, edit); // Ejecuta linea postgres
                            break;

                        case 5:
                            printf("\nRegresando...\n");
                            break;

                        default:
                            printf("\nIngrese una opcion correcta\n");
                        } // Fin del switch
                    } while (mod != 5);
                } // fin del if -else para saber si tiene consultas
            }     // fin del if - else para saber si el paciente tiene cita

        } // fin del if para saber si el paciente existe
        else
        {
            printf("\n ATENCION: este paciente NO ha sido ingresado.\n");
        }
        // Validar si el usuario quiere modificar otro registro
        do
        {
            printf("\n¿Desea modificar otro cliente\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &resp);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (resp != 1 && resp != 2);
    } while (resp == 1);
}

// Funcion para eliminar una cita
void EliminarConsulta()
{
    int resp, num_pac, id_con;
    char nombre[20], appat[20], apmat[20], elim[100], buspac[200], busc[100];
    do
    {
        // Buscar el paciente por nombre completo
        printf("\n===============");
        printf("|ELIMINAR UNA CONSULTA|");
        printf("===============\n");

        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(buspac, "select c.id_cita, con.id_consulta, p.nombre_p, p.appat_p, p.apmat_p from paciente p inner join cita c on c.num_paciente = p.num_paciente inner join consulta con on  con.id_cita = c.id_cita;");
        resultado = PQexec(bd, buspac); // Ejecuta linea postgres
        if (PQntuples(resultado) == 0)
        {
            // Entra si el paciente no se encuentra registrado
            printf("ATENCION: Error al eliminar la consultar. Dato incorrecto\n\n");
        }
        else
        {
            // Imprimir los datos de la consulta buspac
            char tab[50], cad[100];
            int i, j, fila, columna;
            printf("RegistroS encontrados\n\n");

            fila = PQntuples(resultado); // filas de la tabla
            if (fila == 0)
            {
                printf("ATENCION: La tabla está vacía\n");
            }
            else
            {
                columna = PQnfields(resultado); // Columnas de la tabla
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("|id_cita |  id_consulta  |   Nombre    |   Apellido paterno  |  Apellido paterno  |\n");
                for (i = 0; i < fila; i++)
                {
                    printf("-----------------------------------------------------------------------------------------------\n");
                    for (j = 0; j < columna; j++)
                    {
                        printf("|       %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
                    }
                    printf("\n");
                }
            }
            printf("\nIngrese el numero de la consulta que desea eliminar: ");
            scanf("%i", &id_con);
            setbuf(stdin, NULL); // Limpiar el buffer
            // Sentencia para buscar la consulta en la tabla y saber si realmente existe
            sprintf(busc, "select * from consulta where id_consulta = %i;", id_con);
            printf("\n");
            ress = PQexec(bd, busc); // Ejecuta linea postgres

            if (PQntuples(ress) == 0)
            {
                // Entra si la consulta no se encuentra registrado
                printf("ATENCION: Error al eliminar la consulta. Dato incorrecto\n\n");
            }
            else
            {
                // Entra cuando la consulta si está registrada
                sprintf(elim, "delete from consulta where id_consulta = %i;", id_con);
                // fflush (stdin);
                printf("\nInstruccion SQL antes de ejecutarse: %s \n", elim); // Mostrar instruccion SQL
                printf("\n");
                ress = PQexec(bd, elim); // Ejecuta linea postgres
                printf("\n ¡La cita ha sido eliminada!\n");
            }

        } // Fin del else if (PQntuples)
        // Validar si desea eliminar otro registro
        do
        {
            printf("\n¿Desea eliminar otra cita\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &resp);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (resp != 1 && resp != 2);
    } while (resp == 1);
}

void ConsultarConsulta()
{
    char tab[50], cad[100];
    int i, j, fila, columna;
    // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad, "select * from consulta order by id_consulta");
    printf("Instruccion SQL antes de ejecutarse: %s \n", cad); // Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec(bd, cad); // Ejecuta linea postgres

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("---------------------------------------------------------------------------------------------\n");
        printf("|id_consulta | id_cita  |   Cedula    |      fecha     |     hora      |     Consultorio    |\n");
        for (i = 0; i < fila; i++)
        {
            printf("---------------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {

                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

//░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▄▀█ ░█▀▀▀ ░█▀▀▄ ▀█▀ ░█▀▀█ ░█▀▀▀█ ░█▀▀▀█ 　 ░█──░█
//░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█░█░█ ░█▀▀▀ ░█─░█ ░█─ ░█─── ░█──░█ ─▀▀▀▄▄ 　 ░█▄▄▄█
//░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█──░█ ░█▄▄▄ ░█▄▄▀ ▄█▄ ░█▄▄█ ░█▄▄▄█ ░█▄▄▄█ 　 ──░█──

//░█▀▀▀ ░█▀▀▀█ ░█▀▀█ ░█▀▀▀ ░█▀▀█ ▀█▀ ─█▀▀█ ░█─── ▀█▀ ░█▀▀▄ ─█▀▀█ ░█▀▀▄
//░█▀▀▀ ─▀▀▀▄▄ ░█▄▄█ ░█▀▀▀ ░█─── ░█─ ░█▄▄█ ░█─── ░█─ ░█─░█ ░█▄▄█ ░█─░█
//░█▄▄▄ ░█▄▄▄█ ░█─── ░█▄▄▄ ░█▄▄█ ▄█▄ ░█─░█ ░█▄▄█ ▄█▄ ░█▄▄▀ ░█─░█ ░█▄▄▀

void alta_medico()
{
    char cedula[30], nombre[30], appat[30], apmat[30];
    int edad, resp;
    char altaM[500], vali[200];

    do
    {
        printf("\n Ingresar un nuevo cliente a la BDD \n");
        printf("Ingrese la cedula del medico: ");
        scanf("%s", cedula);

        sprintf(vali, "select * from Medico where cedula = '%s'", cedula);
        resultado = PQexec(bd, vali);

        if (PQntuples(resultado) == 0)
        {
            setbuf(stdin, NULL);
            printf("Ingrese la edad del medico(+18):");
            scanf("%i", &edad);

            if (edad >= 18)
            {
                setbuf(stdin, NULL);
                printf("Ingrese el nombre del medico:");
                fgets(nombre, 30, stdin);
                setbuf(stdin, NULL);
                // Remover salto de línea
                if ((strlen(nombre) > 0) && (nombre[strlen(nombre) - 1] == '\n'))
                {
                    nombre[strlen(nombre) - 1] = '\0';
                }

                setbuf(stdin, NULL);
                printf("Ingrese el apellido paterno del medico:");
                fgets(appat, 30, stdin);
                setbuf(stdin, NULL);
                // Remover salto de línea
                if ((strlen(appat) > 0) && (appat[strlen(appat) - 1] == '\n'))
                {
                    appat[strlen(appat) - 1] = '\0';
                }

                setbuf(stdin, NULL);
                printf("Ingrese el apellido materno del medico:");
                fgets(apmat, 30, stdin);
                setbuf(stdin, NULL);
                // Remover salto de línea
                if ((strlen(apmat) > 0) && (apmat[strlen(apmat) - 1] == '\n'))
                {
                    apmat[strlen(apmat) - 1] = '\0';
                }

                sprintf(altaM, "insert into Medico (cedula, edad, nombre_m, appat_m, apmat_m) values('%s', '%i', '%s', '%s', '%s')", cedula, edad, nombre, appat, apmat);
                printf("Instruccion SQL antes de ejecutarse: %s \n", altaM); // Mostrar sentencia SQL
                printf("\n");
                resultado = PQexec(bd, altaM);

                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n El Medico ha sido guardado exitosamente\n");
                }
                else
                {
                    printf("\n Error al guardar cliente\n");
                }
            }
            else
            {
                printf("\n No se admiten medicos menores de edad... \n");
            }
        }
        else
        {
            printf("\n El medico con ese Cedula ya existe...\n");
            resp == 1;
        }

        do
        {
            printf("\nDesea agregar otro medico?:\n");
            printf("1.- Si 2.-No\n");
            printf("teclee numero\n");
            scanf("%d", &resp);

        } while (resp == 1 && resp == 2); // Segundo while por si el suario desea ingresar otro medico

    } while (resp == 1);
}

void baja_medico()
{
    char cedula[20], baja[400], valid[200];
    int opcB;

    do
    {
        printf("\nIngrese la Cedula del medico que desea dar de baja: ");
        scanf("%s", cedula);
        setbuf(stdin, NULL);

        sprintf(valid, "select * from Medico where cedula = '%s'", cedula);
        resultado = PQexec(bd, valid);

        if (PQntuples(resultado) == 0)
        {
            printf("\n No existe el medico que desea dar de baja...\n");
            opcB == 1;
        }
        else
        {
            sprintf(baja, "delete from Medico where cedula = '%s'", cedula);

            printf("Instruccion SQL antes de ejecutarse: %s \n", baja); // Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, baja); // Ejecuta linea postgres

            if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
            {
                printf("\nSe ha dado de baja exitosamente al medico\n");
            }
            else
            {
                printf("\nError al dar de baja al medico... \n");
            }
        }

        do
        {
            printf("\nDesea dar de baja a otro medico?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opcB);

        } while (opcB == 1 && opcB == 2);

    } while (opcB == 1);
}

void actualizar_medico()
{
    char actualizar[300], validar[200];
    char cedula[20], nombre[30], appat[30], apmat[30];
    int edad, opc, opcMod;

    do
    {
        printf("Ingrese la Cedula del medico que desea modificar:");
        scanf("%s", cedula);
        setbuf(stdin, NULL);

        sprintf(validar, "select * from Medico where cedula = '%s'", cedula);
        resultado = PQexec(bd, validar);

        if (PQntuples(resultado) == 0)
        {
            printf("El medico no existe...\n");
            opc == 1;
        }
        else
        {
            // todo va aqui
            do
            {
                printf("\n Elija el dato que desee modificar:");
                printf("\n 1.- nombre del medico\n 2.- Edad \n 3.- Apellido paterno \n 4.- Apellido materno \n 5.- Salir \n");
                printf("\nOpcion: ");
                scanf("%i", &opcMod);

                switch (opcMod)
                {
                case 1:
                    setbuf(stdin, NULL);
                    printf("Introduzca el nuevo nombre del cliente:");
                    fgets(nombre, 30, stdin);
                    setbuf(stdin, NULL);

                    // Remover salto de línea
                    if ((strlen(nombre) > 0) && (nombre[strlen(nombre) - 1] == '\n'))
                    {
                        nombre[strlen(nombre) - 1] = '\0';
                    }

                    sprintf(actualizar, "Update Medico set nombre_m = '%s' where cedula = '%s' ", nombre, cedula);
                    printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); // Mostrar instruccion SQL
                    printf("\n");
                    resultado = PQexec(bd, actualizar);

                    if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                    {
                        printf("\nEl Medico ha sido modificado exitosamente \n");
                    }
                    else
                    {
                        printf("\nError al modificar el medico \n");
                    }

                    break;

                case 2:

                    setbuf(stdin, NULL);
                    printf("introduzca la edad a modificar del medico: ");
                    scanf("%i", &edad);
                    setbuf(stdin, NULL);

                    if (edad >= 18)
                    {
                        sprintf(actualizar, "Update Medico set edad = '%i' where cedula = '%s' ", edad, cedula);

                        printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); // Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, actualizar); // Ejecuta linea postgres
                        if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                        {
                            printf("\nEl Medico ha sido modificado exitosamente \n");
                        }
                        else
                        {
                            printf("\nError al modificar medico... \n");
                        }
                    }
                    else
                    {
                        printf("El Medico no puede ser menor de edad...\n");
                        opcMod == 1; // ojito
                    }

                    break;

                case 3:
                    setbuf(stdin, NULL);
                    printf("Introduzca el nuevo apellido paterno del medico:");
                    fgets(appat, 30, stdin);
                    setbuf(stdin, NULL);

                    // Remover salto de línea
                    if ((strlen(appat) > 0) && (appat[strlen(appat) - 1] == '\n'))
                    {
                        appat[strlen(appat) - 1] = '\0';
                    }

                    sprintf(actualizar, "Update Medico set appat_m = '%s' where cedula = '%s' ", appat, cedula);
                    printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); // Mostrar instruccion SQL
                    printf("\n");
                    resultado = PQexec(bd, actualizar);

                    if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                    {
                        printf("\nEl Medico ha sido modificado exitosamente \n");
                    }
                    else
                    {
                        printf("\nError al modificar el medico \n");
                    }

                    break;

                case 4:
                    setbuf(stdin, NULL);
                    printf("Introduzca el nuevo apellido materno del medico:");
                    fgets(apmat, 30, stdin);
                    setbuf(stdin, NULL);

                    // Remover salto de línea
                    if ((strlen(apmat) > 0) && (apmat[strlen(apmat) - 1] == '\n'))
                    {
                        apmat[strlen(apmat) - 1] = '\0';
                    }

                    sprintf(actualizar, "Update Medico set apmat_m = '%s' where cedula = '%s' ", apmat, cedula);
                    printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); // Mostrar instruccion SQL
                    printf("\n");
                    resultado = PQexec(bd, actualizar);

                    if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                    {
                        printf("\nEl Medico ha sido modificado exitosamente \n");
                    }
                    else
                    {
                        printf("\nError al modificar el medico \n");
                    }
                    break;

                case 5:
                    printf("\n Saliendo de las modificaciones del medico...\n");
                    break;

                default:
                    printf("\n Digite una opcion correcta...\n");
                } // fin del switch

                do
                {
                    printf("\nDesea actualizar otro dato del cliente?:\n");
                    printf("1.- Si 2.-No\n");
                    scanf("%i", &opcMod);

                } while (opcMod == 1 && opcMod == 2);

            } while (opcMod == 1);

        } // Fin del menu de actualizar dato del medico

        do
        {
            printf("\nDesea modificar a otro medico?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opc);

        } while (opc == 1 && opc == 2);

    } while (opc == 1);
}

void consultar_medico()
{
    char tab[50], cad[100];
    int i, j, fila, columna;
    // Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad, "select * from Medico order by cedula");
    printf("Instruccion SQL antes de ejecutarse: %s \n", cad); // Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec(bd, cad); // Ejecuta linea postgres

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("---------------------------------------------------------------------------------------\n");
        printf("|     Cedula    |  Edad |  Nombre Medico |  Apellido Paterno  |  Apellido Materno  |\n");
        for (i = 0; i < fila; i++)
        {
            printf("------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {

                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

// especialidad

void altaEspecialidad()
{
    char cedula[30], especialidad[30];
    int cns, resp;
    char altaE[500], vali[200], vali2[200];

    do
    {
        printf("\n Ingresar una nueva especialidad a la BDD \n");
        printf("Ingrese el cns de la especialidad: ");
        scanf("%i", &cns);

        sprintf(vali, "select * from Espcialidad where cns = '%i'", cns);
        resultado = PQexec(bd, vali);

        if (PQntuples(resultado) == 0)
        {
            setbuf(stdin, NULL);
            printf("Ingrese la cedula del medico:");
            scanf("%s", cedula);

            sprintf(vali2, "select * from Medico where cedula = '%s'", cedula);
            resultado = PQexec(bd, vali2);

            // validacion de cedula en medico
            if (PQntuples(resultado) == 0)
            {
                printf("\n No existe un medico la cedula ingresada...\n");
            }
            else
            {
                setbuf(stdin, NULL);
                printf("Ingrese la especialidad:");
                scanf("%s", especialidad);
                fgets(especialidad, 30, stdin);

                setbuf(stdin, NULL);
                // Remover salto de línea
                if ((strlen(especialidad) > 0) && (especialidad[strlen(especialidad) - 1] == '\n'))
                {
                    especialidad[strlen(especialidad) - 1] = '\0';
                }

                sprintf(altaE, "insert into Especialidad (cns, cedula, especialidad) values('%i', '%s', '%s')", cns, cedula, especialidad);
                printf("Instruccion SQL antes de ejecutarse: %s \n", altaE); // Mostrar sentencia SQL
                printf("\n");
                resultado = PQexec(bd, altaE);

                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\n La especialidad ha sido guardado exitosamente\n");
                }
                else
                {
                    printf("\n Error al guardar especialidad...\n");
                }
            }
        }
        else
        {
            printf("\n Ya existe una especialidad con ese cns...\n");
            resp == 1;
        }

        do
        {
            printf("\nDesea agregar otra especialidad?:\n");
            printf("1.- Si 2.-No\n");
            printf("teclee numero:\n");
            scanf("%i", &resp);

        } while (resp == 1 && resp == 2);

    } while (resp == 1);

} // fin altaEspecialidad

void bajaEspecialidad()
{
    char baja[400], valid[200];
    int cns, opcB;

    do
    {
        printf("\nIngrese el cns de la especialidad que desea dar de baja: ");
        scanf("%i", &cns);
        setbuf(stdin, NULL);

        sprintf(valid, "select * from Especialidad where cns = '%i'", cns);
        resultado = PQexec(bd, valid);

        if (PQntuples(resultado) == 0)
        {
            printf("\n No existe la especialidad que desea dar de baja...\n");
            opcB == 1;
        }
        else
        {
            sprintf(baja, "delete from Especialidad where cns = '%i'", cns);

            printf("Instruccion SQL antes de ejecutarse: %s \n", baja); // Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, baja); // Ejecuta linea postgres

            if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
            {
                printf("\nSe ha dado de baja exitosamente a la especialidad\n");
            }
            else
            {
                printf("\nError al dar de baja la especialidad... \n");
            }
        }

        do
        {
            printf("\nDesea dar de baja a otra ?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opcB);

        } while (opcB == 1 && opcB == 2);

    } while (opcB == 1);

} // Fin bajaEspecialidad

void modificarEspecialidad()
{
    char actualizar[300], validar[200];
    char especialidad[30];
    int cns, opc;

    do
    {
        printf("Ingrese el cns de la especialidad que desea modificar:");
        scanf("%i", &cns);
        setbuf(stdin, NULL);

        sprintf(validar, "select * from Especialidad where cns = '%i'", cns);
        resultado = PQexec(bd, validar);

        if (PQntuples(resultado) == 0)
        {
            printf("\n La especialidad que desea modificar no existe...\n");
            opc == 1;
        }
        else
        {
            setbuf(stdin, NULL);
            printf("Ingrese la nueva especialidad:");
            scanf("%s", especialidad);
            fgets(especialidad, 30, stdin);

            // Remover salto de línea
            if ((strlen(especialidad) > 0) && (especialidad[strlen(especialidad) - 1] == '\n'))
            {
                especialidad[strlen(especialidad) - 1] = '\0';
            }

            sprintf(actualizar, "Update Especialidad set especialidad = '%s' where cns = '%i' ", especialidad, cns);
            printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); // Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, actualizar);

            if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
            {
                printf("\nLa especialidad ha sido modificado exitosamente \n");
            }
            else
            {
                printf("\nError al modificar la especialidad...\n");
            }
        }

        do
        {
            printf("\nDesea modificar a otra especialidad?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opc);

        } while (opc == 1 && opc == 2);

    } while (opc == 1);

} // Fin modificarEspecialidad

void mostrarEspecialidad()
{
    char tab[50], cad[100];
    int i, j, fila, columna;

    sprintf(cad, "select * from Especialidad order by cns");
    printf("Instruccion SQL antes de ejecutarse: %s \n", cad); // Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec(bd, cad); // Ejecuta linea postgres

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("---------------------------------------------------------------------------------------\n");
        printf("|     Cns    |   Cedula   |    Especialidad   |\n");
        for (i = 0; i < fila; i++)
        {
            printf("------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {

                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
} // Fin mostrarEspecialidad

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀▄ ▀█▀ ─█▀▀█ ░█▀▀█ ░█▄─░█ ░█▀▀▀█ ░█▀▀▀█ ▀▀█▀▀ ▀█▀ ░█▀▀█ ░█▀▀▀█
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█─░█ ░█─ ░█▄▄█ ░█─▄▄ ░█░█░█ ░█──░█ ─▀▀▀▄▄ ─░█── ░█─ ░█─── ░█──░█
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█▄▄▀ ▄█▄ ░█─░█ ░█▄▄█ ░█──▀█ ░█▄▄▄█ ░█▄▄▄█ ─░█── ▄█▄ ░█▄▄█ ░█▄▄▄█

void Alta_Diagnostico()
{
    // variables para guardar los  datos en la tabla diagnostico
    int num_exp, res;
    char cedula[10], medicinas[100], valoracion_m[140], buscarD[210], alta_D[400];

    do
    {
        printf("\n|==========================================|\n");
        printf("|           Guardar Diagnostico            |\n");
        printf("|==========================================|\n");
        setbuf(stdin, NULL);
        printf("\nIngrese el numero del expediente del paciente:");
        scanf("%i", &num_exp);
        // se valida si el expediente del paciente existe
        sprintf(buscarD, "select num_exp from expediente where num_exp='%i';", num_exp);
        resultado = PQexec(bd, buscarD); // se manda esa consulta a la bd hospital
        if (PQntuples(resultado) == 1)   // si da uno es que se encontro el dato
        {                                // ya encontrado el expediente, ahora se busca el medico
            printf("\nExpediente encontrado, continue con la alta del diagnostico!\n\n");
            setbuf(stdin, NULL);
            printf("Ingrese la cedula del medico que atendio al paciente:");
            scanf("%[^\n]", cedula);
            sprintf(buscarD, "select cedula from medico where cedula='%s';", cedula);
            resultado = PQexec(bd, buscarD);
            if (PQntuples(resultado) == 1) // si da uno es que se encontro el dato
            {                              // continuamos con la alta del diagnostico

                printf("\nDoctor encontrado!, continue con la alta!\n\n");
                setbuf(stdin, NULL);
                printf("\nIngrese las medicinas que receto el medico al paciente:");
                scanf("%[^\n]", medicinas);
                setbuf(stdin, NULL);
                printf("\nIngrese la valoracion medica que se dio la paciente:");
                scanf("%[^\n]", valoracion_m);
                setbuf(stdin, NULL);
                printf("\n");
                // llamamos al procedimiento almadenado llamado guardardiagnostico para realizar la alta del diagnostico
                sprintf(alta_D, "Call GuardarDiagnostico(%i, '%s', '%s', '%s', NULL); ", num_exp, cedula, medicinas, valoracion_m);
                resultado = PQexec(bd, alta_D); // se manda la insercion a la bd hospital
                printf("Instruccion SQL antes de ejecutarse: %s \n", alta_D);

                if (PQresultStatus(resultado) == PGRES_COMMAND_OK) // verifica si se realizo el comando
                {
                    printf("\nInserrcion exitosa!\n");
                }
                else
                {
                    printf("\nError!!,¡Insercion fallida!!\n");
                }

            } // if de buscar medico
            else
            {
                printf("\nAVISO: El doctor ingresado no ha sido registrado!\n");
            }

        } // if de buscar expediente
        else
        {
            printf("\nAVISO: El expediente del paciente no ha sido regsitrado!!\n");
        }
        printf("\n¿Desea guardar otro diagnostico?:\n1.-Si\n2.-No\nOpcion:");
        scanf("%i", &res);
    } while (res != 2);

} // fin de m

void Actualizar_Diagnostico()
{
    int i, j, fila, columna, num_dia, res, opc, exp;
    char tab[50], cad[120], buscar[230], cedula[20], appat_p[20], apmat_p[20], act[300], med[30], vl[100];
    do
    {
        printf("\n|============================================|\n");
        printf("|         Modificar Diagnostico              |\n");
        printf("|============================================|\n");
        sprintf(cad, "select * from Diagnostico;");
        printf("Instruccion SQL antes de ejecutarse: %s \n\n", cad);
        resultado = PQexec(bd, cad);
        printf("\n|\t\t\t\t  Lista de diagnostico  \t\t\t\t|\n");
        if (resultado != NULL)
        {
            fila = PQntuples(resultado);
            columna = PQnfields(resultado);
            printf("|---------------------------------------------------------------------------------------------|\n");
            printf("|num_diagnostico|num_exp|cedula| medicinas|valoracion_medica                                  |\n");
            for (i = 0; i < fila; i++)
            {
                printf("---------------------------------------------------------------------------------------------\n");
                for (j = 0; j < columna; j++)
                {
                    printf("|    %s\t", PQgetvalue(resultado, i, j));
                }
                printf("\n");
            }
        }
        else
        {
            printf("ATENCION: La tabla está vacia!!\n");
        }
        printf("\nIngrese el numero del diagnostico a  modificar:");
        scanf("%i", &num_dia);
        sprintf(buscar, "select * from diagnostico where num_diagnostico =%i;", num_dia);
        resultado = PQexec(bd, buscar);
        if (PQntuples(resultado) == 0)
        {
            printf("AVISO: El diagnostico no existe!!\n");
        }
        else
        {
            printf("\nEliga el dato a modificar del diagnostico\n");
            printf("1.-Numero del expediente del paciente\n2.-Cedula del medico realizo el diagnostico\n");
            printf("3.-Medicinas\n4.-Valoracion medica\n\n");
            printf("Ingrese una opcion:");
            scanf("%i", &opc);
            switch (opc)
            {
            case 1:
                setbuf(stdin, NULL);
                printf("Ingrese el nuevo numero de expediente:");
                scanf("%i", &exp);
                sprintf(act, "update diagnostico set num_exp=%i where num_diagnostico='%i';", exp, num_dia);
                resultado = PQexec(bd, act);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\nEl diagnostico ha sido modificado exitosamente \n");
                }
                else
                {
                    printf("Error!!,¡Modificacion fallida!! \n");
                }
                break;
            case 2:
                setbuf(stdin, NULL);
                printf("Ingrese la nueva cedula del medico:");
                scanf("%s", cedula);
                sprintf(act, "update diagnostico set cedula='%s' where num_diagnostico='%i';", cedula, num_dia);
                resultado = PQexec(bd, act);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\nEl diagnostico ha sido modificado exitosamente \n");
                }
                else
                {
                    printf("Error!!,¡Modificacion fallida!!");
                }
                break;
            case 3:
                setbuf(stdin, NULL);
                printf("Ingrese la nueva medicina que receto el medico:");
                scanf("%[^\n]", med);
                sprintf(act, "update diagnostico set medicinas='%s' where num_diagnostico='%i';", med, num_dia);
                resultado = PQexec(bd, act);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\nEl diagnostico ha sido modificado exitosamente \n");
                }
                else
                {
                    printf("Error!!,¡Modificacion fallida!! \n");
                }
                break;
            case 4:
                setbuf(stdin, NULL);
                printf("Ingrese la nueva valoracion medica que receto el medico:");
                scanf("%[^\n]", vl);
                sprintf(act, "update diagnostico set valoracion_medica='%s' where num_diagnostico='%i';", vl, num_dia);
                resultado = PQexec(bd, act);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("\nEl diagnostico ha sido modificado exitosamente \n");
                }
                else
                {
                    printf("Error!!,¡Modificacion fallida!! \n");
                }
                break;
            default:
                printf("AVISO: la opcion elegida no existe, de favor eliga bien:");
            }
        }
        printf("\n¿Desea Modificar otro diagnostico?:\n1.-Si\n2.-No\nOpcion:");
        scanf("%i", &res);
    } while (res != 2);
}
// fin de m

void Eliminar_Diagnostico()
{
    int i, j, fila, columna, num_dia, res;
    char tab[50], cad[120], buscar[230], nombre[20], appat_p[20], apmat_p[20], el[130];

    do
    {
        printf("\n|===========================================|\n");
        printf("|             Baja Diagnostico              |\n");
        printf("|===========================================|\n");
        sprintf(buscar, "select di.num_diagnostico, exp.num_exp, pc.nombre_p, pc.appat_p, pc.apmat_p, di.cedula from paciente pc inner join expediente exp on pc.num_paciente= exp.num_paciente inner join diagnostico di on exp.num_exp=di.num_exp;");
        resultado = PQexec(bd, buscar);
        if (PQntuples(resultado) == 0)
        {
            printf("ATENCION: Error al eliminar el diagnostico. Dato incorrecto\n\n");
        }
        else
        {
            printf("Lista de diagnostico encontrados\n");
            if (resultado != NULL)
            {
                fila = PQntuples(resultado);
                columna = PQnfields(resultado);
                printf("|---------------------------------------------------------------------------------------------|\n");
                printf("| Num_diagnostico | Nombre | Apellido paterno | Apellido materno | Cedula_d                              |\n");
                for (i = 0; i < fila; i++)
                {
                    printf("---------------------------------------------------------------------------------------------\n");
                    for (j = 0; j < columna; j++)
                    {
                        printf("|    %s\t", PQgetvalue(resultado, i, j));
                    }
                    printf("\n");
                }
            }
            else
            {
                printf("ATENCION: La tabla está vacia!!\n");
            }
            printf("Ingrese el numero de diagnostico que desea eliminar:");
            scanf("%i", &num_dia);
            sprintf(buscar, "select * from diagnostico where num_diagnostico = %i;", num_dia);
            printf("\n");
            ress = PQexec(bd, buscar); // Ejecuta linea postgres
            if (PQntuples(ress) == 0)
            {
                // Entra si la consulta no se encuentra registrado
                printf("ATENCION: Error al eliminar el diagnostico. Dato incorrecto\n\n");
            }
            else
            {
                // Entra cuando la consulta si está registrada
                sprintf(el, "delete from diagnostico where num_diagnostico = %i;", num_dia);
                // fflush (stdin);
                printf("\nInstruccion SQL antes de ejecutarse: %s \n", el); // Mostrar instruccion SQL
                printf("\n");
                ress = PQexec(bd, el); // Ejecuta linea postgres
                if (PQresultStatus(ress) == PGRES_COMMAND_OK)
                {
                    printf("Eliminacion exitosa!\n");
                }
                else
                {
                    printf("Error!!,¡Eliminacion fallida!!");
                }
            }
        }
        printf("\n¿Desea eliminar otro diagnostico?:\n1.-Si\n2.-No\nOpcion:");
        scanf("%i", &res);
    } while (res != 2);

} // fin de m

void Seleccionar_Diagnostico()
{
    char tab[50], cad[120];
    int i, j, fila, columna;

    sprintf(cad, "select * from Diagnostico;");
    printf("Instruccion SQL antes de ejecutarse: %s \n\n", cad);
    resultado = PQexec(bd, cad);
    printf("\n|\t\t\t\t  Lista de diagnostico  \t\t\t\t|\n");
    if (resultado != NULL)
    {
        fila = PQntuples(resultado);
        columna = PQnfields(resultado);
        printf("|---------------------------------------------------------------------------------------------|\n");
        printf("|num_diagnostico|num_exp|cedula| medicinas|valoracion_medica                                  |\n");
        for (i = 0; i < fila; i++)
        {
            printf("---------------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {
                printf("|    %s\t", PQgetvalue(resultado, i, j));
            }
            printf("\n");
        }
    }
    else
    {
        printf("ATENCION: La tabla está vacia!!\n");
    }

} // fin de m

/*░█▀▀█ ░█▀▀▀█ ░█▄─░█ ░█▀▀▀█ ░█─░█ ░█─── ▀▀█▀▀ ─█▀▀█ ░█▀▀▀█    ░█▀▀█ ░█▀▀▀ ░█▀▀█ ░█▀▀▀█ ░█▀▀█ ▀▀█▀▀ ░█▀▀▀ ░█▀▀▀█
  ░█─── ░█──░█ ░█░█░█ ─▀▀▀▄▄ ░█─░█ ░█─── ─░█── ░█▄▄█ ─▀▀▀▄▄ ▀▀ ░█▄▄▀ ░█▀▀▀ ░█▄▄█ ░█──░█ ░█▄▄▀ ─░█── ░█▀▀▀ ─▀▀▀▄▄
  ░█▄▄█ ░█▄▄▄█ ░█──▀█ ░█▄▄▄█ ─▀▄▄▀ ░█▄▄█ ─░█── ░█─░█ ░█▄▄▄█    ░█─░█ ░█▄▄▄ ░█─── ░█▄▄▄█ ░█─░█ ─░█── ░█▄▄▄ ░█▄▄▄█ */

void Consulta_A()
{
    char con1[1000], cedula[10], busced[200];
    int i, j, fila, columna, opc;
    do
    {
        printf("\n");
        printf("\t REPORTRES DEL SISTEMA\n");
        printf("\nLista de pacientes de cada medico\n\n");
        printf("Ingrese la cedula del medico: ");
        scanf("%s", cedula);
        setbuf(stdin, NULL); // Limpiar el buffer
        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(busced, "Select * from medico where cedula = '%s';", cedula);
        ress = PQexec(bd, busced); // Ejecuta linea postgres
        // Evaluar que el medico
        if (PQntuples(ress) == 0)
        {
            printf("\nATENCION: el medico no ha sido encontrado\n");
        }
        else
        {
            printf("\nMedico encontrado\n");
            sprintf(con1, "select p.num_paciente, p.nombre_p, p.appat_p, p.apmat_p, m.cedula, m.nombre_m, m.appat_m, m.apmat_m from paciente p inner join cita ci on p.num_paciente = ci.num_paciente   inner join consulta co on ci.id_cita = co.id_cita inner join medico m on m.cedula = co.cedula where m.cedula = '%s';", cedula);
            printf("Instruccion SQL antes de ejecutarse: %s \n", con1); // Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, con1); // Ejecuta linea postgres

            fila = PQntuples(resultado); // filas de la tabla
            if (fila == 0)
            {
                printf("La tabla está vacía\n");
            }
            else
            {
                columna = PQnfields(resultado); // Columnas de la tabla
                printf("--------------------------------------------------------------------------------------------------------------------------\n");
                printf("| Paciente |    Nombre   |            Apellidos        |     Cedula    |     Medico    |            Apellidos        |\n");
                for (i = 0; i < fila; i++)
                {
                    printf("--------------------------------------------------------------------------------------------------------------------------\n");
                    for (j = 0; j < columna; j++)
                    {
                        printf("     %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
                    }
                    printf("\n");
                }
            }
        }
        // Validar si el usuario quiere modificar ver otro medico
        do
        {
            printf("\n¿Desea ver la lista de pacientes de otro medico?\n");
            printf("1.- Si \n2.- No");
            printf("\nOpcion: ");
            scanf("%i", &opc);
            setbuf(stdin, NULL); // Limpiar el buffer
        } while (opc != 1 && opc != 2);
    } while (opc == 1);
}

void Consulta_B()
{
    char consulta_edad[400];
    int a, b, fila, columna;

    setbuf(stdin, NULL);
    sprintf(consulta_edad, "select nombre_p, appat_p, apmat_p, edad_p from paciente where edad_p in (select max(edad_p) from paciente);");
    resultado = PQexec(bd, consulta_edad);
    printf("\n");
    printf("\nPaciente con mayor edad:\n");
    if (resultado != NULL)
    {
        fila = PQntuples(resultado);
        columna = PQnfields(resultado);
        for (a = 0; a < fila; a++)
        {
            for (b = 0; b < columna; b++)
            {
                printf("%s\t | \t ", PQgetvalue(resultado, a, b));
            } // fin del for bColumna
            printf("\n\n");
        } // fin del for bFila
    }     // fin del if-null

    setbuf(stdin, NULL);
    sprintf(consulta_edad, "select nombre_m, appat_m, apmat_m, edad from medico where edad in (select max(edad) from medico);");
    resultado = PQexec(bd, consulta_edad);
    printf("\n");
    printf("\nMedico con mayor edad:\n");
    if (resultado != NULL)
    {
        fila = PQntuples(resultado);
        columna = PQnfields(resultado);
        for (a = 0; a < fila; a++)
        {
            for (b = 0; b < columna; b++)
            {
                printf("%s\t | \t ", PQgetvalue(resultado, a, b));
            } // fin del for bColumna
            printf("\n\n");
        } // fin del for bFila
    }     // fin del if-null
}

void consulta_C()
{
    char consulta_promedio_edad[400];
    int a, b, fila, columna;

    setbuf(stdin, NULL);
    sprintf(consulta_promedio_edad, "select avg(p.edad_p) as promedio_de_edades_de_los_pacientes, avg(m.edad) as promedio_de_edades_de_medico from paciente p, medico m;");
    ressu = PQexec(bd, consulta_promedio_edad);
    printf("\n");
    printf("\npromedio_de_edades_de_los_pacientes  |     promedio_de_edades_de_los_medico  |\n\n");
    if (ressu != NULL)
    {
        fila = PQntuples(ressu);
        columna = PQnfields(ressu);
        for (a = 0; a < fila; a++)
        {
            for (b = 0; b < columna; b++)
            {
                printf("\t%s\t     | \t ", PQgetvalue(ressu, a, b));
            } // fin del for bColumna
            printf("\n\n");
        } // fin del for bFila
    }     // fin del if-null
}

void consulta_D()
{
    char consulta[4000], fecha1[15], fecha2[15];
    int i, j, fila, columna;
    setbuf(stdin, NULL);
    printf("Ingrese la primera fecha como inicio del rango(DD-MM-AAAA): ");
    scanf("%s", fecha1);
    setbuf(stdin, NULL);
    printf("Ingrese la segunda fecha como fin del rango(DD-MM-AAAA): ");
    scanf("%s", fecha2);
    printf("\n");
    setbuf(stdin, NULL);
    sprintf(consulta, "select  pa.nombre_p,  pa.appat_p, pa.apmat_p, con.fecha_con, count(con.fecha_con) as numero_de_consultas from paciente pa  inner join cita ci  on pa.num_paciente= ci.num_paciente inner join consulta con  on ci.id_cita=con.id_cita where con.fecha_con between '%s' and '%s' group by con.fecha_con,pa.nombre_p, pa.appat_p, pa.apmat_p order by con.fecha_con,pa.nombre_p,pa.appat_p, pa.apmat_p;", fecha1, fecha2);
    resultado = PQexec(bd, consulta);
    printf("\nInstruccion a ejecutarse :%s\n", consulta);
    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("--------------------------------------------------------------------------------------\n");
        printf("|    Nombre   |  Apellido pat  | Apellido mat  |   Fecha   | No_Consultas |\n");
        for (i = 0; i < fila; i++)
        {
            printf("--------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {
                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

void consulta_E()
{
    char consulta[400], fecha[50];
    int i, j, fila, columna;

    setbuf(stdin, NULL);
    printf("Ingrese fecha de la cita (DD-MM-AAAA): ");
    scanf("%s", fecha);
    setbuf(stdin, NULL);

    sprintf(consulta, "select med.cedula, med.nombre_m,med.appat_m, med.apmat_m, med.edad, count(con.id_consulta) as consultas from consulta con INNER JOIN medico med ON con.cedula = med.cedula where con.fecha_con = '%s' GROUP BY med.cedula;", fecha);

    resultado = PQexec(bd, consulta);
    printf("\n");

    fila = PQntuples(resultado); // filas de la tabla
    if (fila == 0)
    {
        printf("ATENCION: La tabla está vacía\n");
    }
    else
    {
        columna = PQnfields(resultado); // Columnas de la tabla
        printf("--------------------------------------------------------------------------------------\n");
        printf("|    Cedula     | Nombre medico | Apellido pat  | Apellido mat  |  Edad  | Consultas |\n");
        for (i = 0; i < fila; i++)
        {
            printf("--------------------------------------------------------------------------------------\n");
            for (j = 0; j < columna; j++)
            {
                printf("|    %s\t", PQgetvalue(resultado, i, j)); // Resultado fila y columna de la consulta
            }
            printf("\n");
        }
    }
}

//░█▀▀▀█ ░█─░█ ░█▀▀█ ░█▀▄▀█ ░█▀▀▀ ░█▄─░█ ░█─░█ ░█▀▀▀█
//─▀▀▀▄▄ ░█─░█ ░█▀▀▄ ░█░█░█ ░█▀▀▀ ░█░█░█ ░█─░█ ─▀▀▀▄▄
//░█▄▄▄█ ─▀▄▄▀ ░█▄▄█ ░█──░█ ░█▄▄▄ ░█──▀█ ─▀▄▄▀ ░█▄▄▄█

// █▀▄▀█ █▀▀ █▄░█ █░█   █▀ █▀▀ █▀▀ █▀█ █▀▀ ▀█▀ ▄▀█ █▀█ █ ▄▀█
// █░▀░█ ██▄ █░▀█ █▄█   ▄█ ██▄ █▄▄ █▀▄ ██▄ ░█░ █▀█ █▀▄ █ █▀█
void MenuSecretaria()
{
    // variables
    int opcS, opcC, opcP, opcR;
    int opcPac, opcCita, opcCons, opcExp, opcMed, opcDiag;

    /*ALMACENAMOS EL IDENTIFICADOR DEL PROCESO*/
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    /*ALMACENAMOS EL NUMERO DE PROCESOS*/
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (id == 0)
    {
        do
        {
            printf("\t\t█▀▄▀█ █▀▀ █▄░█ █░█   █▀▄ █▀▀   █▀ █▀▀ █▀▀ █▀█ █▀▀ ▀█▀ ▄▀█ █▀█ █ ▄▀█ █▀\n");
            printf("\t\t█░▀░█ ██▄ █░▀█ █▄█   █▄▀ ██▄   ▄█ ██▄ █▄▄ █▀▄ ██▄ ░█░ █▀█ █▀▄ █ █▀█ ▄█\n");
            printf("\nBienvenido al menu de secretarios\n");
            printf("\n 1.- Catalogos \n 2.- procesos \n 3.- Reportes \n 4.- Salir \n");
            printf("Elija una opcion: ");
            scanf("%i", &opcS);

            switch (opcS)
            {
            case 1: // opcion catalogos secretaria
                tmp1sc = MPI_Wtime();
                if (id == 0)
                {

                    do
                    {
                        printf("\n Bienvenido a Catalogos \n");
                        printf("\n 1.- Paciente \n 2.- Cita \n 3.- Consulta \n 4.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcC);

                        switch (opcC)
                        {
                        case 1:
                            do
                            {
                                printf("\n-----Pacientes-----\n");
                                printf("\n 1.- Alta paciente \n 2.- Baja paciente \n 3.- Modificar pacientes \n 4.- Consultar pacientes \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcPac);

                                switch (opcPac)
                                {
                                case 1:
                                    Alta_Paciente();
                                    // Metodo
                                    break;

<<<<<<< HEAD
                                case 2: // Metodo
                                    Actualizar_Paciente();                           
                                    break;

                                case 3:// Metodo
                                    Eliminar_Paciente(); 
=======
                                case 2:
                                    Eliminar_Paciente();
                                    break;

                                case 3:
                                    Actualizar_Paciente();
>>>>>>> origin/master
                                    break;

                                case 4:
                                    Seleccionar_Paciente();
                                    // Metodo
                                    break;

                                case 5:
                                    printf("\n Saliendo de paciente...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion valida... \n");
                                } // Fin del switch pacientes

                            } while (opcPac != 5); // Fin del while pacientes

                            break;

                        case 2:

                            do
                            {
                                printf("\n-----Citas-----\n");
                                printf("\n 1.- Alta cita \n 2.- Baja cita \n 3.- Modificar cita \n 4.- Consultar citas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCita);

                                switch (opcCita)
                                {
                                case 1: // Metodo guardar
                                    GuardarCita();
                                    break;

                                case 2: // Metodo eliminar
                                    EliminarCita();
                                    break;

                                case 3: // Metodo editar
                                    ModificarCita();
                                    break;

                                case 4: // Metodo consulta
                                    ConsultarCita();
                                    break;

                                case 5:
                                    printf("\n Saliendo de citas...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion valida... \n");
                                } // Fin del switch citas

                            } while (opcCita != 5); // Fin del while citas
                            break;

                        case 3:
                            do
                            {
                                printf("\n-----Consultas-----\n");
                                printf("\n 1.- Alta consulta \n 2.- Baja consulta \n 3.- Modificar consulta \n 4.- Consultar consultas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCons);

                                switch (opcCons)
                                {
                                case 1: // Metodo guardar
                                    Guardar_Consulta();
                                    break;

                                case 2: // Metodo eliminar
                                    EliminarConsulta();
                                    break;

                                case 3: // Metodo modificar
                                    ModificarConsulta();
                                    break;

                                case 4: // Metodo consultar
                                    ConsultarConsulta();
                                    break;

                                case 5:
                                    printf("\n Saliendo de consultas...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion valida... \n");
                                } // Fin del switch consultas

                            } while (opcCons != 5); // Fin del while consultas

                            break;

                        case 4:
                            printf("\n Saliendo de catalogos...\n");
                            break;

                        default:
                            printf("\n Digite una opcion correcta...\n");

                        } // Fin del switch opcC

                    } while (opcC != 4);
                }
                tmp1fsc = MPI_Wtime();

                break;

            case 2: // opcion procesos secretaria

                tmp2sp = MPI_Wtime();
                if (id == 0)
                {
                    do
                    {
                        printf("\n Bienvenido a Procesos \n");
                        printf("\n 1.- Expedientes \n 2.- Medico \n 3.- Diagnosticos \n 4.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcP);

                        switch (opcP)
                        {
                        case 1:

                            do
                            {
                                printf("\n-----Expedientes-----\n");
                                printf("\n 1.- Ver expediente \n 2.- Borrar expediente \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcExp);

                                switch (opcExp)
                                {
                                case 1:
                                    // Metodo mostrar expediente
                                    mostrar_expediente();
                                    break;

                                case 2:
                                    // Metodo borrar expediente
                                    borrar_expediente();
                                    break;

                                case 3:
                                    printf("\n Saliendo de expedientes...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion correcta...\n");
                                } // Fin del switch expediente

                            } while (opcExp != 3); // Fin while de expediente

                            break;

                        case 2:

                            do
                            {
                                printf("\n-----Medicos-----\n");
                                printf("\n 1.- Ver medicos \n 2.- Especialidad de medicos \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcMed);

                                switch (opcMed)
                                {
                                case 1:
                                    // Metodo
                                    consultar_medico();
                                    break;

                                case 2:
                                    mostrarEspecialidad();
                                    break;

                                case 3:
                                    printf("\n Saliendo de medicos...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion correcta...\n");
                                } // Fin del switch de medicos

                            } while (opcMed != 3); // Fin while medicos en menu secretaria

                            break;

                        case 3:

                            do
                            {
                                printf("\n-----Diagnosticos-----\n");
                                printf("\n 1.- Ver diagnosticos \n 2.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcDiag);

                                switch (opcDiag)
                                {
                                case 1:
                                    Seleccionar_Diagnostico();
                                    break;

                                case 2:
                                    printf("\n Saliendo de diagnosticos...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion correcta...\n");
                                } // Fin switch diagnostico

                            } while (opcDiag != 2); // Fin del while diagnosticos secretaria

                            break;

                        case 4:
                            printf("\n Saliendo de procesos...\n");
                            break;

                        default:
                            printf("\n Digite una opcion correcta...\n");

                        } // Fin del switch opcP

                    } while (opcP != 4);
                }
                tmp2fsp = MPI_Wtime();

                break;

            case 3: // opcion reportes secretaria
                tmp3sr = MPI_Wtime();
                if (id == 0)
                {
                    do
                    {
                        printf("\n Bienvenido a Reportes \n");
                        printf("\n 1.- B) Paciente y medico con mas edad \n 2.- C) Promedio de edades de pacientes y medicos \n 3.- E) Numero de consultas al dia por medico \n 4.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcR);

                        switch (opcR)
                        {
                        case 1:
                            // Metodo
                            Consulta_B();
                            break;

                        case 2:
                            // Metodo
                            consulta_C();
                            break;

                        case 3: // Metodo consulta E
                            consulta_E();
                            break;

                        case 4:
                            printf("\n Saliendo de reportes...\n");
                            break;

                        default:
                            printf("\n Digite una opcion correcta...\n");

                        } // Fin del switch opcR

                    } while (opcR != 4);
                }
                tmp3fsr = MPI_Wtime();

                break;

            case 4:
                printf("\n Saliendo del menu de secretarios...\n");
                break;

            default:
                printf("\n Seleccione una opcion valida secretaria...\n");
            }

        } while (opcS != 4); // Fin del ciclo secretaria
    }

} // Fin de menusecretaria

/*█▀▄▀█ █▀▀ █▄░█ █░█   █▀▄▀█ █▀▀ █▀▄ █ █▀▀ █▀█
  █░▀░█ ██▄ █░▀█ █▄█   █░▀░█ ██▄ █▄▀ █ █▄▄ █▄█ */

void MenuMedico()
{
    int opcM, opcCM, opcPM, opcRM;
    int opcDiag, opcMedic, opcCrudMedico, opcCrudEspec, opcExp, opcConsulta, opcCruExp;

    /*ALMACENAMOS EL IDENTIFICADOR DEL PROCESO*/
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    /*ALMACENAMOS EL NUMERO DE PROCESOS*/
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (id == 0)
    {

        do
        {
            printf("\t\t█▀▄▀█ █▀▀ █▄░█ █░█   █▀▄▀█ █▀▀ █▀▄ █ █▀▀ █▀█\n");
            printf("\t\t█░▀░█ ██▄ █░▀█ █▄█   █░▀░█ ██▄ █▄▀ █ █▄▄ █▄█\n");

            printf("\nBienvenido al menu de medicos\n");
            printf("\n 1.- Catalogos \n 2.- procesos \n 3.- Reportes \n 4.- Salir \n");
            printf("Elija una opcion: ");
            scanf("%i", &opcM);

            switch (opcM)
            {
            case 1: // opcion catalogos medico

                tmp1mc = MPI_Wtime();
                if (id == 0)
                {
                    do
                    {
                        printf("\n Bienvenido a Catalogos de medico \n");
                        printf("\n 1.- Medico \n 2.- Diagnostico \n 3.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcCM);

                        switch (opcCM)
                        {
                        case 1: // Medico y especialidad

                            do
                            {
                                printf("\n-----Medicos-----\n");
                                printf("\n 1.- Medico \n 2.- Especialidad \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcMedic);

                                switch (opcMedic)
                                {
                                case 1:
                                    // Crud tabla medico
                                    do
                                    {
                                        printf("\n-----Medico-----\n");
                                        printf("\n 1.- Alta medico \n 2.- Baja medico \n 3.- Modificar medico \n 4.- Consultar medicos \n 5.- Salir \n");
                                        printf("Elija una opcion: ");
                                        scanf("%i", &opcCrudMedico);

                                        switch (opcCrudMedico)
                                        {
                                        case 1:
                                            // Metodo alta medico
                                            alta_medico();
                                            break;

                                        case 2:
                                            // Metodo baja medico
                                            baja_medico();
                                            break;

                                        case 3:
                                            // Metodo modificar medico
                                            actualizar_medico();
                                            break;

                                        case 4:
                                            // Metodo consulta medico
                                            consultar_medico();
                                            break;

                                        case 5:
                                            printf("\n --Saliendo de medico...\n");
                                            break;

                                        default:
                                            printf("\n Digite una opcion corretca...\n");
                                        }

                                    } while (opcCrudMedico != 5);

                                    break;

                                case 2:
                                    // Crud tabla especialidad
                                    do
                                    {
                                        printf("\n-----Especialidad de medicos-----\n");
                                        printf("\n 1.- Alta especialidad \n 2.- Baja especialidad \n 3.- Modificar especialidad \n 4.- Consultar especialidades \n 5.- Salir \n");
                                        printf("Elija una opcion: ");
                                        scanf("%i", &opcCrudEspec);

                                        switch (opcCrudEspec)
                                        {
                                        case 1:
                                            altaEspecialidad();
                                            break;

                                        case 2:
                                            bajaEspecialidad();
                                            break;

                                        case 3:
                                            modificarEspecialidad();
                                            break;

                                        case 4:
                                            mostrarEspecialidad();
                                            break;

                                        case 5:
                                            printf("\n --Saliendo de especialidades...\n");
                                            break;

                                        default:
                                            printf("\n Digite una opcion correcta...\n");
                                        }

                                    } while (opcCrudEspec != 5);

                                    break;

                                case 3:
                                    printf("\n Saliendo de medicos...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion corretca...\n");
                                }

                            } while (opcMedic != 3); // Fin del while medicos

                            break;

                        case 2: // Diagnostico
                            do
                            {
                                // Crud tabla diagnostico
                                printf("\n-----Diagnosticos-----\n");
                                printf("\n 1.- Alta diagnostico \n 2.- Baja diagnostico \n 3.- Modificar diagnostico \n 4.- Consultar diagnosticos \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcDiag);

                                switch (opcDiag)
                                {
                                case 1:
                                    Alta_Diagnostico();
                                    break;

                                case 2:
                                    Eliminar_Diagnostico();
                                    break;

                                case 3:
                                    Actualizar_Diagnostico();
                                    break;

                                case 4:
                                    Seleccionar_Diagnostico();
                                    break;

                                case 5:
                                    printf("\n --Saliendo de diagnostico...\n");
                                    break;

                                default:
                                    printf("\n Digite una opcion correcta...\n");
                                }

                            } while (opcDiag != 5);

                            break;

                        case 3: // Salir
                            printf("\n Saliendo de catalogos de medicos...\n");
                            break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                        }

                    } while (opcCM != 3); // Fin del while catalogos del medico
                }
                tmp1fmc = MPI_Wtime();

                break;

            case 2: // opcion procesos medico

                tmp2mp = MPI_Wtime();
                if (id == 0)
                {
                    do
                    {
                        printf("\n Bienvenido a procesos de medico \n");
                        printf("\n 1.- Paciente \n 2.- Cita \n 3.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcPM);

                        switch (opcPM)
                        {
                        case 1: // paciente

                            do
                            {
                                printf("\n -----Pacientes----- \n");
                                printf("\n 1.- Ver paciente \n 2.- expedientes \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcExp);

                                switch (opcExp)
                                {
                                case 1:
                                    Seleccionar_Paciente();
                                    break;

                                case 2:
                                    // Metodo ver expediente
                                    do
                                    {
                                        printf("\n----- Expedientes-----");
                                        printf("\n 1.- Alta expediente \n 2.- Modificar expediente \n 3.- Mostrar expediente \n 4.- Salir de expedientes \n");
                                        printf("Elija una opcion:");
                                        scanf("%i", &opcCruExp);

                                        switch (opcCruExp)
                                        {
                                        case 1:
                                            alta_expediente();
                                            break;

                                        case 2:
                                            modificar_expediente();
                                            break;

                                        case 3:
                                            // metodo mostrar expediente
                                            mostrar_expediente();
                                            break;

                                        case 4:
                                            printf("\n Saliendo de expedientes...\n");
                                            break;

                                        default:
                                            printf("\n Seleccione una opcion valida...\n");
                                        }

                                    } while (opcCruExp != 4); // Fin while cru(d) expediente

                                    break;

                                case 3:
                                    printf("\n --Saliendo de Pacientes...\n ");
                                    break;

                                default:
                                    printf("\n Seleccione una opcion valida...\n");
                                }

                            } while (opcExp != 3); // Fin del while paciente proceso

                            break;

                        case 2: // cita

                            do
                            {
                                printf("\n -----Citas----- \n");
                                printf("\n 1.- Ver citas \n 2.- Ver consultas \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcConsulta);

                                switch (opcConsulta)
                                {
                                case 1: // Metodo ver citas
                                    ConsultarCita();
                                    break;

                                case 2: // Metodo ver consultas
                                    ConsultarConsulta();
                                    break;

                                case 3:
                                    printf("\n --Saliendo de Citas...\n ");
                                    break;

                                default:
                                    printf("\n Seleccione una opcion valida...\n");
                                }

                            } while (opcConsulta != 3);

                            break;

                        case 3: // salir
                            printf("\n Saliendo de procesos de medicos...\n");
                            break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                        }

                    } while (opcPM != 3); // Fin del while procesos del medico
                }
                tmp2fmp = MPI_Wtime();

                break;

            case 3: // opcion reportes medico

                tmp3mr = MPI_Wtime();
                if (id == 0)
                {
                    do
                    {
                        printf("\n Bienvenido a reportes del medico \n");
                        printf("\n 1.- A) Lista de pacientes por medico \n 2.- D) Consultas de los pacientes por fecha \n 3.- E) Numero de consultas por dia por el medico \n 4.- Salir \n");
                        printf("Elija una opcion: ");
                        scanf("%i", &opcRM);

                        switch (opcRM)
                        {
                        case 1: // Metodo A)
                            Consulta_A();
                            break;

                        case 2:
                            // Metodo D)
                            consulta_D();
                            break;

                        case 3: // Metodo E)
                            consulta_E();
                            break;

                        case 4:
                            printf("\nSaliendo del menu reportes medico...\n");
                            break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                        }

                    } while (opcRM != 4); // Fin del while de reportes del medico
                }
                tmp3fmr = MPI_Wtime();

                break;

            case 4:
                printf("\n Saliendo del menu de medicos...\n");
                break;

            default:
                printf("\n Seleccione una opcion valida medico...\n");
            }

        } while (opcM != 4); // Fin del ciclo secretaria
    }

} // Fin de menu medico

// ░█▀▄▀█ ░█▀▀▀ ░█▄─░█ ░█─░█ 　 ░█▀▀█ ░█▀▀█ ▀█▀ ░█▄─░█ ░█▀▀█ ▀█▀ ░█▀▀█ ─█▀▀█ ░█─── 　 ░█──░█ 　 ░█▀▄▀█ ─█▀▀█ ▀█▀ ░█▄─░█
// ░█░█░█ ░█▀▀▀ ░█░█░█ ░█─░█ 　 ░█▄▄█ ░█▄▄▀ ░█─ ░█░█░█ ░█─── ░█─ ░█▄▄█ ░█▄▄█ ░█─── 　 ░█▄▄▄█ 　 ░█░█░█ ░█▄▄█ ░█─ ░█░█░█
// ░█──░█ ░█▄▄▄ ░█──▀█ ─▀▄▄▀ 　 ░█─── ░█─░█ ▄█▄ ░█──▀█ ░█▄▄█ ▄█▄ ░█─── ░█─░█ ░█▄▄█ 　 ──░█── 　 ░█──░█ ░█─░█ ▄█▄ ░█──▀█

int menu_principal()
{
    int opcUsuario;
    char host[15] = "localhost";
    char puerto[5] = "5432";
    char database[15] = "hospital";
    char usuario[20];
    char password[20];

    // MPI DESDE AQUI

    /*INICIALIZAMOS EL ENTRORNO DE EJECUCION MPI*/

    /*ALMACENAMOS EL IDENTIFICADOR DEL PROCESO*/
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    /*ALMACENAMOS EL NUMERO DE PROCESOS*/
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (id == 0)
    {

        do
        {
            printf("\n");
            printf("\t\t  █▀▄▀█ █▀▀ █▄░█ █░█   █▀█ █▀█ █ █▄░█ █▀▀ █ █▀█ ▄▀█ █░░\n");
            printf("\t\t  █░▀░█ ██▄ █░▀█ █▄█   █▀▀ █▀▄ █ █░▀█ █▄▄ █ █▀▀ █▀█ █▄▄\n");

            printf("\n 1.- Secretaria \n 2.- Medico \n 3.- Salir \n ");
            printf("Elija su opcion: ");
            scanf("%opcUsuario", &opcUsuario);

            switch (opcUsuario)
            {
            case 1: // Secretaria
                tmp1s = MPI_Wtime();
                if (id == 0)
                {
                    printf("Ingrese su usuario: ");
                    scanf("%s", usuario);
                    printf("Ingrese la contraseña: ");
                    scanf("%s", password);

                    bd = PQsetdbLogin(host, puerto, NULL, NULL, database, usuario, password);

                    printf("\nProbando conexion con POSTGRESQL ...\n\n");

                    if (PQstatus(bd) == CONNECTION_OK)
                    { // Valida si la conexion fue exitosa
                        printf("Conexion exitosa\n");
                        tmp2s = MPI_Wtime();
                        if (id == 0)
                        {
                            MenuSecretaria();
                        } // llamando al metodo MenuSecretaria
                        tmp2fs = MPI_Wtime();
                    }
                    else
                    {
                        printf("Usuario o contraseña incorrectos\n");
                    } // Fin de la validacion de conexion a la BD
                }
                tmp1fs = MPI_Wtime();

                break;

            case 2: // Medicos

                tmp3m = MPI_Wtime();
                if (id == 0)
                {
                    printf("Ingrese el usuario medico: ");
                    scanf("%s", usuario);
                    printf("Ingrese la contraseña: ");
                    scanf("%s", password);

                    bd = PQsetdbLogin(host, puerto, NULL, NULL, database, usuario, password);

                    printf("\nProbando conexion con POSTGRESQL ...\n\n");

                    if (PQstatus(bd) == CONNECTION_OK)
                    { // Valida si la conexion fue exitosa
                        printf("Conexion exitosa\n");
                        MenuMedico(); // llamando al metodo de medicos
                    }
                    else
                    {
                        printf("Usuario o contraseña incorrectos\n");
                    } // Fin de la validacion de conexion a la BD
                }
                tmp3fm = MPI_Wtime();

                break;

            case 3:
                printf("\n\n\n \t---𝗦 𝗮 𝗹 𝗶 𝗲 𝗻 𝗱 𝗼  𝗱 𝗲 𝗹  𝗽 𝗿 𝗼 𝗴 𝗿 𝗮 𝗺 𝗮  𝗽 𝗿 𝗶 𝗻 𝗰 𝗶 𝗽 𝗮 𝗹---\n");
                break;

            default:
                printf("\n Digite una opcion correcta...\n");

            } // Fin del switch principal

        } while (opcUsuario != 3);
    }
}
// main
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    printf("\n\n");
    printf("\t██████╗ ██╗███████╗███╗  ██╗██╗   ██╗███████╗███╗  ██╗██╗██████╗  █████╗\n");
    printf("\t██╔══██╗██║██╔════╝████╗ ██║██║   ██║██╔════╝████  ██║██║██╔══██╗██╔══██╗\n");
    printf("\t██████╦╝██║█████╗  ██╔██╗██║╚██╗ ██╔╝█████╗  ██╔██╗██║██║██║  ██║██║  ██║\n");
    printf("\t██╔══██╗██║██╔══╝  ██║╚████║ ╚████╔╝ ██╔══╝  ██║╚████║██║██║  ██║██║  ██║\n");
    printf("\t██████╦╝██║███████╗██║ ╚███║  ╚██╔╝  ███████╗██║ ╚███║██║██████╔╝╚█████╔╝\n");
    printf("\t╚═════╝ ╚═╝╚══════╝╚═╝  ╚══╝   ╚═╝   ╚══════╝╚═╝  ╚══╝╚═╝╚═════╝  ╚════╝");
    printf("\n\n");
    printf("\t\t      ░█ ░█ ░█▀▀▀█ ░█▀▀▀█ ░█▀▀█ ▀█▀ ▀▀█▀▀ ░█▀▀█ ░█\n");
    printf("\t\t      ░█▀▀█ ░█  ░█  ▀▀▀▄▄ ░█▄▄█ ░█   ░█   ░█▄▄█ ░█\n");
    printf("\t\t      ░█ ░█ ░█▄▄▄█ ░█▄▄▄█ ░█    ▄█▄  ░█   ░█ ░█ ░█▄▄█\n");

    printf("\n █▀▀▀█ █▀▀█ █    　 █   █ ▀█▀ █   █ █▀▀▀█ 　 █▀▀▀█ ▀█▀ 　 █▀▀█ █  █ █▀▀▀ █▀▀▄ █▀▀▀ █▀▀▀█ \n");
    printf(" ▀▀▀▄▄ █▄▄█ █    　 █   █  █  █   █ █   █ 　 ▀▀▀▄▄  █  　 █▄▄█ █  █ █▀▀▀ █  █ █▀▀▀ ▀▀▀▄▄ \n");
    printf(" █▄▄▄█ █  █ █▄▄█ 　  ▀▄▀  ▄█▄  ▀▄▀  █▄▄▄█ 　 █▄▄▄█ ▄█▄ 　 █    ▀▄▄▀ █▄▄▄ █▄▄▀ █▄▄▄ █▄▄▄█\n\n\n\n");

    /*ALMACENAMOS EL IDENTIFICADOR DEL PROCESO*/
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    /*ALMACENAMOS EL NUMERO DE PROCESOS*/
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    tmpinic = MPI_Wtime();
    if (id == 0)
    {
        menu_principal();
    }
    tmpfin = MPI_Wtime();

    if (id == 0)
    {
        printf("\n\n\t\t---- 🇹 ​​​​​🇮​​​​​ 🇪​​​​​ 🇲​​​​​ 🇵​​​​​ 🇴 ​​​​​🇸​​​​​  🇩​​​​​ 🇪 ​​​​​ 🇪 ​​​​​🇯​​​​​ 🇪 ​​​​​🇨 ​​​​​🇺​​​​​ 🇨 ​​​​​🇮​​​​​ 🇴​​​​​ 🇳​ ​​​​ ----\n\n");
        fprintf(stdout, "proceso 1 menu de secretaria: %f\n\n", tmp1fs - tmp1s);
        fprintf(stdout, "   subproceso 1 del menu de secretarias(catalogos): %f\n\n", tmp1fsc - tmp1sc);
        fprintf(stdout, "   subproceso 2 del menu de secretarias(procesos): %f\n\n", tmp2fsp - tmp2sp);
        fprintf(stdout, "   subproceso 3 del menu de secretarias(reportes): %f\n\n", tmp3fsr - tmp3sr);
        fprintf(stdout, "proceso 2 menu de medico: %f\n\n", tmp3fm - tmp3m);
        fprintf(stdout, "   subproceso 1 del menu de medico(catalogos): %f\n\n", tmp1fmc - tmp1mc);
        fprintf(stdout, "   subproceso 2 del menu de medico(procesos): %f\n\n", tmp2fmp - tmp2mp);
        fprintf(stdout, "   subproceso 3 del menu de medico(reportes): %f\n\n", tmp3fmr - tmp3mr);
        fprintf(stdout, "Tiempo total de ejecucion del programa o proceso principal: %f\n\n", tmpfin - tmpinic);
    }
    MPI_Finalize;
    return 0;
} // Fin del Main