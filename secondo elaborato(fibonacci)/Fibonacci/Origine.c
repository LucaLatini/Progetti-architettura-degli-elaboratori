/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Dato in input un numero naturale n, restituire i primi n termini
			  della successione di Fibonacci.

 ********************************************************************************/

#include <stdio.h>

void main()
{
	//Variabili
	int n = 12;						//Numero di termini da restituire
	int successione[50];			//Vettore in cui mettere i primi n termini
									//della successione di Fibonacci

	//Blocco Assembler
	__asm
	{
		XOR EAX, EAX 
		XOR EBX , EBX 
		XOR ECX , ECX 
		XOR EDX , EDX
		XOR ESI , ESI 
		XOR EDI , EDI //azzero tutti i registri che andr� ad usare
		MOV EDI, -1 // lo setto a -1 cos� da non avere problemi con l'incremento iniziale 
		MOV EAX, n // sposto dentro un registro EAX il numeri dei termini della successione di fibonacci 
		MOV EBX, 0 // 
		MOV ECX, 1 //EBX ed ECX saranno i registri con i quali andr� a calcolare mano mano i valori della sequenza di fibonacci 
		MOV EDX, 0 //mi servir� per ripetere il ciclo fin quando EDX non raggiumge un valore uguale ad N in questo caso EAX 
		Salto1:
		INC EDX
		INC EDI
		MOV successione[EDI * 4], EBX // devo mettere *4 poich� mi sposto di interi ossia 4byte
		ADD ESI, EBX
		ADD ESI, ECX // utilizzo il registro ESI come appoggio nel quale vado a salvare la somma dei due registri 
		MOV EBX, ECX // EBX assumer� il valore pi� piccola tra i due termini che poi al nuovo "giro" sar� salvato nell'array
		MOV ECX, ESI //la somma dei due registri la somma ( ossia il seguente valore della successione di fibonacci lo salvo in ECX
		XOR ESI , ESI // resetto ESI in cui salver� la nuova somma del prossimo ciclo 
		CMP EDX, n // se non ho ancora raggiunto il valore di n allora rieseguo il tutto

		JLE Salto1
		JMP Fine
		Fine:
	}

	//Stampa su video
	{
		int i;
		for (i = 0; i <= n; i++)
		{
			printf("%d\n", successione[i]);
		}
	}
}
