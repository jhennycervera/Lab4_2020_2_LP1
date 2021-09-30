/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 30 de septiembre de 2021, 04:11 PM
 */


#include "Laboratorio04_Funciones.h"

int main(int argc, char** argv) {
    char **codigoMed, **medicos;
    double *tarifas;
    
    cargarMedicos(codigoMed, medicos, tarifas);
    reporteMedicos(codigoMed, medicos, tarifas);
    reporteDeIngresos(codigoMed, medicos, tarifas);
    
    return 0;
}