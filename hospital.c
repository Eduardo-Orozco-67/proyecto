
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
// gcc -o crud hospital.c -I /usr/include/postgresql/ -lpq
// ./crud

/*conectaar con postgres 
--sudo -i -u postgres
--psql
*/

PGconn *bd; 
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

//Funciones para el catalago de CITA -----------------------------------------------------------------------------------------
void GuardarCita()
{
    int num_paciente, resp;
    char consultorio[10], fecha [20], hora[20], nombre[20], appat[20], apmat[20], buspac[200], alta[200];   
    do{
        //Buscar el cliente por nombre completo
        printf ("\n===============");
    	printf("|AGENDAR UNA CITA|");
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
   	        printf("Ingrese fecha de la cita: ");
   	        scanf ("%s", fecha);
    	    setbuf(stdin, NULL); //Limpiar el buffer
   	        printf("Ingrese hora de la cita: ");
   	        scanf ("%s", hora);
    	    setbuf(stdin, NULL); //Limpiar el buffer

            //NOTA: AGREGAR CONDICIONAL DE FECHA ************************************************* OJO
            


            //Para las sentencias se usa sprintf y en automatico se declara la variable dentro del parentesis para almacenarla
    	    sprintf(alta,"insert into Cita (num_paciente, consultorio, fecha, hora) values (%i, '%s', '%s', '%s');", num_paciente, consultorio, fecha, hora);
    
    	    printf("\nInstruccion SQL antes de ejecutarse: %s \n", alta); //Mostrar instruccion SQL
    	    printf("\n");
    	    resultado = PQexec(bd, alta); //Ejecuta linea postgres  
    	    printf("La cita ha sido agendada\n");
      
        //fin del else del if PQntuples donde se busca el paciente 
        }
        else
        {
            printf ("\nATENCION: El el paciente no ha sido registrado \n");         
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
/*	id_consulta integer not NULL GENERATED ALWAYS AS IDENTITY, este no
	id_cita integer not null,
	cedula varchar not null,
	fecha_con date not null constraint fecha_invalida check (fecha_con > now()),
	hora_con time not null,
	consultorio_con varchar*/

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

//Metodos de los menus---------------------------------------------------------------------------
void MenuSecretaria()
{
    //variables
    int opcS, opcC, opcP, opcR;
    int opcPac, opcCita, opcCons, opcExp;

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
                                        //Metodo guardar
                                        GuardarCita();
                                    break;

                                    case 2:
                                        //Metodo eliminar
                                        EliminarCita();
                                    break;

                                    case 3:
                                        //Metodo editar

                                    break;

                                    case 4:
                                        //Metodo consulta
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
                                printf("\n 1.- Alta consulta \n 2.- Baja consulta \n 3.- Modificar consulta \n 4.- Consultar cconsultas \n 5.- Salir \n");
                                printf("Elija una opcion: ");
                                scanf("%i", &opcCons);

                                switch(opcCons)
                                {
                                    case 1:
                                        //Metodo guardar
                                    break;

                                    case 2:
                                        //Metodo eliminar
                                        EliminarConsulta();
                                    break;

                                    case 3:
                                        //Metodo modificar
                                    break;

                                    case 4:
                                        //Metodo consultar
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
                                    break;

                                    case 2:
                                    break;

                                    case 3:
                                    break;

                                    default:
                                        printf("\n Digite una opcion correcta...\n");
                                }//Fin del switch expediente

                            }while(opcExp != 3); //Fin while de expediente
                            
                        break;

                        case 2:
                        break;

                        case 3:
                        break;
                        
                        case 4:
                        break;

                        default:
                            printf("\n Digite una opcion corretca...\n");

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
                        break;

                        case 2:
                        break;

                        case 3:
                        break;

                        case 4:
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
    char database[20] = "hospital";
    char usuario[30];
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

}//Fin del Main
//