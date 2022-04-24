
--creacion de la base
create database Hospital;

--Conectarse a la base de datos
\c hospital

--creacion de la tablas
create table Paciente
(
	num_paciente integer not NULL GENERATED ALWAYS AS IDENTITY,
	nombre_p varchar NOT NULL,
	appat_p varchar NOT NULL,
	apmat_p varchar NOT NULL,
	edad_p integer NOT NULL,
	direccion varchar NOT NULL,
	CONSTRAINT Paciente_pkey PRIMARY KEY(num_paciente)
);

CREATE TABLE Expediente
(
	num_exp integer not NULL GENERATED ALWAYS AS IDENTITY, 
	num_paciente integer not null,
	alergias varchar,
	constraint Expediente_pkey primary key(num_exp),
	constraint Expediente_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Cita
(
	id_cita integer not NULL GENERATED ALWAYS AS IDENTITY,
	num_paciente integer not null,
	consultorio varchar not null,
	fecha_hora_con TIMESTAMP not null constraint fecha_invalida check (fecha_hora_con < now()),
	constraint Cita_pkey primary key(id_cita),
	constraint Cita_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Medico
(
	cedula varchar not null, 
	edad integer not null constraint edad_invalida check (edad >= 18), 
	nombre_m varchar not null, 
	appat_m varchar not null,
	apmat_m varchar not null,
	constraint Medico_pkey primary key(cedula)
);


create table Especialidad
(
	cns integer not NULL GENERATED ALWAYS AS IDENTITY,
	cedula varchar not null,
	especialidad varchar not null,
	constraint Especialidad_pkey primary key(cns, cedula),
	constraint Especialidad_fkey foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Consulta
(
	id_consulta integer not NULL GENERATED ALWAYS AS IDENTITY,
	id_cita integer not null,
	cedula varchar not null,
	fecha_hora_con TIMESTAMP not null,
	consultorio_con varchar not null,
	constraint Consulta_pkey primary key(id_consulta),
	constraint Consulta_fkey_idCita foreign key(id_cita)
	references Cita(id_cita) match simple on update no action on delete cascade,
	constraint Consulta_fkey_cedula foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Diagnostico
(
	num_diagnostico integer not NULL GENERATED ALWAYS AS IDENTITY,
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

--Crear grupos de usuarios
create group recepcion;
create group medicos;
create group administrador;

--Creacion de usuarios para cada grupo
--Grupo de recepcion
create user noe_orozco with password 'recepcion' in group recepcion;
create user jeannette_guillen with password 'recepcion' in group recepcion;
--Grupo de medicos
create user samuel_losada with password 'medico' in group medicos;
create user eduardo_guzman with password 'medico' in group medicos;
--Grupo de administrador
create user emilia_hernandez with password 'admin' in group administrador;

--Otorgando privilegios de las tablas para el grupo de recepcion
--Tablas en las que se otorgan todos los permisos
GRANT all ON table Paciente to group recepcion;
GRANT all ON table Cita to group recepcion;
GRANT all ON table Consulta to group recepcion;
--Tablas a las que se le da permiso para seleccionar y eliminar
GRANT select, delete ON table Expediente to group recepcion;
--Tablas con permisos solo para seleccionar
GRANT select ON table Medico to group recepcion;
GRANT select ON table Especialidad to group recepcion;
GRANT select ON table Diagnostico to group recepcion;

--Otorgando privilegios de las tablas para el grupo de medicos
--Tablas en las que se otorgan todos los permisos
GRANT all ON table Medico to group medicos;
GRANT all ON table Especialidad to group medicos;
GRANT all ON table Diagnostico to group medicos;
--Tablas a las que se le da permiso para seleccionar, eliminar y actualizar
GRANT select, delete, update ON table Expediente to group medicos;
--Tablas con permisos solo para seleccionar
GRANT select ON table Paciente to group medicos;
GRANT select ON table Cita to group medicos;
GRANT select ON table Consulta to group medicos; 

--Otorgando permisos de las tablas para el grupo del administrador
GRANT all ON table Paciente to group administrador;
GRANT all ON table Expediente to group administrador;
GRANT all ON table Cita to group administrador;
GRANT all ON table Medico to group administrador;
GRANT all ON table Especialidad to group administrador;
GRANT all ON table Consulta to group administrador;
GRANT all ON table Diagnostico to group administrador;
GRANT all ON table Detalle_Paciente_Medico to group administrador; 
