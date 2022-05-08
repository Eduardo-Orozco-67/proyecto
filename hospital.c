#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
#include <mpi.h>

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

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀█ ─█▀▀█ ░█▀▀█ ▀█▀ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ ░█▀▀▀
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█▄▄█ ░█▄▄█ ░█─── ░█─ ░█▀▀▀ ░█░█░█ ─░█── ░█▀▀▀
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█─── ░█─░█ ░█▄▄█ ▄█▄ ░█▄▄▄ ░█──▀█ ─░█── ░█▄▄▄

void Alta_Paciente()
{ 
    int num_paciente, edad_p, respAddP, opcRep, c, d, aFila, aColumna;
    char nombre_p[50], appat_p[50], apmat_p[50], direccion_p[60], addPaciente[700];
    setbuf(stdin, NULL);

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

    do
    {
        printf("\nIngresar el nombre del paciente: ");
        scanf("%s", nombre_p);
        printf("Ingresar el apellido paterno del paciente: ");
        scanf("%s", appat_p);
        printf("Ingresar el apellido materno del paciente: ");
        scanf("%s", apmat_p);
        setbuf(stdin, NULL);
        printf ("ban0\n");
        sprintf (addPaciente, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s';", nombre_p, appat_p, apmat_p);//busca si ya existe el paciente en nustra bdd
        resultado = PQexec(bd, addPaciente); //Ejecuta linea postgres
        printf ("ban1\n");
        //Si es uno quiere decir que si lo encontro, por lo tanto ya no se piden los demás datos
        if (PQntuples (resultado) == 1)
        {
            printf("ban 2\n");
            printf("\nPaciente encontrado\n");
            printf("\nIngrese otro paciente!\n\n");
        }
        else
        {
            printf("ban 2.0n");
            printf("\nPaciente NO encontrado. Complete los datos\n");
            printf("Ingresar la edad del paciente: ");
            scanf("%i", &edad_p);
            printf("Ingresar la direccion del cliente: ");
            scanf("%s", direccion_p);

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
        }//fin de la validacion
        do
        {
            printf ("\n¿Desea agregar otro Paciente?\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &respAddP);
            setbuf(stdin, NULL); //Limpiar el buffer
        }while  (respAddP != 1 && respAddP != 2);
    } while (respAddP == 1 );
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
        printf("Ingresar de favor el numero del paciente el cual desea eliminar:\n");
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
                printf("Ingresar de favor el nombre anteriormente guardado:\n");
                scanf("%s", nombre_paciente);
                printf("Ingresar de favor el nombre nuevo a guardar\n");
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
                printf("Ingresar de favor el apellido paterno anteriormente guardado:\n");
                scanf("%s", appat_p);
                printf("Ingresar de favor el apellido paterno nuevo a guardar\n");
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
                printf("Ingresar de favor el apellido materno anteriormente guardado:\n");
                scanf("%s", apmat_p);
                printf("Ingresar de favor el apellido materno nuevo a guardar\n");
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
                printf("Ingresar de favor la edad anteriormente guardado:\n");
                scanf("%i", &edad_p);
                printf("Ingresar de favor la edad nueva a guardar\n");
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
                printf("Ingresar de favor la direccion anteriormente guardado:\n");
                scanf("%s", direccion);
                printf("Ingresar de favor la direccion nueva a guardar\n");
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
                printf("Ingresar una opcion valida, de favor\n\n");
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
        printf("Ingresar de favor el numero del paciente el cual desea eliminar:\n");
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
            case 1: //caso para selecionar todos los datos de un paciente en especifico
            
                printf("\n\nOpcion uno:\n\n");
                printf("Ingresar de favor el numero del paciente deseado del cual desea ver todos los datos: \n");
                scanf("%i", &bNum_Paciente);
                sprintf(selecPaciente, "select * from Paciente where num_paciente = %i", bNum_Paciente);
                resultado = PQexec(bd, selecPaciente);
                printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                if (PQntuples (resultado) == 1)
                {
                    printf("Pacientes encontrado! \n\n\n");
                    printf("Mostrando resultado del punto 1: \n\n\n");
                    if (resultado != NULL)
                    {
                    
                        bFila = PQntuples(resultado);
                        bColumna = PQnfields(resultado);

                        for (a = 0; a < bFila; a++)
                        {
                            for ( b = 0; b < bColumna; b++)
                            {
                                printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                            }//fin del for bColumna
                            printf("\n\n");
                        }//fin del for bFila
                    }//fin del if-null
    
                }else{

                    printf("Paciente no encontrado! \n\n");
                }
                
            break;

            case 2: //opcion para ver un dato en especifico de un cliente en especifico

                setbuf(stdin, NULL);
                printf("Opcion dos:\n\n");
                printf("Ingresar de favor el numero del paciente deseado del cual desea ver un dato en especifico: \n");
                scanf("%i", &bNum_Paciente);
                sprintf(selecPaciente, "select * from Paciente where num_paciente = %i", bNum_Paciente);
                resultado = PQexec(bd, selecPaciente);

                if (PQntuples (resultado) == 1)//valida si encuntra el paciente
                {
                    printf("Pacientes encontrado! \n\n\n\n");


                    printf("Seleccionar una de las opciones ofertadas: \n");
                    printf(" 1.- Nombre \n 2.- Apellidos \n 3.- Edad \n 4.- Direccion \n\n");
                    scanf("%i", &opcVer);
                    switch (opcVer)
                    {
                        case 1: //caso para el nombre
                            setbuf(stdin, NULL);
                            printf("Ingresar de favor el numero del paciente deseado del cual desea ver el dato: \n");
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
                                    for ( b = 0; b < bColumna; b++)
                                    {
                                        printf("El nombre del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                    }//fin del for bColumna
                                    printf("\n\n");
                                }//fin del for bFila
                            }//fin del if-null
                        break;
                
                        case 2: //caso para los apellidos
                            setbuf(stdin, NULL);
                            printf("Ingresar de favor el numero del paciente deseado del cual desea ver el dato: \n");
                            scanf("%i", &bNum_Paciente);
                            setbuf(stdin, NULL);
                            sprintf(selecPaciente, "select appat_p, apmat_p from Paciente where num_paciente = %i", bNum_Paciente);
                            resultado = PQexec(bd, selecPaciente);
                            printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                            if (PQntuples (resultado) == 1)
                            {
                                printf("Pacientes encontrado! \n\n");

                                if (resultado != NULL)
                                {
                    
                                    bFila = PQntuples(resultado);
                                    bColumna = PQnfields(resultado);
                                    printf("Los apellidos del paciente son: \n");
                                    for (a = 0; a < bFila; a++)
                                    {
                                        for ( b = 0; b < bColumna; b++)
                                        {
                                            printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                                        }//fin del for bColumna
                                        printf("\n\n");
                                    }//fin del for bFila
                                }//fin del if-null

                            }else{
                                printf("Paciente no encontrado! \n\n");
                            }
                        break;//break case 2

                        case 3://case 3 para la edad
                            setbuf(stdin, NULL);
                            printf("Ingresar de favor el numero del paciente deseado del cual desea ver el dato: \n");
                            scanf("%i", &bNum_Paciente);
                            setbuf(stdin, NULL);
                            sprintf(selecPaciente, "select edad_p from Paciente where num_paciente = %i", bNum_Paciente);
                            resultado = PQexec(bd, selecPaciente);
                            printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                            if (PQntuples (resultado) == 1)
                            {
                                printf("Pacientes encontrado! \n\n");

                                if (resultado != NULL)
                                {
                    
                                    bFila = PQntuples(resultado);
                                    bColumna = PQnfields(resultado);

                                    for (a = 0; a < bFila; a++)
                                    {
                                        for ( b = 0; b < bColumna; b++)
                                        {
                                            printf("La edad del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                        }//fin del for bColumna
                                        printf("\n\n");
                                    }//fin del for bFila
                                }//fin del if-null

                            }else{
                                printf("Paciente no encontrado! \n\n");
                            }

                        break;

                        case 4://case 4 para la direccion
                            setbuf(stdin, NULL);
                            printf("Ingresar de favor el numero del paciente deseado del cual desea ver el dato: \n");
                            scanf("%i", &bNum_Paciente);
                            sprintf(selecPaciente, "select direccion from Paciente where num_paciente = %i", bNum_Paciente);
                            resultado = PQexec(bd, selecPaciente);
                            printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                            if (PQntuples (resultado) == 1)
                            {
                                printf("Pacientes encontrado! \n\n");

                                if (resultado != NULL)
                                {
                    
                                    bFila = PQntuples(resultado);
                                    bColumna = PQnfields(resultado);

                                    for (a = 0; a < bFila; a++)
                                    {
                                        for ( b = 0; b < bColumna; b++)
                                        {
                                            printf("La direccion del paciente es: %s\t | \t ", PQgetvalue(resultado, a, b));
                                        }//fin del for bColumna
                                        printf("\n\n");
                                    }//fin del for bFila
                                }//fin del if-null

                            }else{
                                printf("Paciente no encontrado! \n\n");
                            }

                        break;

                    default:
                        printf("\n\nElegir una de las opciones ofrecidas!\n\n");
                    break;
                }


                }else{//else paciente no encontrado
                    printf("Paciente no encontrado! \n\n");
                }


            break;

            case 3:
                //opcion de ver los datos de todos los pacientes

                sprintf(selecPaciente, "select * from Paciente");
                resultado = PQexec(bd, selecPaciente);
                printf("Opcion SQL antes de ejecutarse: %s\n\n", selecPaciente);


                    if (resultado != NULL)
                    {
                    
                        bFila = PQntuples(resultado);
                        bColumna = PQnfields(resultado);

                        for (a = 0; a < bFila; a++)
                        {
                            for ( b = 0; b < bColumna; b++)
                            {
                                printf("%s\t | \t ", PQgetvalue(resultado, a, b));
                                }//fin del for bColumna
                                printf("\n\n");
                            }//fin del for bFila
                    }//fin del if-null

            break;

            case 4: 
                printf("\n\n");
            break;
        
            default:
                printf("\n\nIngrsar una copcion valida, de favor\n\n");
            break;
        }

    } while (opcSelecPac != 4);

            printf ("\n¿Desea usar otra funcion?\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &respConsP);
            setbuf(stdin, NULL); //Limpiar el buffer
    }while  (respConsP != 1 && respConsP != 2);
}

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀▀ ▀▄░▄▀ ░█▀▀█ ░█▀▀▀ ░█▀▀▄ ▀█▀ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ ░█▀▀▀
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█▀▀▀ ─░█── ░█▄▄█ ░█▀▀▀ ░█─░█ ░█─ ░█▀▀▀ ░█░█░█ ─░█── ░█▀▀▀
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█▄▄▄ ▄▀░▀▄ ░█─── ░█▄▄▄ ░█▄▄▀ ▄█▄ ░█▄▄▄ ░█──▀█ ─░█── ░█▄▄▄

void alta_expediente()
{
}

void borrar_expediente()
{
}

void modificar_expediente()
{
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
    char presplc [100], consultorio[10], fechac[20], hora[20], nombre[20], appat[20], apmat[20], buspac[200], alta[200];

    time_t t;
    char fecha[100];
    t = time(NULL);
    char *ch;
    ch = ctime(&t);
    strcpy(fecha, ch);
    // printf("%s",fecha);

    do
    {
        //Buscar el cliente por nombre completo 
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
            //printf ("\nEl valor de retorno es: %i", prespl);
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

//Funcion para modificar una consulta
void ModificarConsulta()
{
    int resp, mod, modcita, num_paciente, i, j, columna, fila, idcita;
    char edit[500], busconsul [300], buspac[300], nombre[20], appat[20], apmat[20], fecha[30], hora[20], consultorio[10], cedula [10], busnumpac[200], buspacit[200], busnum[200];
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
                printf ("\nEl paciente cuenta con citas. Buscando consultas...\n");
                idcita = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
                //selecciona todos los datos de la tabla de consulta
                sprintf(busconsul, "select * from consulta where id_cita = %i", idcita); 
                resu = PQexec(bd, busconsul); // Ejecuta linea postgres 

                if (PQntuples(resu) == 0)
                {
                    printf("\n ATENCION: este paciente NO cuenta con consultas agendadas.\n");
                }
                else
                {  
                    //entra cuando encuentra consultas del paciente
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
                            //buscar si la cedula existe
                            sprintf(buspacit, "select * from medico where cedula = '%s'", cedula);
                            ress = PQexec(bd, buspacit); // Ejecuta linea postgres
                            //entra si el medico no existe
                            if (PQntuples(ress) == 0)
                            {
                                printf ("\n ATENCION: El medico no existe\n");
                            }
                            else 
                            {
                                printf ("\nEl medico ha sido encontrado. Guardando modificacion...\n");
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
                }//fin del if -else para saber si tiene consultas
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

// ░█▀▀█ ░█▀▀█ ░█─░█ ░█▀▀▄ 　 ░█▀▀▄ ▀█▀ ─█▀▀█ ░█▀▀█ ░█▄─░█ ░█▀▀▀█ ░█▀▀▀█ ▀▀█▀▀ ▀█▀ ░█▀▀█ ░█▀▀▀█
// ░█─── ░█▄▄▀ ░█─░█ ░█─░█ 　 ░█─░█ ░█─ ░█▄▄█ ░█─▄▄ ░█░█░█ ░█──░█ ─▀▀▀▄▄ ─░█── ░█─ ░█─── ░█──░█
// ░█▄▄█ ░█─░█ ─▀▄▄▀ ░█▄▄▀ 　 ░█▄▄▀ ▄█▄ ░█─░█ ░█▄▄█ ░█──▀█ ░█▄▄▄█ ░█▄▄▄█ ─░█── ▄█▄ ░█▄▄█ ░█▄▄▄█














//-------------------------------------------------------------FUNCIONES PARA LAS CONSULTAS - REPORTES
void Consulta_A() 
{
    char con1[1000], cedula [10], busced[200]; 
    int i,j,fila,columna, opc;
    do
    {
        printf ("\n");
        printf("\t REPORTRES DEL SISTEMA\n");
        printf ("\nLista de pacientes de cada medico\n\n");
        printf ("Ingrese la cedula del medico: ");
        scanf ("%s", cedula);
        setbuf(stdin, NULL); // Limpiar el buffer
        // Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf(busced, "Select * from medico where cedula = '%s';", cedula);
        ress = PQexec(bd, busced); // Ejecuta linea postgres
        //Evaluar que el medico
        if (PQntuples(ress) == 0)
        {
            printf ("\nATENCION: el medico no ha sido encontrado\n");
        }
        else 
        {
            printf ("\nMedico encontrado\n");
            sprintf(con1,"select p.num_paciente, p.nombre_p, p.appat_p, p.apmat_p, m.cedula, m.nombre_m, m.appat_m, m.apmat_m from paciente p inner join cita ci on p.num_paciente = ci.num_paciente   inner join consulta co on ci.id_cita = co.id_cita inner join medico m on m.cedula = co.cedula where m.cedula = '%s';", cedula);
            printf("Instruccion SQL antes de ejecutarse: %s \n",con1); //Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec (bd, con1); //Ejecuta linea postgres
            
            fila = PQntuples(resultado); //filas de la tabla
            if (fila == 0)
            {
                printf ("La tabla está vacía\n");      	
            }
            else
            {     	
                columna = PQnfields(resultado); //Columnas de la tabla
                printf("--------------------------------------------------------------------------------------------------------------------------\n");   
                printf ("| Paciente |    Nombre   |            Apellidos        |     Cedula    |     Medico    |            Apellidos        |\n");            	
                for (i = 0; i < fila ; i++)
                {
                    printf("--------------------------------------------------------------------------------------------------------------------------\n");
                    for (j = 0; j < columna; j++)
                    {
                        printf("     %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
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

void consulta_e()
{
    char consulta[400], fecha[50];
    int i,j,fila,columna;

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

                                case 2: // Metodo
                                    Actualizar_Paciente();                           
                                    break;

                                case 3:// Metodo
                                    Eliminar_Paciente(); 
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

                                    break;

                                case 2: // Metodo eliminar
                                    EliminarConsulta();
                                    break;

                                case 3: // Metodo modificar

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
                                    // Metodo
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
                                    // Metodo
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
                            break;

                        case 2:
                            // Metodo
                            break;

                        case 3: //Metodo consulta E
                            consulta_e();
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
                                            // Metodo alta especialidad
                                            break;

                                        case 2:
                                            // Metodo baja especialidad
                                            break;

                                        case 3:
                                            // Metodo modificar especialidad
                                            break;

                                        case 4:
                                            // Metodo consulta especialidad
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
                                    // Metodo alta diagnostico
                                    break;

                                case 2:
                                    // Metodo baja diagnostico
                                    break;

                                case 3:
                                    // Metodo modificar diagnostico
                                    break;

                                case 4:
                                    // Metodo consultar diagnostico
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
                                    // Metodo ver paciente
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
                                            // Metodo agregar expediente
                                            break;

                                        case 2:
                                            // Metodo modificar expediente
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
                            Consulta_A ();
                            break;

                        case 2:
                            // Metodo D)
                            break;

                        case 3: // Metodo E)                            
                            consulta_e();
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
    char database[15] = "hospital1";
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