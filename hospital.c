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

//Metodos para el menu de la secretaria --------------------------------------------------------------------------------------------
void Alta_Paciente()    
{
    int num_paciente, edad_p;
    char nombre_p[50], appat_p[50], apmat_p[50], direccion_p[60], addPaciente[700];
    setbuf(stdin, NULL);

    printf("Listado de pacientes: \n\n");

    printf("Ingresar el nombre del paciente: \n");
    scanf("%s", nombre_p);
    printf("Ingresar el apellido paterno del paciente: \n");
    scanf("%s", appat_p);
    printf("Ingresar el apellido materno del paciente: \n");
    scanf("%s", apmat_p);
    setbuf(stdin, NULL);
    sprintf (addPaciente, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre_p, appat_p, apmat_p);//busca si ya existe el cliente en nustra bdd
    resultado = PQexec(bd, addPaciente); //Ejecuta linea postgres
    //Si es uno quiere decir que si lo encontro, por lo tanto ya no se piden los demás datos
    if (PQntuples (resultado) == 1){
    	printf("\nPaciente encontrado\n");
        printf("\nIngrese otro paciente!\n\n");
    }else{

        printf("Ingresar la edad del paciente: \n");
        scanf("%i", &edad_p);
        printf("Ingresar la direccion del cliente: \n");
        scanf("%s", direccion_p);

        sprintf(addPaciente, "insert into Paciente ( nombre_p, appat_p, apmat_p, edad_p, direccion) values ( '%s', '%s', '%s', '%i', '%s')", nombre_p, appat_p, apmat_p, edad_p, direccion_p);
        printf("Instruccion SQL antes de ejecutarse: %s", addPaciente);
        resultado = PQexec(bd, addPaciente);

        if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
        {
            printf("\n\nInserccion exitosa!\n\n");
        }else{
            printf("Inserccion sin exito! \n\n");
        }

    }//fin de la validacion 
}

void Actualizar_Paciente()
{

}

void Eliminar_Paciente()
{

}

void Seleccionar_Paciente()
{

    setbuf(stdin, NULL);
    char selecPaciente[500];
    int opcSelecPac = 0, bNum_Paciente, bFila, bColumna, a, b, opcVer;
    printf("Seleccionar una de las opciones anteriores: \n");
    do
    {
        printf(" 1.- Selecionar todos los datos de un paciente en especifico \n 2.- Seleccionar un dato en especifico que desea ver de un paciente en especifico \n 3.- Ver los datos de todos los pacientes\n\n");
        scanf("%i", &opcSelecPac);
        switch (opcSelecPac)
        {
            case 1: //caso para selecionar todos los datos de un paciente en especifico
            
                printf("Opcion uno:\n\n");
                printf("Ingresar de favor el numero del paciente deseado del cual desea ver todos los datos: \n");
                scanf("%i", &bNum_Paciente);
                sprintf(selecPaciente, "select * from Paciente where num_paciente = %i", bNum_Paciente);
                resultado = PQexec(bd, selecPaciente);
                printf("Oopcion SQL antes de ejecutarse: %s\n\n", selecPaciente);
                if (PQresultStatus(resultado) == PGRES_COMMAND_OK)
                {
                    printf("Pacientes encontrado! \n\n");
                }else{
                    printf("Pacienste no encontrado! \n\n");
                }

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

            case 2: //opcion para ver un dato en especifico de un cliente en especifico
                
                setbuf(stdin, NULL);
                printf("Opcion dos:\n\n");
                printf("Ingresar de favor el numero del paciente deseado del cual desea ver un dato en especifico: \n");
                scanf("%i", &bNum_Paciente);
                printf("Seleccionar una de las opciones ofertadas: \n");
                printf("1.- Nombre \n 3. Apellido Paterno \n 4. Apellido Materno \n 5. Edad \n 6. Direccion \n\n");
                scanf("%i", &opcVer);
                switch (opcVer)
                {
                case 1:
                    sprintf(selecPaciente, "select nombre_p from Paciente where num_paciente = %i", bNum_Paciente);
                    break;
                
                default:
                    break;
                }


            break;

            case 3:
            break;

        
        default:
            break;
        }

    } while (opcSelecPac != 4);
    
}   

//CRUD Expediente ------------------------------------------------------------------------------------------------s
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
    int i,j,fila,columna;    
    //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad,"select * from Expediente order by num_exp");
    printf("Instruccion SQL antes de ejecutarse: %s \n",cad); //Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec (bd, cad); //Ejecuta linea postgres

    fila = PQntuples(resultado); //filas de la tabla
    if (fila == 0)
    {
    	printf ("ATENCION: La tabla está vacía\n");      	
    }else
    {     	
       	columna = PQnfields(resultado); //Columnas de la tabla 
        printf ("---------------------------------------------------------------------------\n"); 
       	printf ("| Num_exp | Num_paciente  |    Alergias     |\n");               	
       	for (i = 0; i < fila ; i++)
       	{
                printf ("---------------------------------------------------------------------------\n"); 
              	for (j = 0; j < columna; j++)
              	{
                        
                    printf("|    %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
		        }
		    printf("\n");
        }
    }

}

//Funciones para el catalago de CITA -----------------------------------------------------------------------------------------
void GuardarCita()
{
    int num_paciente, resp;
    char consultorio[10], fechac [20], hora[20], nombre[20], appat[20], apmat[20], buspac[200], alta[200];  

    time_t t;
    char fecha[100];
    t=time(NULL);
    char *ch ;
    ch = ctime(&t); 
    strcpy(fecha, ch);
    //printf("%s",fecha); 

    do
    {
        //Buscar el cliente por nombre completo
        printf ("\n===============");
    	printf("|AGENDAR UNA CITA|");
        printf ("===============\n");
        setbuf(stdin, NULL); //Limpiar el buffer
        printf("\nIngrese el nombre del paciente: ");
    	scanf ("%[^\n]", nombre);
    	setbuf(stdin, NULL); //Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
    	scanf ("%[^\n]", appat);
        setbuf(stdin, NULL); //Limpiar el buffer
        printf("Ingrese el apellido materno del paciente: ");
    	scanf ("%[^\n]", apmat);
    	setbuf(stdin, NULL); //Limpiar el buffer

        //Sentencia SQL para saber si el paciente ya ha sido registrado
    	sprintf (buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre, appat, apmat);
    	resultado = PQexec(bd, buspac); //Ejecuta linea postgres
    	//Si es uno quiere decir que si lo encontro
        if (PQntuples (resultado) == 1){
    	    printf("\nPaciente encontrado. Agende la cita\n");            
            //Obtener el numero del paciente de la consulta           
            //El numero del paciente se puede dar por defecto con buscar el paciente	    
            num_paciente = strtol(PQgetvalue(resultado, 0, 0), NULL, 10);
            printf ("\n");
    	    printf("\t Agendar una nueva cita");
    	    //Pedir que el usuario ingrese los datos 
    	    printf("\nIngrese el consultorio: ");
   	        scanf ("%[^\n]", consultorio);
   	        setbuf(stdin, NULL); //Limpiar el buffer
            
            //Condicion para que la fecha sea mayor o igual a la del dia de hoy ***********************MODIFICAR CONDICION PARA LA FECHA
            do{
   	        printf("Ingrese fecha de la cita (DD-MM-AAAA): ");
   	        scanf ("%s", fechac);
            setbuf(stdin, NULL); //Limpiar el buffer
            }while(fechac >= fecha); 
    	    
   	        printf("Ingrese hora de la cita (HH:MM:SS): ");
   	        scanf ("%s", hora);
    	    setbuf(stdin, NULL); //Limpiar el buffer




            //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    	    sprintf(alta,"insert into Cita (num_paciente, consultorio, fecha, hora) values (%i, '%s', '%s', '%s');", num_paciente, consultorio, fechac, hora);
    
    	    printf("\nInstruccion SQL antes de ejecutarse: %s \n", alta); //Mostrar instruccion SQL
    	    printf("\n");
    	    resultado = PQexec(bd, alta); //Ejecuta linea postgres  
    	    printf("La cita ha sido agendada\n");
      
        //fin del else del if PQntuples donde se busca el paciente 
        }
        else
        {
            printf ("\nATENCION: El paciente no ha sido registrado \n");         
        }
        //Validar si desea eliminar otro registro
     	do
        {
            printf ("\n¿Desea agendar otra cita\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &resp);
            setbuf(stdin, NULL); //Limpiar el buffer
        }while  (resp != 1 && resp != 2); 
    }while (resp == 1);     			
}

//Funcion para modificar datos de la cita
void ModificarCita()
{
    int resp, mod, modcita, num_paciente, i, j, columna, fila;   
    char edit[500], buspac[300], nombre[20], appat[20], apmat[20], fecha[30], hora[20], consultorio[10], busnumpac[200], buspacit[200], busnum[200];
    do
    {
        //Buscar el cliente por nombre completo
        printf ("\n===============");
        printf("|MODIFICAR UNA CITA|");
        printf ("===============\n");
        setbuf(stdin, NULL); //Limpiar el buffer
        printf("\nIngrese el nombre del paciente: ");
        scanf ("%[^\n]", nombre);
        setbuf(stdin, NULL); //Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
        scanf ("%[^\n]", appat);
        setbuf(stdin, NULL); //Limpiar el buffer
        printf("Ingrese el apellido materno del paciente: ");
        scanf ("%[^\n]", apmat);
        setbuf(stdin, NULL); //Limpiar el buffer

        //Sentencia SQL para saber si el paciente ya ha sido registrado
        sprintf (buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s'", nombre, appat, apmat);
        ressu = PQexec(bd, buspac); //Ejecuta linea postgres        
    
        //Pedir que se ingrese los datos del usuario que se desea editar
        //Si es uno quiere decir que si lo encontro               
        if (PQntuples (ressu) == 1)
        {
            
            printf("\nPaciente encontrado.\n");           
            //Obtener el numero del paciente de la consulta           
            //buscar el numero del paciente obtenido en la consulta anterior 	    
            num_paciente = strtol(PQgetvalue(ressu, 0, 0), NULL, 10); 

            sprintf (buspacit, "select * from cita where num_paciente = %i", num_paciente);
            ress = PQexec(bd, buspacit); //Ejecuta linea postgres  
            //extraer el id de la cita
            //idcita = strtol(PQgetvalue(ress, 0, 0), NULL, 10); 
            //Evaluar si se ha encontrado citas para este paciente 
            if (PQntuples (ress) == 0)
            {
                 printf ("\n ATENCION: este paciente NO cuenta con citas agendadas.\n");
            }
            else
            {               
                printf("\nCitas del paciente encontradas.\n");            
                //Imprimir todas las citas del paciente            
                fila = PQntuples(ress); //filas de la tabla
                if (fila == 0)
                {
                    printf ("ATENCION: La tabla está vacía\n");      	
                }
                else
                {     	
                    columna = PQnfields(ress); //Columnas de la tabla 
                    printf ("---------------------------------------------------------------------------\n"); 
                    printf ("|id_cita | Paciente  |    Consultorio     |             Fecha/Hora         |\n");               	
                    for (i = 0; i < fila ; i++)
                    {
                        printf ("---------------------------------------------------------------------------\n"); 
                        for (j = 0; j < columna; j++)
                        {                        
                            printf("|    %s\t",PQgetvalue(ress,i,j)); //Resultado fila y columna de la consulta
                        }
                        printf("\n");
                    }
                }

                //Preguntar cual es la cita que desea modificar 
                printf ("\nIngrese la cita que desea modificar: ");
                scanf ("%i", &modcita);
                
                do
                {
                    printf ("Elija el dato que desea editar\n");
                    printf("\n 1.- Consultorio\n 2.- Fecha \n 3.- Hora \n 4.- Regresar\n");
                    printf ("Opcion: ");
                    scanf ("%i", &mod); 
                    setbuf(stdin, NULL); //Limpiar el buffer    	
                    switch (mod)
                    {
                            case 1:
                                //Agregar dato modificado el consultorio
                                printf("\nIngrese el nuevo consultorio: ");
                                scanf ("%s", consultorio);
                                sprintf(edit,"UPDATE Cita set consultorio = '%s' where id_cita = %i", consultorio, modcita);    			    
   			                    printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); //Mostrar instruccion SQL
                                printf("\n");  
                                resultado = PQexec(bd, edit); //Ejecuta linea postgres
                                break; 

                            case 2:
                                //Agregar dato modificado la fecha
                                printf("\nIngrese la nueva fecha (DD-MM-AAAA): ");
                                scanf ("%s", fecha);
                                sprintf(edit,"UPDATE Cita set fecha = '%s' where id_cita = %i", fecha, modcita);    			    
   			                    printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); //Mostrar instruccion SQL
                                printf("\n");  
                                resultado = PQexec(bd, edit); //Ejecuta linea postgres
                                break; 

                            case 3:
                                //Agregar dato modificado la hora
                                printf("\nIngrese la nueva hora: ");
                                scanf ("%s", hora);
                                sprintf(edit,"UPDATE Cita set hora = '%s' where id_cita = %i", hora, modcita);    			    
   			                    printf("\nInstruccion SQL antes de ejecutarse: %s \n", edit); //Mostrar instruccion SQL
                                printf("\n");  
                                resultado = PQexec(bd, edit); //Ejecuta linea postgres
                                break; 

    		                case 4:
    			                printf ("\nRegresando...\n");
    			                break;
    			
                            default:
                                printf ("\nIngrese una opcion correcta\n");	   			    			
    	            } //Fin del switch
                } while (mod !=4);
            }//fin del if - else para saber si el paciente tiene cita

        }//fin del if para saber si el paciente existe
        else 
        {
            printf ("\n ATENCION: este paciente NO ha sido ingresado.\n");
        } 

        //Validar si el usuario quiere modificar otro registro
        do{
            printf ("\n¿Desea modificar otro cliente\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &resp);
            setbuf(stdin, NULL); //Limpiar el buffer
        } while  (resp != 1 && resp != 2); 
    } while(resp == 1); 

}

//Funcion para eliminar una cita
void EliminarCita()
{
    int resp, num_pac;
    char nombre [20], appat[20], apmat[20], elim[100], buspac[200];	   
    do
    {
        //Buscar el paciente por nombre completo
        printf ("\n===============");
    	printf("|ELIMINAR UNA CITA|");
        printf ("===============\n");
        printf("\nIngrese el nombre del paciente: ");
    	scanf ("%s", nombre);
    	setbuf(stdin, NULL); //Limpiar el buffer
        printf("Ingrese el apellido paterno del paciente: ");
    	scanf ("%s", appat);
        printf("Ingrese el apellido materno del paciente: ");
    	scanf ("%s", apmat);
    	setbuf(stdin, NULL); //Limpiar el buffer
        //Sentencia SQL para saber si el paciente ya ha sido registrado
    	sprintf (buspac, "select num_paciente from paciente where nombre_p = '%s' and appat_p = '%s' and apmat_p = '%s';", nombre, appat, apmat);
    	ress = PQexec(bd, buspac); //Ejecuta linea postgres
    
   	    if (PQntuples (ress) == 0){
            //Entra si el cliente no se encuentra registrado
		    printf("Error al eliminar la cita. Registro no encontrado\n\n");    	
        }
        else
        {
            printf("Registro encontrado\n\n");    
	        //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
            num_pac = strtol(PQgetvalue(ress, 0, 0), NULL, 10);
    	    sprintf(elim,"delete from cita where num_paciente = %i;", num_pac);
    	    //fflush (stdin);
    	    printf("\nInstruccion SQL antes de ejecutarse: %s \n", elim); //Mostrar instruccion SQL
    	    printf("\n");
            ress = PQexec(bd, elim); //Ejecuta linea postgres  
    	    printf ("\n ¡La cita ha sido eliminada!\n");        
   	    } //Fin del else if (PQntuples)     	
        //Validar si desea eliminar otro registro
        do{
            printf ("\n¿Desea eliminar otra cita\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &resp);
            setbuf(stdin, NULL); //Limpiar el buffer
        }while  (resp != 1 && resp != 2); 
    }while (resp == 1);   
}

//Funcion para consultar una cita
void ConsultarCita()
{
    char tab[50], cad[100];
    int i,j,fila,columna;    
    //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad,"select * from cita order by id_cita");
    printf("Instruccion SQL antes de ejecutarse: %s \n",cad); //Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec (bd, cad); //Ejecuta linea postgres

    fila = PQntuples(resultado); //filas de la tabla
    if (fila == 0){
    	printf ("ATENCION: La tabla está vacía\n");      	
    }else{     	
       	columna = PQnfields(resultado); //Columnas de la tabla 
        printf ("---------------------------------------------------------------------------\n"); 
       	printf ("|id_cita | Paciente  |    Consultorio     |             Fecha/Hora         |\n");               	
       	for (i = 0; i < fila ; i++)
       	{
                printf ("---------------------------------------------------------------------------\n"); 
              	for (j = 0; j < columna; j++)
              	{
                        
                      	printf("|    %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
		}
		printf("\n");
        }
    }
}

//Funciones para el catalago de CONSULTA -----------------------------------------------------------------------------------------
//Funcion para eliminar una cita
void EliminarConsulta()
{
    int resp, num_pac, id_con;
    char nombre [20], appat[20], apmat[20], elim[100], buspac[200], busc[100];	   
    do
    {
        //Buscar el paciente por nombre completo
        printf ("\n===============");
    	printf("|ELIMINAR UNA CONSULTA|");
        printf ("===============\n");

        //Sentencia SQL para saber si el paciente ya ha sido registrado
    	sprintf (buspac, "select c.id_cita, con.id_consulta, p.nombre_p, p.appat_p, p.apmat_p from paciente p inner join cita c on c.num_paciente = p.num_paciente inner join consulta con on  con.id_cita = c.id_cita;");
    	resultado = PQexec(bd, buspac); //Ejecuta linea postgres        
   	    if (PQntuples (resultado) == 0)
        {
            //Entra si el paciente no se encuentra registrado
		    printf("ATENCION: Error al eliminar la consultar. Dato incorrecto\n\n");    	
        }
        else
        {
            //Imprimir los datos de la consulta buspac
            char tab[50], cad[100];
            int i,j,fila,columna; 
            printf("RegistroS encontrados\n\n");
            
            fila = PQntuples(resultado); //filas de la tabla
            if (fila == 0)
            {
    	        printf ("ATENCION: La tabla está vacía\n");      	
            }
            else
            {     	
       	        columna = PQnfields(resultado); //Columnas de la tabla 
                printf ("-----------------------------------------------------------------------------------------------\n");
       	        printf ("|id_cita |  id_consulta  |   Nombre    |   Apellido paterno  |  Apellido paterno  |\n");               	
       	        for (i = 0; i < fila ; i++)
       	        {
                    printf ("-----------------------------------------------------------------------------------------------\n"); 
              	    for (j = 0; j < columna; j++)
              	    {                        
                        printf("|       %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
		            }
		            printf("\n");
                }   
            }
            printf("\nIngrese el numero de la consulta que desea eliminar: ");
    	    scanf ("%i", &id_con);
    	    setbuf(stdin, NULL); //Limpiar el buffer
            //Sentencia para buscar la consulta en la tabla y saber si realmente existe
            sprintf(busc,"select * from consulta where id_consulta = %i;", id_con);
            printf("\n");
            ress = PQexec(bd, busc); //Ejecuta linea postgres  

            if (PQntuples (ress) == 0)
            {
                //Entra si la consulta no se encuentra registrado
		        printf("ATENCION: Error al eliminar la consulta. Dato incorrecto\n\n");     
            }
            else 
            {
                //Entra cuando la consulta si está registrada
                sprintf(elim,"delete from consulta where id_consulta = %i;", id_con);
    	        //fflush (stdin);
    	        printf("\nInstruccion SQL antes de ejecutarse: %s \n", elim); //Mostrar instruccion SQL
    	        printf("\n");
                ress = PQexec(bd, elim); //Ejecuta linea postgres  
    	        printf ("\n ¡La cita ha sido eliminada!\n");
            }

   	    } //Fin del else if (PQntuples)     	
        //Validar si desea eliminar otro registro
        do{
            printf ("\n¿Desea eliminar otra cita\n");
            printf ("1.- Si \n2.- No");
            printf ("\nOpcion: ");
            scanf ("%i", &resp);
            setbuf(stdin, NULL); //Limpiar el buffer
        }while  (resp != 1 && resp != 2); 
    }while (resp == 1);   
}

void ConsultarConsulta()
{
    char tab[50], cad[100];
    int i,j,fila,columna;    
    //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad,"select * from consulta order by id_consulta");
    printf("Instruccion SQL antes de ejecutarse: %s \n",cad); //Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec (bd, cad); //Ejecuta linea postgres

    fila = PQntuples(resultado); //filas de la tabla
    if (fila == 0){
    	printf ("ATENCION: La tabla está vacía\n");      	
    }else{     	
       	columna = PQnfields(resultado); //Columnas de la tabla 
        printf ("---------------------------------------------------------------------------------------------\n"); 
       	printf ("|id_consulta | id_cita  |   Cedula    |      fecha     |     hora      |     Consultorio    |\n");               	
       	for (i = 0; i < fila ; i++)
       	{
                printf ("---------------------------------------------------------------------------------------------\n"); 
              	for (j = 0; j < columna; j++)
              	{
                        
                      	printf("|    %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
		}
		printf("\n");
        }
    }
}


//CRUD medicos y especialidad---------------------------------------------------------------------------
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

        if(PQntuples(resultado) == 0)
        {
            setbuf(stdin, NULL);
            printf("Ingrese la edad del medico(+18):");
            scanf("%i", &edad);

            if(edad >= 18)
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
                printf("Instruccion SQL antes de ejecutarse: %s \n", altaM); //Mostrar sentencia SQL
                printf("\n");
                resultado = PQexec(bd, altaM);

                if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
                {
    	            printf("\n El Medico ha sido guardado exitosamente\n");
                }else {
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
            scanf("%i", &resp);

        }while(resp == 1 && resp == 2); //Segundo while por si el suario desea ingresar otro medico

    }while(resp == 1);

}

void baja_medico()
{
    char cedula[20], baja[400], valid[200];
    int opcB;

    do
    {
        printf ("\nIngrese la Cedula del medico que desea dar de baja: ");
        scanf ("%s", cedula);
        setbuf(stdin, NULL); 

        sprintf(valid, "select * from Medico where cedula = '%s'", cedula);
        resultado = PQexec(bd, valid);

        if(PQntuples(resultado) == 0)
        {
            printf("\n No existe el medico que desea dar de baja...\n");
            opcB == 1;

        }else
        {
            sprintf(baja, "delete from Medico where cedula = '%s'", cedula);

            printf("Instruccion SQL antes de ejecutarse: %s \n", baja); //Mostrar instruccion SQL
            printf("\n");
            resultado = PQexec(bd, baja); //Ejecuta linea postgres   
    
            if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
            {
    	        printf("\nSe ha dado de baja exitosamente al medico\n");
            }else 
            {
    	        printf("\nError al dar de baja al medico... \n");
            }
        }

        do
        {
            printf("\nDesea dar de baja a otro medico?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opcB);

        }while(opcB == 1 && opcB == 2);

    }while(opcB == 1);

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

        if(PQntuples(resultado)==0)
        {
            printf("El medico no existe...\n");
            opc == 1;
        }
        else
        {
            //todo va aqui
            do
            {
                printf("\n Elija el dato que desee modificar:");
                printf("\n 1.- nombre del medico\n 2.- Edad \n 3.- Apellido paterno \n 4.- Apellido materno \n 5.- Salir \n");
                printf ("\nOpcion: ");
                scanf ("%i", &opcMod);

                switch(opcMod)
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

                        sprintf(actualizar,"Update Medico set nombre_m = '%s' where cedula = '%s' ", nombre, cedula);
                        printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); //Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, actualizar);

                        if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
                        {
    	                    printf("\nEl Medico ha sido modificado exitosamente \n");
                        }else {
    	                    printf("\nError al modificar el medico \n");
                        }

                    break;

                    case 2:

                        setbuf(stdin, NULL);
                        printf("introduzca la edad a modificar del medico: ");
                        scanf("%i", &edad);
                        setbuf(stdin, NULL);

                        if(edad>=18)
                        {
                            sprintf(actualizar,"Update Medico set edad = '%i' where cedula = '%s' ", edad, cedula);

                            printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); //Mostrar instruccion SQL
                            printf("\n");
                            resultado = PQexec(bd, actualizar); //Ejecuta linea postgres
                            if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
                            {
    	                        printf("\nEl Medico ha sido modificado exitosamente \n");
                            }else
                            {
    	                        printf("\nError al modificar medico... \n");
                            }

                        }else
                        {
                            printf("El Medico no puede ser menor de edad...\n");
                            opcMod == 1; //ojito
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

                        sprintf(actualizar,"Update Medico set appat_m = '%s' where cedula = '%s' ", appat, cedula);
                        printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); //Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, actualizar);

                        if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
                        {
    	                    printf("\nEl Medico ha sido modificado exitosamente \n");
                        }else {
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

                        sprintf(actualizar,"Update Medico set apmat_m = '%s' where cedula = '%s' ", apmat, cedula);
                        printf("Instruccion SQL antes de ejecutarse: %s \n", actualizar); //Mostrar instruccion SQL
                        printf("\n");
                        resultado = PQexec(bd, actualizar);

                        if(PQresultStatus(resultado)== PGRES_COMMAND_OK)
                        {
    	                    printf("\nEl Medico ha sido modificado exitosamente \n");
                        }else {
    	                    printf("\nError al modificar el medico \n");
                        }
                    break;

                    case 5:
                        printf("\n Saliendo de las modificaciones del medico...\n");
                    break;

                    default:
                        printf("\n Digite una opcion correcta...\n");
                }//fin del switch

                do
                {
                    printf("\nDesea actualizar otro dato del cliente?:\n");
                    printf("1.- Si 2.-No\n");
                    scanf("%i", &opcMod);

                }while(opcMod==1 && opcMod==2);

            }while(opcMod == 1);
            
        }//Fin del menu de actualizar dato del medico

        do
        {
            printf("\nDesea modificar a otro medico?:\n");
            printf("1.- Si 2.-No\n");
            scanf("%i", &opc);

        }while(opc == 1 && opc == 2);

    }while(opc == 1);
    
}

void consultar_medico()
{
    char tab[50], cad[100];
    int i,j,fila,columna;    
    //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    sprintf(cad,"select * from Medico order by cedula");
    printf("Instruccion SQL antes de ejecutarse: %s \n",cad); //Mostrar instruccion SQL
    printf("\n");
    resultado = PQexec (bd, cad); //Ejecuta linea postgres

    fila = PQntuples(resultado); //filas de la tabla
    if (fila == 0)
    {
    	printf ("ATENCION: La tabla está vacía\n");      	
    }else
    {     	
       	columna = PQnfields(resultado); //Columnas de la tabla 
        printf ("---------------------------------------------------------------------------------------\n"); 
       	printf ("|     Cedula    |  Edad |  Nombre Medico |  Apellido Paterno  |  Apellido Materno  |\n");               	
       	for (i = 0; i < fila ; i++)
       	{
                printf ("------------------------------------------------------------------------------------\n"); 
              	for (j = 0; j < columna; j++)
              	{
                        
                    printf("|    %s\t",PQgetvalue(resultado,i,j)); //Resultado fila y columna de la consulta
		        }
		    printf("\n");
        }
    }

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
                                        Alta_Paciente();
                                        //Metodo
                                    break;

                                    case 2:
                                        //Metodo
                                    break;

                                    case 3:
                                        //Metodo
                                    break;

                                    case 4:
                                        Seleccionar_Paciente();
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
                                    case 1: //Metodo guardar
                                        GuardarCita();
                                    break;

                                    case 2: //Metodo eliminar
                                        EliminarCita();
                                    break;

                                    case 3: //Metodo editar
                                        ModificarCita();
                                    break;

                                    case 4: //Metodo consulta
                                        ConsultarCita();
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
                                printf("\n 1.- Alta consulta \n 2.- Baja consulta \n 3.- Modificar consulta \n 4.- Consultar consultas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCons);

                                switch(opcCons)
                                {
                                    case 1: //Metodo guardar
                                        
                                    break;

                                    case 2: //Metodo eliminar
                                        EliminarConsulta();
                                    break;

                                    case 3: //Metodo modificar
                                        
                                    break;

                                    case 4://Metodo consultar                                        
                                        ConsultarConsulta();
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
                                        //Metodo mostrar expediente
                                        mostrar_expediente();
                                    break;

                                    case 2:
                                        //Metodo borrar expediente

                                    break;

                                    case 3:
                                        printf("\n Saliendo de expedientes...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }//Fin del switch expediente

                            }while(opcExp!=3); //Fin while de expediente
                            
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
                                        consultar_medico();
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
                    printf("\n 1.- B) Paciente y medico con mas edad \n 2.- C) Promedio de edades de pacientes y medicos \n 3.- E) Numero de consultas al dia por medico \n 4.- Salir \n");
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
                            printf("\n Digite una opcion correcta...\n");

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
    int opcM, opcCM, opcPM, opcRM;
    int opcDiag, opcMedic, opcCrudMedico, opcCrudEspec, opcExp, opcConsulta, opcCruExp;

    do
    {
        printf("\nBienvenido al menu de medicos\n");
        printf("\n 1.- Catalogos \n 2.- procesos \n 3.- Reportes \n 4.- Salir \n");
        printf("Elija una opcion: ");
        scanf("%i", &opcM);

        switch(opcM)
        {
            case 1: //opcion catalogos medico
                do
                {
                    printf("\n Bienvenido a Catalogos de medico \n");
                    printf("\n 1.- Medico \n 2.- Diagnostico \n 3.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcCM);

                    switch(opcCM)
                    {
                        case 1: //Medico y especialidad

                            do 
                            { 
                                printf("\n-----Medicos-----\n");
                                printf("\n 1.- Medico \n 2.- Especialidad \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcMedic);

                                switch(opcMedic)
                                {
                                    case 1:
                                        //Crud tabla medico
                                        do
                                        {
                                            printf("\n-----Medico-----\n");
                                            printf("\n 1.- Alta medico \n 2.- Baja medico \n 3.- Modificar medico \n 4.- Consultar medicos \n 5.- Salir \n");
                                            printf("Elija una opcion: ");
                                            scanf("%i", &opcCrudMedico);

                                            switch(opcCrudMedico)
                                            {
                                                case 1:
                                                    //Metodo alta medico
                                                    alta_medico();
                                                break;

                                                case 2:
                                                    //Metodo baja medico
                                                    baja_medico();
                                                break;

                                                case 3:
                                                    //Metodo modificar medico
                                                    actualizar_medico();
                                                break;

                                                case 4:
                                                    //Metodo consulta medico
                                                    consultar_medico();
                                                break;

                                                case 5:
                                                    printf("\n --Saliendo de medico...\n");
                                                break;

                                                default:
                                                    printf("\n Digite una opcion corretca...\n");
                                            }

                                        }while(opcCrudMedico!=5);

                                    break;

                                    case 2:
                                        //Crud tabla especialidad
                                        do
                                        {
                                            printf("\n-----Especialidad de medicos-----\n");
                                            printf("\n 1.- Alta especialidad \n 2.- Baja especialidad \n 3.- Modificar especialidad \n 4.- Consultar especialidades \n 5.- Salir \n");
                                            printf("Elija una opcion: ");
                                            scanf("%i", &opcCrudEspec);

                                            switch(opcCrudEspec)
                                            {
                                                case 1:
                                                    //Metodo alta especialidad
                                                break;

                                                case 2:
                                                    //Metodo baja especialidad
                                                break;

                                                case 3:
                                                    //Metodo modificar especialidad
                                                break;

                                                case 4:
                                                    //Metodo consulta especialidad
                                                break;

                                                case 5:
                                                    printf("\n --Saliendo de especialidades...\n");
                                                break;

                                                default:
                                                    printf("\n Digite una opcion correcta...\n");
                                            }

                                        }while(opcCrudEspec!=5);

                                    break;

                                    case 3:
                                        printf("\n Saliendo de medicos...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion corretca...\n");
                                }

                            }while(opcMedic!=3); //Fin del while medicos 

                        break;

                        case 2: //Diagnostico
                            do
                            {
                                //Crud tabla diagnostico
                                printf("\n-----Diagnosticos-----\n");
                                printf("\n 1.- Alta diagnostico \n 2.- Baja diagnostico \n 3.- Modificar diagnostico \n 4.- Consultar diagnosticos \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcDiag);

                                switch(opcDiag)
                                {
                                    case 1:
                                        //Metodo alta diagnostico
                                    break;
                                    
                                    case 2:
                                        //Metodo baja diagnostico
                                    break;

                                    case 3:
                                        //Metodo modificar diagnostico
                                    break;

                                    case 4:
                                        //Metodo consultar diagnostico
                                    break;

                                    case 5:
                                        printf("\n --Saliendo de diagnostico...\n");
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }

                            }while(opcDiag!=5);

                        break;

                        case 3: //Salir
                            printf("\n Saliendo de catalogos de medicos...\n");
                        break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                    }

                }while(opcCM!=3); //Fin del while catalogos del medico
                
            break;

            case 2: //opcion procesos medico

                do
                {
                    printf("\n Bienvenido a procesos de medico \n");
                    printf("\n 1.- Paciente \n 2.- Cita \n 3.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcPM);

                    switch(opcPM)
                    {
                        case 1: //paciente

                            do
                            {
                                printf("\n -----Pacientes----- \n");
                                printf("\n 1.- Ver paciente \n 2.- expedientes \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcExp);

                                switch(opcExp)
                                {
                                    case 1:
                                        //Metodo ver paciente
                                    break;

                                    case 2:
                                        //Metodo ver expediente
                                        do
                                        {
                                            printf("\n----- Expedientes-----");
                                            printf("\n 1.- Alta expediente \n 2.- Modificar expediente \n 3.- Mostrar expediente \n 4.- Salir de expedientes \n");
                                            printf("Elija una opcion:");
                                            scanf("%i", &opcCruExp);

                                            switch(opcCruExp)
                                            {
                                                case 1:
                                                    //Metodo agregar expediente
                                                break;

                                                case 2:
                                                    //Metodo modificar expediente
                                                break;

                                                case 3:
                                                    //metodo mostrar expediente
                                                    mostrar_expediente();
                                                break;

                                                case 4:
                                                    printf("\n Saliendo de expedientes...\n");
                                                break;

                                                default:
                                                    printf("\n Seleccione una opcion valida...\n");
                                            }

                                        }while(opcCruExp!=4); //Fin while cru(d) expediente
                                        
                                    break;

                                    case 3:
                                        printf("\n --Saliendo de Pacientes...\n ");
                                    break;

                                    default:
                                        printf("\n Seleccione una opcion valida...\n");
                                }

                            }while(opcExp!=3); //Fin del while paciente proceso
                            
                        break;

                        case 2: //cita

                            do
                            {
                                printf("\n -----Citas----- \n");
                                printf("\n 1.- Ver citas \n 2.- Ver consultas \n 3.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcConsulta);

                                switch(opcConsulta)
                                {
                                    case 1: //Metodo ver citas
                                        ConsultarCita();
                                    break;

                                    case 2: //Metodo ver consultas
                                        ConsultarConsulta();
                                    break;

                                    case 3:
                                        printf("\n --Saliendo de Citas...\n ");
                                    break;

                                    default:
                                        printf("\n Seleccione una opcion valida...\n");
                                }

                            }while(opcConsulta!=3);

                        break;

                        case 3: //salir
                            printf("\n Saliendo de procesos de medicos...\n");
                        break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                    }

                } while(opcPM!=3); //Fin del while procesos del medico
                
            break;

            case 3://opcion reportes medico
                do
                {
                    printf("\n Bienvenido a reportes del medico \n");
                    printf("\n 1.- A) Lista de pacientes por medico \n 2.- D) Consultas de los pacientes por fecha \n 3.- E) Numero de consultas por dia por el medico \n 4.- Salir \n");
                    printf("Elija una opcion: ");
                    scanf("%i", &opcRM);

                    switch(opcRM)
                    {
                        case 1:
                            //Metodo A)
                        break;

                        case 2:
                            //Metodo D)
                        break;

                        case 3:
                            //Metodo E)
                        break;

                        case 4:
                            printf("\nSaliendo del menu reportes medico...\n");
                        break;

                        default:
                            printf("\n Seleccione una opcion valida...\n");
                    }

                }while(opcRM!=4); //Fin del while de reportes del medico
                
            break;

            case 4:
                printf("\n Saliendo del menu de medicos...\n");
            break;

            default:
                printf("\n Seleccione una opcion valida medico...\n");
        }

    }while(opcM!=4);//Fin del ciclo secretaria

}//Fin de menu medico

int menu_principal()
{
    int opcUsuario;
    char host[15] = "localhost";
    char puerto[5] = "5432";
    char database[15] = "hospital";
    char usuario[20];
    char password[20];

    do
    {
        printf("\nBienvenido al hospital:\n");
        printf("🅂 🄰 🄻  🅅 🄸 🅅 🄾  🅂 🄸  🄿 🅄 🄴 🄳 🄴 🅂\n");
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
	
                bd = PQsetdbLogin(host, puerto, NULL, NULL, database, usuario, password);

	            printf("\nProbando conexion con POSTGRESQL ...\n\n");

                if(PQstatus(bd) == CONNECTION_OK)
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
	
                bd = PQsetdbLogin(host, puerto, NULL, NULL, database, usuario, password);

	            printf("\nProbando conexion con POSTGRESQL ...\n\n");

                if(PQstatus(bd) == CONNECTION_OK)
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
}
//main
int main(int argc, char *argv[])
{
    MPI_Init(& argc ,& argv ) ;
    printf("\n\n");
    printf("\t  ██████╗░██╗███████╗███╗░░██╗██╗░░░██╗███████╗███╗░░██╗██╗██████╗░░█████╗░░\n");
    printf("\t  ██╔══██╗██║██╔════╝████╗░██║██║░░░██║██╔════╝████╗░██║██║██╔══██╗██╔══██╗\n");
    printf("\t  ██████╦╝██║█████╗░░██╔██╗██║╚██╗░██╔╝█████╗░░██╔██╗██║██║██║░░██║██║░░██║\n");
    printf("\t  ██╔══██╗██║██╔══╝░░██║╚████║░╚████╔╝░██╔══╝░░██║╚████║██║██║░░██║██║░░██║\n");
    printf("\t  ██████╦╝██║███████╗██║░╚███║░░╚██╔╝░░███████╗██║░╚███║██║██████╔╝╚█████╔╝\n");
    printf("\t  ╚═════╝░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚══════╝╚═╝░░╚══╝╚═╝╚═════╝░░╚════╝░\n\n");
    printf("\n\n");
    menu_principal();
    MPI_Finalize ;
    return 0;
}//Fin del Main