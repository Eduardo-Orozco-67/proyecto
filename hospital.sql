--creacion de la base
create database Hospital;

--Conectarse a la base de datos
psql Hospital 

--cambiarse a la base datos
\c Hospital

create table Paciente
(
	num_paciente integer not NULL,
	nombre_p varchar NOT NULL,
	appat_p varchar NOT NULL,
	apmat_p varchar NOT NULL,
	edad_p integer NOT NULL,
	direccion varchar NOT NULL,
	CONSTRAINT Paciente_pkey PRIMARY KEY(num_paciente)
);

CREATE TABLE Expediente
(
	num_exp integer not NULL, 
	num_paciente integer not null,
	alergias varchar,
	constraint Expediente_pkey primary key(num_exp),
	constraint Expediente_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Cita
(
	id_cita integer not NULL,
	num_paciente integer not null,
	consultorio varchar not null,
	fecha date not null constraint fecha_invalida check (fecha > now()),
	hora time not null,
	estado varchar not null,
	constraint Cita_pkey primary key(id_cita),
	constraint Cita_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Medico
(
	cedula varchar not null, 
	edad integer not null constraint edad_invalida check (edad >= 25), 
	nombre_m varchar not null, 
	appat_m varchar not null,
	apmat_m varchar not null,
	constraint Medico_pkey primary key(cedula)
);


create table Especialidad
(
	cns integer not NULL,
	cedula varchar not null,
	especialidad varchar not null,
	constraint Especialidad_pkey primary key(cns, cedula),
	constraint Especialidad_fkey foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Consulta
(
	id_consulta integer not NULL,
	id_cita integer not null,
	cedula varchar not null,
	fecha_con date not null constraint fecha_invalida check (fecha_con > now()),
	hora_con time not null,
	consultorio_con varchar not null,
	constraint Consulta_pkey primary key(id_consulta),
	constraint Consulta_fkey_idCita foreign key(id_cita)
	references Cita(id_cita) match simple on update no action on delete cascade,
	constraint Consulta_fkey_cedula foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Diagnostico
(
	num_diagnostico integer not NULL,
	num_exp integer not null, 
	cedula varchar not null,
	medicinas varchar not null,
	valoracion_medica varchar not null,
	constraint Diagnostico_pkey primary key(num_diagnostico),
	constraint Diagnostico_fkey_numExp foreign key (num_exp)
	references Expediente(num_exp) match simple on update no action on delete cascade,
	constraint Diagnostico_fkey_cedula foreign key (cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

--Crear tabla de la relacion entre paciente y medico
create table Detalle_Paciente_Medico
(
	cedula varchar not null,
	num_paciente integer not null,
	constraint Detalle_Paciente_Medico_pkey primary key(cedula, num_paciente),
	constraint Detalle_Medico_fkey foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade,
	constraint Detalle_Paciente_fkey foreign key(num_paciente)
	references Paciente(num_paciente) match simple on update no action on delete cascade
);

--crear secuencia  siga la numeracion para crear correctamente 1, 2 ,3

--1
create sequence paciente_num_paciente;
create sequence Expediente_num_expediente;
create sequence Cita_id_cita;
create sequence Especialidad_cns;
create sequence Consulta_id_consulta;
create sequence Diagnostico_num_diagnostico;

--2
ALTER TABLE Diagnostico
ALTER COLUMN num_diagnostico
SET DEFAULT NEXTVAL('Diagnostico_num_diagnostico');

ALTER TABLE Consulta
ALTER COLUMN id_consulta
SET DEFAULT NEXTVAL('Consulta_id_consulta');

ALTER TABLE especialidad 
ALTER COLUMN cns
SET DEFAULT NEXTVAL('Especialidad_cns');

ALTER TABLE Cita 
ALTER COLUMN id_cita
SET DEFAULT NEXTVAL('Cita_id_cita');

ALTER TABLE Expediente 
ALTER COLUMN num_exp
SET DEFAULT NEXTVAL('Expediente_num_expediente');

ALTER TABLE paciente 
ALTER COLUMN num_paciente
SET DEFAULT NEXTVAL('paciente_num_paciente');

--3
UPDATE Especialidad
set cns = NEXTVAL ('Especialidad_cns');

UPDATE Expediente
set num_exp = NEXTVAL ('Expediente_num_expediente');

UPDATE cita
set id_cita = NEXTVAL ('Cita_id_cita');

UPDATE paciente
set num_paciente = NEXTVAL ('paciente_num_paciente');

UPDATE consulta
set id_consulta = NEXTVAL ('Consulta_id_consulta');

UPDATE Diagnostico
set num_diagnostico = NEXTVAL ('Diagnostico_num_diagnostico');

--Crear grupos de usuarios
create role recepcion WITH NOLOGIN;
create role medicos WITH NOLOGIN;
create role administrador WITH NOLOGIN;

GRANT USAGE ON SCHEMA public TO medicos;
GRANT USAGE ON SCHEMA public TO recepcion;
GRANT USAGE ON SCHEMA public TO administrador;

--Creacion de usuarios para cada grupo
--Grupo de recepcion
create user noe_orozco with password 'recepcion';
create user jeannette_guillen with password 'recepcion';
--Grupo de medicos
create user samuel_losada with password 'medico' ;
create user eduardo_guzman with password 'medico' ;

--Grupo de administrador
create user emilia_hernandez with password 'admin';

GRANT medicos TO eduardo_guzman;
GRANT medicos TO samuel_losada;
GRANT recepcion TO noe_orozco;
GRANT recepcion TO jeannette_guillen;
GRANT administrador TO emilia_hernandez;

--Otorgando privilegios de las tablas para el grupo de recepcion
--Tablas en las que se otorgan todos los permisos
GRANT all ON table Paciente to recepcion;
GRANT all ON table Cita to recepcion;
GRANT all ON table Consulta to recepcion;
--Tablas a las que se le da permiso para seleccionar y eliminar
GRANT select, delete ON table Expediente to recepcion;
--Tablas con permisos solo para seleccionar
GRANT select ON table Medico to recepcion;
GRANT select ON table Especialidad to recepcion;
GRANT select ON table Diagnostico to recepcion;

--Otorgando privilegios de las tablas para el grupo de medicos
--Tablas en las que se otorgan todos los permisos
GRANT all ON table Medico to medicos;
GRANT all ON table Especialidad to medicos;
GRANT all ON table Diagnostico to medicos;
--Tablas a las que se le da permiso para seleccionar, eliminar y actualizar
<<<<<<< HEAD
GRANT select, insert, update ON table Expediente to group medicos;
=======
GRANT select, insert, update ON table Expediente to medicos;
>>>>>>> origin/master
--Tablas con permisos solo para seleccionar
GRANT select ON table Paciente to medicos;
GRANT select ON table Cita to medicos;
GRANT select ON table Consulta to medicos; 

--Otorgando permisos de las tablas para el grupo del administrador
GRANT all ON table Paciente to administrador;
GRANT all ON table Expediente to administrador;
GRANT all ON table Cita to administrador;
GRANT all ON table Medico to administrador;
GRANT all ON table Especialidad to administrador;
GRANT all ON table Consulta to administrador;
GRANT all ON table Diagnostico to administrador;
GRANT all ON table Detalle_Paciente_Medico to administrador; 

GRANT ALL on sequence expediente_num_expediente to medicos;
GRANT ALL on sequence paciente_num_paciente to medicos;
GRANT ALL on sequence Expediente_num_expediente to medicos;
GRANT ALL on sequence Cita_id_cita to medicos;
GRANT ALL on sequence Especialidad_cns to medicos;
GRANT ALL on sequence Consulta_id_consulta to medicos;
GRANT ALL on sequence Diagnostico_num_diagnostico to medicos;

GRANT ALL on sequence expediente_num_expediente to recepcion;
GRANT ALL on sequence paciente_num_paciente to recepcion;
GRANT ALL on sequence Expediente_num_expediente to recepcion;
GRANT ALL on sequence Cita_id_cita to recepcion;
GRANT ALL on sequence Especialidad_cns to recepcion;
GRANT ALL on sequence Consulta_id_consulta to recepcion;
GRANT ALL on sequence Diagnostico_num_diagnostico to recepcion;

GRANT ALL on sequence expediente_num_expediente to administrador;
GRANT ALL on sequence paciente_num_paciente to administrador;
GRANT ALL on sequence Expediente_num_expediente to administrador;
GRANT ALL on sequence Cita_id_cita to administrador;
GRANT ALL on sequence Especialidad_cns to administrador;
GRANT ALL on sequence Consulta_id_consulta to administrador;
GRANT ALL on sequence Diagnostico_num_diagnostico to administrador;

GRANT ALL on procedure AgendarCita to administrador;
GRANT ALL on procedure AgendarCita to medicos;
GRANT ALL on procedure AgendarCita to recepcion;

GRANT ALL on procedure GuardarDiagnostico to administrador;
GRANT ALL on procedure GuardarDiagnostico to medicos;
GRANT ALL on procedure GuardarDiagnostico to recepcion;