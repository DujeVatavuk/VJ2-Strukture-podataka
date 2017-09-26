/*
Definirati strukturu osoba (ime, prezime, godina rodjenja) i napisati program koji:
- dinamicki dodaje novi element na pocetak liste,__________________________________NAPRAVIJA
- ispisuje listu,__________________________________________________________________NAPRAVIJA
- dinamicki dodaje novi element na kraj liste,_____________________________________NAPRAVIJA
- pronalazi element u listi (po prezimenu),________________________________________NAPRAVIJA
- brise odredjeni element iz liste,________________________________________________NAPRAVIJA
- dinamicki dodaje novi element iza odredjenog elementa,___________________________NAPRAVIJA
- dinamicki dodaje novi element ispred odredjenog elementa,________________________NAPRAVIJA
U zadatku se ne smiju koristiti globalne varijable.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct osoba *Pos;
typedef struct osoba
{
	char ime[10];
	char prezime[10];
	int godina_rodjenja;
	Pos next;
}osoba;

void DodajNaPocetak(Pos);
void DodajNaKraj(Pos);
void DodajIspred(Pos);
void DodajIza(Pos);
Pos Pronadji(Pos);
Pos PronadjiPredhodnog(Pos);
Pos PronadjiZadnjeg(Pos);
void Ispisi(Pos);
void Izbrisi(Pos);
void UpisiUDatoteku(Pos);
void CitanjeIzDatoteke(Pos);

int main()
{
	osoba head;
	head.next = NULL;

	Pos q;
	int izbor = 0;

	while (izbor != 7)
	{
		printf("\nUnesite broj ispred radnje koju zelite izvrsiti");
		printf("\n\t0 - Unos elementa na pocetak");
		printf("\n\t1 - Unos elementa na kraj");
		printf("\n\t2 - Unos elementa na ispred nekog drugog elementa");
		printf("\n\t3 - Unos elementa na iza nekog drugog elementa");
		printf("\n\t4 - Ispis liste");
		printf("\n\t5 - Trazenje po prezimenu");
		printf("\n\t6 - Brisanje nekog clana liste");
		printf("\n\t7 - KRAJ");
		printf("\nUnesite svoj izbor: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 0:
			DodajNaPocetak(&head);
			break;
		case 1:
			DodajNaKraj(&head);
			break;
		case 2:
			DodajIspred(&head);
			break;
		case 3:
			DodajIza(&head);
			break;
		case 4:
			Ispisi(head.next);
			break;
		case 5:
			q = Pronadji(&head);
			printf("\n\t %s %s %d", q->ime, q->prezime, q->godina_rodjenja);
			break;
		case 6:
			Izbrisi(&head);
			break;
		case 7:
			printf("\nKRAJ PROGRAMA");
			break;
		default:
			printf("\nUnjeli ste krivi broj, pokusajte ponovo");
			break;
		}
	}
	return 0;
}

void DodajNaPocetak(Pos P)
{
	Pos temp = (Pos)malloc(sizeof(osoba));

	printf("\nUnesite svoje ime: ");
	scanf(" %s", temp->ime);
	printf("Unesite svoje prezime: ");
	scanf(" %s", temp->prezime);
	printf("Unesite svoju godinu rodjenja: ");
	scanf("%d", &temp->godina_rodjenja);

	temp->next = P->next;
	P->next = temp;
}

void DodajNaKraj(Pos P)
{
	Pos temp = (Pos)malloc(sizeof(osoba));

	printf("\nUnesite svoje ime: ");
	scanf(" %s", temp->ime);
	printf("Unesite svoje prezime: ");
	scanf(" %s", temp->prezime);
	printf("Unesite svoju godinu rodjenja: ");
	scanf("%d", &temp->godina_rodjenja);

	P = PronadjiZadnjeg(P);

	temp->next = NULL;//moglo se i temp->next = P->next posto je isto null
	P->next = temp;
}

void DodajIspred(Pos P)
{
	P = Pronadji(P);

	DodajNaPocetak(P);
}

void DodajIza(Pos P)
{
	P = Pronadji(P);
	P = P->next;
	DodajNaPocetak(P);
}

Pos Pronadji(Pos P)
{
	char prez[10];
	printf("\nUnesite prezime osobe koju trazite: ");
	scanf(" %s", prez);

	while (!strcmp(P->prezime, prez) && NULL != P->next);
	{
		P = P->next;
	}

	if (NULL == P->next)
	{
		printf("\nNe postoji osoba s tim prezimenom");
		P = NULL;
	}
	return P;
}

Pos PronadjiPredhodnog(Pos P)
{
	char prez[10];

	if (NULL == P)
	{
		P = NULL;
	}
	else
	{
		printf("\nUnesite prezime osobe: ");
		scanf(" %s", prez);

		while (!strcmp(P->next->prezime, prez) && NULL != P->next->next)
		{
			P = P->next;
		}

		if (!strcmp(P->next->prezime, prez))
		{
			printf("\nNe postoji osoba s tim prezimenom");
			P = NULL;
		}
	}
	return P;
}

Pos PronadjiZadnjeg(Pos P)
{
	while (NULL != P->next)
	{
		P = P->next;
	}
	return P;
}

void Ispisi(Pos P)//ode ima neki zez, pripaziti
{
	while (NULL != P->next)
	{
		printf("\nIme i prezime: %s %s\nGodina rodjenja: %d", P->ime, P->prezime, P->godina_rodjenja);
		P = P->next;
	}
	printf("\nIme i prezime: %s %s\nGodina rodjenja: %d", P->ime, P->prezime, P->godina_rodjenja);
}

void Izbrisi(Pos P)
{
	Pos prev;
	
	prev = PronadjiPredhodnog(P);

	if (NULL != prev)
	{
		P = prev->next;
		prev->next = P->next;
		printf("\n\tOsoba %s %s %d ce biti izbrisana", P->ime, P->prezime, P->godina_rodjenja);
		free(P);
	}
	else
	{
		printf("\nOsoba ne postoji u listi");
	}
}