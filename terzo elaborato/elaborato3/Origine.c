/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione: Dato un array di BYTE, invertire l’ordine dei bit all’interno
			  dell’array.

 ********************************************************************************/


#include <stdio.h>

void main()
{
#define MAX_LEN	100

	// Input
	unsigned char vet[] = { 0xAA,0xFC,0x09};			//Array di BYTE
	unsigned int len = sizeof(vet) / sizeof(vet[0]);	// numero di byte in vet	
// Output
	unsigned char res[MAX_LEN];						//Array di BYTE contenente il risultato 

// Blocco assembler
	__asm
	{	XOR ESI , ESI // contatore che mi va da 0 a len-1 mi serve per portare il terzo byte al primo posto 
		XOR EAX , EAX // ho azzerato EAX perchè il AL ci ancrà il bit da invertire 
		XOR BL , BL // ci inserisco i bit che mano mano con RCL vengono shiftati verso sinistra per poi porre tutto BL dentro Res
		XOR ECX , ECX
		MOV  ECX , len // pongo in ECX la lunghezza 
		XOR EDX,EDX
		DEC ECX
		MOV EDX, 8 // numero di bit in un byte
		CicloGrande:
		MOV AL , vet[ECX]
		CicloPiccolo:
		SHR AL, 1// shifta a destra il byte originale
		RCL BL, 1//shifta a sinistra il byte invertito e copia il bit meno significativo del byte originale tramite la flag CF
		DEC EDX
		CMP EDX, 0//controlla se sono stati shiftati tutti i bit
		JNE CicloPiccolo //se non tutti i bit sono stati shiftati, ritorna all'inizio del loop
		MOV res[ESI], BL
		DEC ECX // devo shiftare tutti i byte 
		INC ESI
		XOR AL , AL
		XOR BL , BL
		XOR EDX , EDX
		MOV EDX , 8 // ripristino a 8 EDX così che potrò riusarlo per il secondo byte e così via 
		CMP ECX , 0 // se non sono arrivato a 0 significa che devo gestire altri byte
		JGE CicloGrande
		JMP Fine // se ECX è < di 0 significa che ho gestito tutti i byte

Fine:
	}

	// Stampa su video
	{
		unsigned int i;
		for (i = 0; i < len; i++)
			printf("res[%2d] = %10d (%08X)\n", i, res[i], res[i]);
	}
}

