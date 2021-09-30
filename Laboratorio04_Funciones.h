/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Laboratorio04_Funciones.h
 * Author: jhenn
 *
 * Created on 30 de septiembre de 2021, 04:15 PM
 */

#ifndef LABORATORIO04_FUNCIONES_H
#define LABORATORIO04_FUNCIONES_H

#include <iostream>        
#include <fstream>
using namespace std;

void imprimirLinea(ofstream &, char, int);
void  cargarMedicos(char ** &codigoMed, char** &medicos, double * &tarifas);
char* leerCodMed(ifstream &archMed);
char * leerNombMed(ifstream & archMed);
double leerTarifaMed(ifstream &  archMed);
void reporteMedicos(char ** codigoMed,  char** medicos, double *tarifas);
void reporteDeIngresos(char ** codigoMed, char**medicos, double *tarifas) ;


void cargarPacientes(char *codMed, int *&codigoPac, char **&pacientes,
        double * &porcentajes, int *&veces);


int  buscarPaciente(int codPac, int buffCodPac[], int numPac);

void reporteDelMedico(char *codMed,char ** codigoMed, char** medicos,double * tarifas,
                        int * codigoPac, char **pacientes, double *porcentajes,int *veces, ofstream &archRep);

void liberarEspacios(int *codigoPac, char **pacientes,double * porcentajes, int *veces);

#endif /* LABORATORIO04_FUNCIONES_H */
