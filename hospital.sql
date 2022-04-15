
--creacion de la base
create database Hospital;

--cambiarse de bd de la por defecto(postgres)
\c hospital

--creacion de la tablas

create table Paciente
(
	num_paciente serial,
	nombre_p varchar NOT NULL,
	appat_p varchar NOT NULL,
	apmat_p varchar NOT NULL,
	edad_p integer NOT NULL,
	direccion varchar NOT NULL,
	CONSTRAINT Paciente_pkey PRIMARY KEY(num_paciente)
);

CREATE TABLE Expediente
(
	num_exp serial, 
	num_paciente integer not null,
	alergias varchar,
	constraint Expediente_pkey primary key(num_exp),
	constraint Expediente_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Cita
(
	id_cita serial,
	num_paciente integer not null,
	consultorio varchar not null,
	fecha_hora timestamp not null constraint fecha_invalida check (fecha_hora < now()),
	constraint Cita_pkey primary key(id_cita),
	constraint Cita_fkey foreign key(num_paciente) references Paciente(num_paciente)
);

create table Medico
(
	cedula varchar not null, 
	edad integer not null constraint edad_invalida check (edad <= 18), 
	nombre_m varchar not null, 
	appat_m varchar not null,
	apmat_m varchar not null,
	constraint Medico_pkey primary key(cedula),	
);


create table Especialidad
(
	cns serial,
	cedula varchar not null,
	especialidad varchar not null,
	constraint Especialidad_pkey primary key(cns, cedula),
	constraint Especialidad_fkey foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Consulta
(
	id_consulta serial,
	id_cita integer not null,
	cedula varchar not null,
	fecha_hora_c timestamp not null,
	consultorio_c varchar not null,
	constraint Consulta_pkey primary key(id_consulta),
	constraint Consulta_fkey_idCita foreign key(id_cita)
	references Cita(id_cita) match simple on update no action on delete cascade,
	constraint Consulta_fkey_cedula foreign key(cedula)
	references Medico(cedula) match simple on update no action on delete cascade
);

create table Diagnostico
(
	num_diagnostico serial,
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


--esta atabla no se si deba de ir, seria la relacion que tiene el paciete con el medico, ayudaria a identificar que paciente se atiende con que medico y que medico atiende a los diferentes pacientes
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
