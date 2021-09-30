/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/* 
 * File:   Laboratorio04_Funciones.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 30 de septiembre de 2021, 04:15 PM
 */

#include "Laboratorio04_Funciones.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX 500

void imprimirLinea(ofstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void cargarMedicos(char ** &codigoMed, char** &medicos, double * &tarifas) {

    ifstream archMed("RelacionMedicos.csv", ios::in);

    if (!archMed) {
        cout << "No se puede abrir el archivo RelacionMedicos.csv" << endl;
        exit(1);
    }

    int numMed = 0;
    char *buffCod[MAX], *buffNomb[MAX];
    double bufftarifa[MAX];

    while (1) {
        buffCod[numMed] = leerCodMed(archMed);
        if (buffCod[numMed] == nullptr) break; //ERROR: falto colocar el [numMed] en buffCod
        buffNomb[numMed] = leerNombMed(archMed);
        bufftarifa[numMed] = leerTarifaMed(archMed);
        numMed++;
    }
    codigoMed = new char*[numMed + 1];
    medicos = new char *[numMed];
    tarifas = new double[numMed];

    for (int i = 0; i < numMed; i++) {
        codigoMed[i] = buffCod[i];
        medicos[i] = buffNomb[i];
        tarifas[i] = bufftarifa[i];
    }
    codigoMed[numMed] = nullptr;

}

char* leerCodMed(ifstream &archMed) {

    char nomb[7], *ptrnombr;
    archMed.getline(nomb, 7, ',');
    if (archMed.eof()) return nullptr;

    ptrnombr = new char[strlen(nomb) + 1];
    strcpy(ptrnombr, nomb);
    return ptrnombr;
}

char * leerNombMed(ifstream & archMed) {

    char nombr[MAX], *ptrNomb;
    archMed.getline(nombr, MAX, ',');
    ptrNomb = new char[ strlen(nombr) + 1];
    strcpy(ptrNomb, nombr);
    return ptrNomb;

}

double leerTarifaMed(ifstream & archMed) {
    double tarifa;
    char aux[MAX];
    archMed.getline(aux, MAX, ',');
    archMed>>tarifa;
    archMed.get(); //\n
    return tarifa;

}

void reporteMedicos(char ** codigoMed, char** medicos, double *tarifas) {

    ofstream archRep("RepMedicos.txt", ios::out);
    if (!archRep) {
        cout << "No se pudo abrir RepMedicos.txt" << endl;
        exit(1);
    }
    archRep.precision(2);
    archRep << fixed;
    archRep << left << setw(15) << "CODIGO" << setw(60) << "NOMBRE" << "TARIFA" << endl;
    for (int i = 0; codigoMed[i] != nullptr; i++) {
        archRep << setw(15) << codigoMed[i] << setw(60) << medicos[i] << tarifas[i] << endl;
    }

}

void reporteDeIngresos(char ** codigoMed, char**medicos, double *tarifas) {

    ifstream archMed("Medicos.csv", ios::in);
    if (!archMed) {
        cout << "No se puede abrir el archivo Conductores.csv" << endl;
        exit(1);
    }
    
    ofstream archRep("RepMedicos.txt", ios:: out);
    if(!archRep){
        cout<<"No se pudo abrir RepConductores.txt"<<endl;
 	exit(1);
    }
    int *codigoPac, *veces;
    char **pacientes, codMed[7]; //**
    double *porcentajes;
    
    // Iteración por cada médico 
    while (1) {
        archMed>>codMed;
        if (archMed.eof()) break;
        cargarPacientes(codMed, codigoPac, pacientes, porcentajes, veces);
        reporteDelMedico(codMed, codigoMed, medicos, tarifas, codigoPac, pacientes, porcentajes, veces, archRep);
        liberarEspacios(codigoPac, pacientes, porcentajes, veces);

    }
}


void cargarPacientes(char *codMed, int *&codigoPac, char **&pacientes,
        double * &porcentajes, int *&veces) {
    ifstream archPac("Pacientes-Atencion.csv", ios::in);
    if (!archPac) {
        cout << "No se puede abrir el archivo Pacientes-Atencio.csv" << endl;
        exit(1);
    }
    char auxFech[15], car, nombre[200], codMedicoArch[7],  *buffPac[MAX];
    double porc, buffPorc[MAX];
    int buffVeces[MAX]={0}, buffCodPac[MAX], numPac=0, codPac;
    
    while(1){
        archPac.getline(auxFech, 15, ',');
        if(archPac.eof()) break;      
        while(1){ //pacientes de esa fecha
            archPac>>car;
            archPac.get(); //coma
            archPac>>codPac;
            archPac.get(); //coma
            archPac.getline(nombre, 200, ',');
            archPac>>porc;
            archPac.get(); //coma
            archPac.get(codMedicoArch, 7, ','); //se pone get para dejar el utimo caracter en el buffer ; o /n ..> siempre se para cuando lee 6 caracteres            
            //procesarDatos      
            if(car == 'A'  && strcmp(codMed, codMedicoArch) == 0){ //llenar los buff
                int pos= buscarPaciente(codPac,buffCodPac,numPac);
                if(pos!=numPac){ //encontro al paciente
                    buffVeces[pos]++;                   }
                else{ //paciente nuevo  
                    buffCodPac[numPac]= codPac;
                    buffPac[numPac]= new char[strlen(nombre) + 1];
                    strcpy( buffPac[numPac], nombre);
                    buffPorc[numPac]= porc;     
                    buffVeces[numPac]=1;
                    numPac++;
                }               
            }
            if( archPac.get() == '\n') break; //salida 
        }
    }

    codigoPac= new int [numPac + 1];
    pacientes= new char*[numPac];
    porcentajes= new double[numPac];
    veces= new int[numPac];
    
    for(int i=0; i<numPac;i++){
        codigoPac[i]= buffCodPac[i];
        pacientes[i]= buffPac[i];
        porcentajes[i]= buffPorc[i];
        veces[i]= buffVeces[i];
    }
    codigoPac[numPac]= -1; //terminador
}


int  buscarPaciente(int codPac, int buffCodPac[], int numPac){
    
    for(int i=0; i<numPac; i++){
        if(buffCodPac[i] == codPac) return i;
    }
    return numPac;
}


void reporteDelMedico(char *codMed,char ** codigoMed, char** medicos,double * tarifas,
                        int * codigoPac, char **pacientes, double *porcentajes,int *veces, ofstream &archRep){
    
    archRep.precision(2);
    archRep<<fixed;      
    double montoRec, montoSeg;
    int numCitas;
    for(int i=0; codigoMed[i]!=nullptr; i++ ){
        if(strcmp(codigoMed[i], codMed)== 0 ){
            archRep<<left<<"Medico: "<<medicos[i]<<endl;
            archRep<<"Codigo: "<<codigoMed[i]<<endl;
            archRep<<"Honorarios por cita: "<<tarifas[i]<<endl;
            imprimirLinea(archRep, '=', 300);
            archRep<<"Pacientes Atendidos:"<<endl;
            imprimirLinea(archRep, '-', 300);
            archRep<<setw(15)<<"No."<<setw(15)<<"Paciente"<<setw(15)<<"Pago"<<setw(15)<<"Seguro"<<"Veces"<<endl;
            numCitas=montoRec=montoSeg=0;
            for(int j=0; codigoPac[j]!=-1 ; j++){
                
                double pago= porcentajes[j]/100.0 * tarifas[i] * veces[j];
                double seguro= (tarifas[i]* veces[j]) - pago;
                archRep<<setw(15)<<j+1<<setw(15)<<codigoPac[j]<<setw(15)<<pago<<setw(15)<<seguro<<veces[j]<<endl;
                numCitas+= veces[j];
                montoRec+= pago;
                montoSeg+= seguro;
            }
            
            imprimirLinea(archRep, '=', 300);
            archRep<<setw(30)<<"Monto total recibido por paciente:"<<montoRec<<endl;
            archRep<<setw(30)<<"Monto a solicitar al seguro:"<<montoSeg<<endl;
            archRep<<setw(30)<<"Total de citas atendidas:"<<numCitas<<endl;
            imprimirLinea(archRep, '=', 300);
        }
        
    }
    
}

void liberarEspacios(int *codigoPac, char **pacientes,double * porcentajes, int *veces){
    
    for(int i=0; codigoPac[i]!=-1; i++){
        delete pacientes[i];
    }
    delete pacientes;
    delete codigoPac;
    delete porcentajes;
    delete veces;
    
}