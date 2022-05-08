--Procedimiento almacenado para hospital

-- PL para que cuando se guarde una cita
-- un paciente no puede tener mas de dos citas agendadas activas 
drop procedure AgendarCITA;

DROP PROCEDURE IF Exists AgendarCita (IN vpaciente INTEGER, IN vcon VARCHAR, IN vfecha varchar, IN vhora varchar, IN vestado VARCHAR, INOUT pRes INTEGER);

drop procedure AgendarCita;

CREATE PROCEDURE AgendarCita ( IN vpaciente INTEGER, IN vcon VARCHAR, IN vfecha DATE, IN vhora TIME, INOUT pRes INTEGER) AS $$
	DECLARE 
		vpaciente alias for $1;
		vcon alias for $2;
		vfecha alias for $3;
		vhora alias for $4;
		vestado alias for $5;
		vreg record;
		vnuevo varchar;
		vban integer;
	BEGIN
		-- Selecciona el paciente
		Select into vreg * from Paciente where num_paciente = vpaciente for update;
		--Entra si el paciente existe
		IF FOUND THEN
			-- Si el paciente existe buscar la cita 
                IF vfecha > now() THEN
                    --buscar una cita con ese id y que este activa 
                    select into vreg * from cita where num_paciente = vpaciente and estado = 'activo' for update;
                    IF FOUND THEN  
                        vban:= 0;
                        Rollback;
                    ELSE
                        --Realiza la insercion de la cita   
                        vnuevo := 'activo';      
                        Insert into Cita (num_paciente,consultorio,fecha,hora,estado) values ( vpaciente, vcon, vfecha, vhora, vnuevo);					
                        vban := 1; 
                        Commit;
                    END IF;
                    pRes := vban;
                ELSE
                    vban:= 0;
					Rollback;                        
                END IF;
                pRes := vban;
		END IF;
			pRes := vban;	
	END;
	$$ LANGUAGE plpgsql;

Call AgendarCita (1, '10', '10-05-2022', '17:00:00', NULL);

-- PL para que cuando se guarde un diagnostico la cita se ponga como realizada

--Agregar expdiente --
insert into Expediente values (1, 1, 'Camaron');
insert into consulta (id_cita, cedula, fecha_con, hora_con, consultorio_con) values(2, 'CJT45', '05-05-2022', '13:00:00', 'las lomas'); 

drop procedure GuardarDiagnostico;

CREATE PROCEDURE GuardarDiagnostico (IN vexped INTEGER, IN vcedula VARCHAR, IN vmedicinas VARCHAR, IN vvaloracion VARCHAR, INOUT pRes VARCHAR) AS $$
	DECLARE  
		vexped alias for $1;
		vcedula alias for $2;
		vmedicinas alias for $3;
		vvaloracion alias for $4;
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
					Insert into Diagnostico(num_exp, cedula, medicinas, valoracion_medica) values (vexped, vcedula, vmedicinas, vvaloracion);
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

call GuardarDiagnostico (1, 'as22', 'amoxicilina','infeccion en la pierna por herida', NULL);