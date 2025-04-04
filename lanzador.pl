#!/usr/bin/perl

#**************************************************************
#Pontificia Universidad Javeriana
#Facultad de Ingeniería Carrera de Ingeniería de Sistemas
#Materia: Sistemas Operativos
#Autor: Jair Santiago Vargas Saenz
#Fichero: Lanzador de procesos por lotes
#Descripción:
#Automatización de ejecuciones oara obtención de 30 resultados
#de ejecuciones de los benchmarks de distintos sabores con el
#proposito de hacer experimentos de caracter cientifico
#(fiabilidad, precisión, etc).
#**************************************************************/




#!/usr/bin/perl
$Path = `pwd`;
chomp($Path);
@Nombre_Ejecutable = ("matriz");

@Size_Matriz = (500, 1000, 2000);

@Num_Hilos = (1, 2);

$Repeticiones = 1;

# Compilar con Makefile antes de ejecutar
system("make");

foreach $Nombre_Ejecutable (@Nombre_Ejecutable) {
    foreach $size (@Size_Matriz) {
        foreach $hilo (@Num_Hilos) {

            $file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

            for ($i = 0; $i < $Repeticiones; $i++) {

                system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

                printf("$Path/$Nombre_Ejecutable $size $hilo \n");
            }

            close($file);

            $p = $p + 1;
        }
    }
}

