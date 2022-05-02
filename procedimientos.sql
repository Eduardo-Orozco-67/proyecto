--Procedimiento almacenado para hospital

-- un paciente no puede tener mas de dos citas agendadas activas 

--Modificar la tabla de cita
drop table cita cascade;

create table Cita
(
	id_cita integer not NULL,
	num_paciente integer not null,
	consultorio varchar not null,
	fecha date not null constraint fecha_invalida check (fecha > now()),
	hora time not null,
	estado varchar not null, --activa, cancelada
	constraint Cita_pkey primary key(id_cita),
	constraint Cita_fkey foreign key(num_paciente) references Paciente(num_paciente)
);
--NO DEJA INSERTAR PORQUE EVALUA LA FECHA 
Call AgendarCita (1, 1, '9', '28-04-2022', '13:00:00', NULL);

--DATO CON LA FECHA CORRECTA y el estado activo
--Call AgendarCita (1, 1, '9', '30-04-2022', '13:00:00', 'activa', NULL);

--dato con la fecha correcta pero con otro estado
Call AgendarCita (1, 1, '9', '28-04-2022', '13:00:00', 'cancelada', NULL);

Call AgendarCita (1, 1, '9', '30-04-2022', '13:00:00', NULL);

Call AgendarCita (1, 1, '9', '30-04-2022', '13:00:00', NULL);

Call AgendarCita (1, 1, '10', '02-05-2022', '15:00:00', NULL);
Call AgendarCita (2, 1, '10', '10-05-2022', '17:00:00', NULL);

drop procedure AgendarCITA;

DROP PROCEDURE IF Exists AgendarCita (IN vidcita INTEGER, IN vpaciente INTEGER, IN vcon VARCHAR, IN vfecha varchar, IN vhora varchar, IN vestado VARCHAR, INOUT pRes INTEGER);

drop procedure AgendarCita;
CREATE PROCEDURE AgendarCita (IN vidcita INTEGER, IN vpaciente INTEGER, IN vcon VARCHAR, IN vfecha DATE, IN vhora TIME, INOUT pRes VARCHAR) AS $$
	DECLARE 
		vidcita alias for $1;
		vpaciente alias for $2;
		vcon alias for $3;
		vfecha alias for $4;
		vhora alias for $5;
		vestado alias for $6;
		vreg record;
		vnuevo varchar;
		vban varchar;
	BEGIN
		-- Selecciona el paciente
		Select into vreg * from Paciente where num_paciente = vpaciente for update;
		--Entra si el paciente existe
		IF FOUND THEN
			-- Si el paciente existe buscar la cita 
			Select into vreg * from cita where id_cita = vidcita for update;
			IF FOUND THEN
                vban:= 'Error esta cita ya ha sido agendada';
				Rollback;
				--Entra si no encuentra la cita 
			ELSE
                IF vfecha > now() THEN
                    --buscar una cita con ese id y que este activa 
                    select into vreg * from cita where num_paciente = vpaciente and estado = 'activo' for update;
                    IF FOUND THEN  
                        vban:= 'Error ya se ha agendado una cita y esta activa';
		                Rollback;
                    ELSE
                        --Realiza la insercion de la cita  
                        vnuevo := 'activo';      
                        Insert into Cita values (vidcita, vpaciente, vcon, vfecha, vhora, vnuevo);					
                        vban := '¡La cita ha sido agendada con exito!';
                        Commit;
                    END IF;
                    pRes := vban;
                ELSE
                    vban:= 'Error la fecha es incorrecta';
					Rollback;                        
                END IF;
                pRes := vban;
			END IF;
            pRes := vban;
		END IF;
			pRes := vban;	
	END;
	$$ LANGUAGE plpgsql;

-- PL para que cuando se guarde un diagnostico la cita se ponga como realizada
--Modificar la tabla de expediente 
drop table diagnostico cascade ;
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

--modificar la consulta

--Agregar expdiente -- NOTA es tabla modificada por error :(
insert into Expediente values (1, 1, 'Camaron');
insert into consulta (id_cita, cedula, fecha_con, hora_con, consultorio_con) values(2, 'CJT45', '05-05-2022', '13:00:00', 'las lomas'); 



Call GuardarExpediente (1, 1, 'CJT45', 'paracetamol', 'infeccion', NULL); 

drop procedure GuardarExpediente;
CREATE PROCEDURE GuardarExpediente (IN vdiafn INTEGER, IN vexped INTEGER, IN vcedula VARCHAR, IN vmedicinas VARCHAR, IN vvaloracion VARCHAR, INOUT pRes VARCHAR) AS $$
	DECLARE  
		vdiagn alias for $1;
		vexped alias for $2;
		vcedula alias for $3;
		vmedicinas alias for $4;
		vvaloracion alias for $5;
		vreg record;
		vnuevo varchar;
		vban varchar;
	BEGIN
		-- Selecciona el expediente, si este existe entonces significa que existe un paciente
		Select into vreg * from Expediente where num_exp = vexped for update;
		--Entra si el paciente existe
		IF FOUND THEN
			-- Buscar que el paciente tenga una cita
			Select into vreg * from Cita where num_paciente = vreg.num_paciente and estado = 'activo' for update;
			--Entra si el paciente tiene una cita
			IF FOUND THEN
				-- Valida si tiene una consulta 
				Select into vreg * from Consulta where id_cita = vreg.id_cita for update; 
				--Entra si tiene consulta
				if FOUND THEN
					--Insertar el dato en la tabla diagnostico
					Insert into Diagnostico values (vdiagn, vexped, vcedula, vmedicinas, vvaloracion);
					--Actualizar el estado de la consulta a realizada
					Update Cita set estado = 'realizada' where id_cita = vreg.id_cita;
					vban:= '¡El diagnostico ha sido guardado!';
                    Commit;
				ELSE
					vban:= 'Error el paciente no cuenta con consulta';
					Rollback;
				END IF;
				pRes := vban;
			ELSE
				vban:= 'Error el paciente no cuenta con cita activa';
				Rollback;
			END IF;
				pRes := vban;
		ELSE 
			vban:= 'Error el paciente no ha sido registrado';
			Rollback;
		END IF;
			pRes := vban;

	END;
	$$ LANGUAGE plpgsql;