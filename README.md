# TP Final - Registro Automotor

Este proyecto consiste en un sistema de registro automotor desarrollado como trabajo práctico final. Permite la gestión de titulares, vehículos, cédulas, domicilios, y eventos del historial de cada vehículo.

![db-registro-automotor (1)](https://github.com/user-attachments/assets/4201f9b1-e367-4ba4-9f05-791e55e5defe)


## Documentación

Podés acceder al informe completo del proyecto en el siguiente enlace:

👉 [Ver informe en Google Docs](https://docs.google.com/document/d/1Z8EF9JKB7I55qxfOUtWaGTnqBExOlhGBCaDm_WjFv4c/edit?tab=t.is44njostnfh)

## Tecnologías utilizadas

- Lenguaje C
- Sistema de archivos (persistencia con `.txt`)
- Módulos separados (`main.c`, `menu.c`, `registro.c`, etc.)

## Funcionalidades principales

- Alta, baja y modificación de titulares y vehículos
- Asociación entre vehículos y titulares
- Registro de eventos (multas, transferencias, etc.)
- Reportes completos e informes listando datos interrelacionados

## Cómo compilar

gcc main.c menu.c registro.c automotor.c cedula.c titular.c domicilio.c historialevento.c -o registroApp.exe
