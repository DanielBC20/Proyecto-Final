CREATE DATABASE pase_de_abordaje;
USE pase_de_abordaje;

CREATE TABLE passengers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    apellido VARCHAR(100) NOT NULL,
    correo VARCHAR(100) NOT NULL,
    telefono VARCHAR(15) NOT NULL
);

CREATE TABLE flights (
    id INT AUTO_INCREMENT PRIMARY KEY,
    numero_vuelo VARCHAR(10) NOT NULL,
    origen VARCHAR(100) NOT NULL,
    destino VARCHAR(100) NOT NULL,
    fecha_hora_salida DATETIME NOT NULL,
    fecha_hora_llegada DATETIME NOT NULL
);

CREATE TABLE boarding_passes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    pasajero_id INT NOT NULL,
    vuelo_id INT NOT NULL,
    numero_asiento VARCHAR(5) NOT NULL,
    puerta_abordaje VARCHAR(10) NOT NULL,
    fecha_emision DATETIME NOT NULL,
    FOREIGN KEY (pasajero_id) REFERENCES passengers(id),
    FOREIGN KEY (vuelo_id) REFERENCES flights(id)
);

INSERT INTO passengers (nombre, apellido, correo, telefono)
VALUES ('Carlos', 'Breganza', 'carlosbregnza32@mail.com', '51286124'),
       ('Daniel', 'Carrera', 'Daniecarrera22@gmail.com', '54532124'),
       ('Karla', 'Gomez', 'Elkarla42@gmail.com', '51282344');

INSERT INTO flights (numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada)
VALUES ('3455', 'New York', 'Los Angeles', '2024-06-01 08:00:00', '2024-06-01 11:00:00'),
       ('4545', 'Petén', 'Madrid', '2024-06-01 07:00:00', '2024-06-01 19:00:00'),
       ('9800', 'Monterrey', 'San francisco', '2024-07-01 09:00:00', '2024-07-01 14:00:00');


INSERT INTO boarding_passes (pasajero_id, vuelo_id, numero_asiento, puerta_abordaje, fecha_emision)
VALUES (1, 1, '12A', 'G5', '2024-06-01 07:30:00'),
       (2, 2, '14B', 'G7', '2024-06-01 08:30:00');
       
SELECT * FROM passengers;
SELECT * FROM flights;
SELECT * FROM boarding_passes;


       


       
       
     



