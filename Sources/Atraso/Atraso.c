
#include "Motor.h"
#include "Atraso.h"

void atraso_init(){
	motor_init();
	home();
	WaitStop();
}

void atraso_MoverRelativo(int Tempo){
	double dDeslocamento = 0;

	dDeslocamento = (Tempo*C)/2;

	if(mv_relative(dDeslocamento) != None){
		// Colocar msg de erro
	}

	if (WaitStop() != None){
		//Colocar mensagem de erro
	}
}

void atraso_MoverAbsolute(int Tempo){
	double dDeslocamento = 0;

	dDeslocamento = (Tempo*C)/2;

	if(mv_absolute(dDeslocamento) != None){
		// Colocar msg de erro
	}

	if (WaitStop() != None){
		//Colocar mensagem de erro
	}
}
