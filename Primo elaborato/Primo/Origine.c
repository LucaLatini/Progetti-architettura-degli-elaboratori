/*********************************************************************************
 *                                                                               *
 *                   Architetture dei sistemi di Elaborazione                    *
 *                                                                               *
 *********************************************************************************

 Elaborato 1
 Descrizione:	Data una stringa C (terminata dal carattere nullo), contenente una
			frase (ossia parole separate da spazi e/o segni di punteggiatura),
			trovare la parola più lunga e la parola più corta. In caso di parole
			di uguale lunghezza, considerare la prima da sinistra.
			Le due parole vanno copiate in due array di caratteri come stringhe
			C (terminate dal carattere nullo).
			I segni di punteggiatura da considerare sono: ".,;:'?!"

 **********************************************************************************/


#include <stdio.h>


void main()
{
	// Variabili
#define MAX_LEN	100
	char frase[MAX_LEN] = "Ciao";
	char parolaMax[MAX_LEN + 1];
	char parolaMin[MAX_LEN + 1];

	// Blocco assembler
	__asm
	{ JMP Principale

		Salto2: // salto2 gestiste il caso specifico in cui si è arrivati alla fine della stringa ossia si è incontrato il carattere '\0'
		CMP ECX, 0 //se ECX è uguale a 0 allora si è incontrato un carattere di fine parola .,;:'?! , e salto a Qui4
		JE Qui4
		CMP ECX, EBX // qui verifico se la parola corrente è minore ( a lunghezza) della parolaMin che avevo trovata in precedenza se così è allora modifico parolaMin altrimenti provo a vedere se è maggiore della parola che già avevo saltando a MaggioreFine
		JL MinoreFine
		JMP MaggioreFine
		MinoreFine :
		XOR EBX, EBX // vado a rimettere a 0 EBX perchè ho trovato una parola più corta qui ci salverò la lunghezza della nuova parola 
		SUB EAX, ECX // sottraggo a EAX, ECX in modo tale da poter ritornare alla prima lettera trovata della parola corrente ad esempio se la parola iniziale è 'ciao' sotraendo ad EAX(4) ECX(4) vado a frase[0] quindi la C 
		CicloFine :
	XOR DH, DH // resetto DH dove salverò i vari caratteri 
		MOV DH, frase[EAX * 1] // ci sposto il carattere 
		MOV parolaMin[EBX * 1], DH // salvo il carattere in parolaMin[EBX] EBX partirà da 0
		XOR DH, DH // ripulisco DH
		INC EAX // incremento EAX in modo tale da avanzare nell'array
		INC EBX// incrememnto EBX poichè ho aggiunto un carattere in parolaMin[] e mi devo comunque salavare il prossimo carattere non più nella posizione 0 ma 1 e così via 
		DEC ECX // decremento ECX sia perchè così posso effettuare il cicloFine esattamente come la lunghezza della parola trovata e allo stesso modo riporto ECX a 0 
		CMP ECX, 0 
		JG CicloFine // se ECX è maggiore di 0 allora ripeti il ciclo 
		MOV parolaMin[EBX], '\0'// quando ECX è 0 esce dal ciclo EBX è stato incrementato e in quella posizione ( una in più rispetto alla vera lunghezza della parola ) vado a metterci il carattere di fine stringa'\0'
		MaggioreFine :
	CMP EDI, ESI // confronto se la nuova parola ha una lunghezza maggiore se è così faccio tutti i cambiamenti 
		JG GrandeFine
		JMP Qui4 // se non è maggiore allora salto a Qui4
		GrandeFine :
	XOR ESI, ESI //vado a rimettere a 0 ESI perchè ho trovato una parola più lunga qui ci salverò la lunghezza della nuova parola
		SUB EAX, EDI // come per il caso della parola minore vado a sottrarre ad EAX la lunghezza (in questo caso ) di EDI 
		Ciclo2Fine:
	XOR DH, DH
		MOV DH, frase[EAX * 1]
		MOV parolaMax[ESI*1], DH
		XOR DH, DH
		// tramite il loop ecx mi viene decrementato mano mano quindi quando è zero vado fuori dal loop e salvo mano mano in parolaMax[] i vari caratteri trovati 
		INC EAX
		INC ESI
		DEC EDI
		CMP EDI, 0
		JG Ciclo2Fine
		MOV parolaMax[ESI], '\0' // com per EBX , ESI avrà un valore maggiore di 1 rispetto alla lunghezza di EDI ( iniziale) quindi in quella posizione vado a salvarci il carattere '\0'
		JMP Fine

	Qui4: // in questo pezzo di codice (quando ECX è 0) incremento EAX e resetto ECX per poi saltare alla fine 
	INC EAX
	XOR ECX, ECX
	JMP Fine







		Salto1:// questo salto controlla i vari caratteri di fine parola , il ragionamento effettuato è il medesimo per salto2 soltanto che al posto di saltare a Fine qui vado a ricomincia poichè non mi trovo alla fine della frase
		CMP ECX , 0
		JE Qui
		CMP ECX , EBX // se ECX è minore di EBX ho trovato una parola più corta altrimenti verifico se essa è più grande
		JL Minore
		JMP Maggiore
		Minore:
		XOR EBX, EBX // vado a rimettere a 0 EBX perchè ho trovato una parola più corta qui ci ssalverò la lunghezza della nuova parola 
		SUB EAX, ECX // qui vado a fare una sottrazione tra la posizione atttuale nell'array meno la lunghezza della parola trovata poi salvo mano le lettere
		CICLO:
		XOR DH, DH
		MOV DH, frase[EAX * 1]
		MOV parolaMin[EBX* 1], DH  // salvo mano in parolaMin[EBX] i vari caratteri della nuova parola EBX , EAX verranno incrementati in modo tale da spostarmi nei 2 array 
		XOR DH, DH
		INC EAX
		INC EBX
		DEC ECX
		CMP ECX, 0
		JG CICLO
		MOV parolaMin[EBX], '\0'

		Maggiore :
		CMP EDI, ESI // confronto se la nuova parola ha una lunghezza maggiore se è così faccio tutti i cambiamenti 
		JG Grande
		JMP Qui // se non è maggiore vuol dire che la nuova parola trovata non è ne maggiore ne minore oppure anche se aveva una lunghezza pari a quella che già era stata salvata allora non apporto modifiche mi tengo la prima trovata 
		Grande :
		XOR ESI, ESI //vado a rimettere a 0 ESI perchè ho trovato una parola più lunga qui ci salverò la lunghezza della nuova parola
		SUB EAX, EDI
		Ciclo2 :
		XOR DH, DH
		MOV DH, frase[EAX * 1]
		MOV parolaMax[ESI*1], DH // salvo mano mano in parolamax[] i vari caratteri della nuova parola da salvare
		XOR DH, DH
			// tramite il loop ecx mi viene decrementato mano mano quindi quando è zero vado fuori dal loop 
		INC EAX
		INC ESI
		DEC EDI
		CMP EDI, 0
		JG Ciclo2
		MOV parolaMax[ESI], '\0' // sposto in nella posizione ESI ( una in più rispetto alla lunghezza effettiva della parola trovata ) il carattere di fine stringa 
		JMP Ricomincia // vado a ricomincia perchè non ho ancora finito la stringa 

		Qui:
		INC EAX 
		XOR ECX , ECX 
		XOR EDI , EDI
		JMP Ricomincia


		Principale:
		XOR EAX , EAX // scorre l'array incrememntato di 1 mano mano 
		XOR ECX , ECX // tiene conto della lunghezza della parola corrente trovata 
		XOR EBX , EBX // contatore per il numero di lettere nella parola più piccola
		MOV EBX , 65535 // In EBX metto il valore massimo in modo tale che la prima parola trovata sarà per forza minore e verrà salvaat in parolaMin[]
		XOR ESI , ESI // contatore per il numero di lettere nella parola maggiore
		XOR EDX , EDX //   di EDX  mi servono DH e DL , DL mi servirà per salvare , e poi fare gli opportuni confronti, con i caratteri che determinano la fine della parola (compreso il carattere di fine stringa '\0')
		// DH mi serve nei vari cicli Salto1 e Salto2 per spostarci dentro i vari caratteri trovati nella parola corrente per poi salvarli in parolaMax[]/parolaMin[]
		MOV ESI , -1 // ESI assumer valore -1 in modo tale che la prima parola trovata sarà per forza maggiore di -1
		XOR EDI , EDI // EDI svolge la medesima funzione di ECX ma verrà usato nel confronto Maggiore e MaggioreFine



		Ricomincia:
		MOV DL, '\0'
		CMP DL, frase[EAX]
		JE Salto2

		MOV DL, '.'
		CMP DL, frase[EAX]
		JE  Salto1
		XOR DL, DL
		MOV DL, ','
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, ';'
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, ':'
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, 27h
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, '?'
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, '!'
		CMP DL, frase[EAX]
		JE Salto1
		XOR DL, DL
		MOV DL, ' '
		CMP DL, frase[EAX]
		JE Salto1
		// faccio i vari controlli per verificare che nella posizione frase[EAX] vi sia un carattere di fine parola nel caso vado a salto1(o salto 2 se mi trovo a fine stringa) muovo dentro DL ogni volta un carattere diverso ma prima con XOR lo pulisco
		INC ECX 
		INC EAX
		INC EDI
		// se ho fatto i vari incrementi allora non ho trovato nessun carattere di fine parola , incremento EAX perchè mi devo muovere nell'array , ECX lo incrememnto perchè vuol dire che ho trovato una parola o anche singola lettera , stesso discorso per EDI
		JMP Ricomincia
		Fine:
		CMP EBX , 65535
		JE NOMIN
		JMP MAX
			NOMIN:
		MOV parolaMin[0], '\0' // confronto inizialmente EBX se questo è invariato allora sposto in parolaMin[0] '\0' , se così non fosse ovvero EBX è cambiato allora mi sposto nel confronto per parolaMax[] e ripeto lo stesso ragionamento
		MAX:
		CMP ESI , -1
		JE NOMAX
		JMP FINE2
			NOMAX:
		MOV parolaMax[0], '\0'
// alla fine pongo un controllo specifico per i casi di stringa vuota o di assenza di parole quindi solo punteggiatura , in questo caso vado a verificare che se i vari contatori della parola 
// maggiore e minore sono rimasti invariati quindi non vi è stato trovata nessuna parola e parolaMax e parolaMin avranno solamente l'elemento di fine stringa 
FINE2:


	}

	// Stampa su video
	printf("%s\n%s\n%s\n", frase, parolaMax, parolaMin);

}

