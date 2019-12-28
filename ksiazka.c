#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>


struct kontakt {
	char imie[20];
	char nazwisko[20];
	char numer[20];
	char grupa[20];
};

struct element {
	struct element *poprzedni;
	struct kontakt dane;
	struct element *nastepny;
};

int wczytaj(struct element **nowy);
void wyswietl(struct element **lista);
void zamien(struct element **lista);
void sortowanie(struct element **lista, int *sort);
int porownanie(struct element **lista, int sort);
int dodaj_kontakt(struct element **lista, int sort);
void szukaj_i_n_g_A(struct element **lista);
int usun_kontakt(struct element **lista);

int main()
{
	struct element *lista, *podstawa;
	int sort = 0, decyzja, flaga = 0, wczytano = 0; //sort 1 - imie, 2 - nazwisko, 3 - grupa
	char c;
	setlocale(LC_ALL, "polish_poland");
	podstawa = lista = malloc(1 * sizeof(struct element));
	lista->poprzedni = NULL;
	strcpy(lista->dane.imie, "zero");
	while (flaga == 0)
	{
		system("cls");
		if (wczytano != 0)
		{
			lista = podstawa;
			wyswietl(&lista);
		}		
		printf("MENU: \n 1. Wczytaj liste kontaktow. \n 2. Posortuj liste kontaktow. \n 3. Dodaj kontakt. \n 4. Usun kontakt. \n 5. Szukaj kontakty. \n 6. Zamknij program. \n");
		while ((scanf("%d", &decyzja) == 0 || decyzja > 6 || decyzja < 1))
		{
			printf("Podano bledna odpowiedz! \n");
			while (getchar() != '\n');
		}
		switch (decyzja)
		{
			lista = podstawa;
		case 1:
			if (wczytano == 0)
			{
				if(wczytaj(&lista) == 1)
					wczytano++;				
				sort = 0;			// Ponieważ jeśli wczyta się listę PO dodaniu kontatku to będzie nieposegregowana!
			} 
			else
			{
				while (lista->nastepny != NULL)
					lista = lista->nastepny;
				wczytaj(&lista);
				if (wczytaj(&lista) == 1)
					wczytano++;
				sort = 0;
			}
			break;
		case 2:
			if (wczytano != 0)
			{			
				lista = podstawa;
				sortowanie(&lista, &sort);
				podstawa = lista;
				printf("Pomyslnie posortowano! \n");
				system("pause");
				break;
			}
			else
			{
				printf("Nie ma co sortowac! \n");
				system("pause");
				break;
			}
		case 3:			
				lista = podstawa;
				dodaj_kontakt(&lista, sort);
				podstawa = lista;				
				wczytano++;
				printf("Pomyslnie dodano kontakt! \n");
				system("pause");
				break;
			
		case 4:
			if (wczytano != 0)
			{	
				lista = podstawa;
				if (usun_kontakt(&lista) == 0)
					wczytano = 0;
				podstawa = lista;
				printf("Pomyslnie usunieto kontakt! \n");
				system("pause");
				break;
			}
			else
			{
				printf("Nie ma co usuwac! \n");
				system("pause");
				break;
			}			
		case 5:
			if (wczytano != 0)
			{	
				lista = podstawa;
				szukaj_i_n_g_A(&lista);
				printf("Skonczono wyszukiwanie kontaktow! \n");
				system("pause");
				break;
			}
			else
			{
				printf("Lista jest pusta i nie ma czego szukać! \n");
				system("pause");
				break;
			}			
		case 6:
			flaga++;
			printf("Zamykam program! \n");
			system("pause");
			break;
		}
	}
	lista = podstawa;
	while (lista != NULL)
	{
		if(lista->nastepny != NULL)
			podstawa = lista->nastepny;
		else
		{
			free(lista);
			return 0;
		}
		free(lista);
		lista = podstawa;
	}
	return 0;
}

int wczytaj(struct element **nowy)
{
	FILE *plik;
	struct element *temp;
	char tekst[50];

	printf("Podaj sciezke pliku! \n");
	scanf("%s", &tekst);
	if (plik = fopen(tekst, "r"))
	{
		temp = malloc(1 * sizeof(struct element));
		if ((*nowy)->poprzedni == NULL)
		{
			fscanf(plik, " %[^;];%[^;];%[^;];%s ", &(*nowy)->dane.imie, &(*nowy)->dane.nazwisko, &(*nowy)->dane.numer, &(*nowy)->dane.grupa);
			(*nowy)->nastepny = temp;
		}
		while (feof(plik) == 0)
		{
			(*nowy)->nastepny = temp;
			fscanf(plik, " %[^;];%[^;];%[^;];%s ", &temp->dane.imie, &temp->dane.nazwisko, &temp->dane.numer, &temp->dane.grupa);
			temp->poprzedni = *nowy;
			*nowy = temp;
			temp = malloc(1 * sizeof(struct element));

		}
		(*nowy)->nastepny = NULL;
		return 1;
	}
	else
	{
		printf("Nie udalo sie otworzyc pliku! \n");
		system("pause");
		return 0;
	}
}
void wyswietl(struct element **lista)
{
	int i = 0;
	struct element *podstawa = *lista;
	while ((*lista) != NULL)
	{
		printf(" Kontakt %d: \n \t Imie: %s \n\t Nazwisko: %s \n\t Numer: %s \n\t Grupa: %s \n", i, (*lista)->dane.imie, (*lista)->dane.nazwisko, (*lista)->dane.numer, (*lista)->dane.grupa);
		*lista = (*lista)->nastepny;
		i++;
	}
	*lista = podstawa;
}
void sortowanie(struct element **lista, int *sort)
{
	int decyzja = 0, flaga = 1, k;
	char kategoria1[50], kategoria2[50];
	struct element swap;
	printf("Wedlug czego chcesz posegregowac liste? \n 1. imie \n 2. nazwisko \n 3. grupa \n");
	while (scanf("%d", sort) == 0 || *sort < 1 || *sort > 3)
	{
		while (getchar() != '\n');
		printf("Podaj poprawna odpowiedz! \n");
	}
	while (flaga != 0)
	{

		flaga = 0;
		//wyswietl(lista);	

		while ((*lista)->nastepny != NULL)
		{
			if (porownanie(lista, *sort) == 1)
			{
				zamien(lista);
				flaga++;
			}
			else
				(*lista) = (*lista)->nastepny;
		}
		while ((*lista)->poprzedni != NULL)
			*lista = (*lista)->poprzedni;
	}
}
int porownanie(struct element **lista, int sort)
{
	char kategoria1[50], kategoria2[50];
	int flaga = 0, k = 0;
	//wyswietl(lista);	

	switch (sort)
	{
	case 1:
		strcpy(kategoria1, (*lista)->dane.imie);
		strcpy(kategoria2, (*lista)->nastepny->dane.imie);
		break;
	case 2:
		strcpy(kategoria1, (*lista)->dane.nazwisko);
		strcpy(kategoria2, (*lista)->nastepny->dane.nazwisko);
		break;
	case 3:
		strcpy(kategoria1, (*lista)->dane.grupa);
		strcpy(kategoria2, (*lista)->nastepny->dane.grupa);
		break;
	}
	k = 0;
	//printf("1. %s \n2. %s \n", kategoria1, kategoria2);
	k = strcoll(kategoria1, kategoria2);
	return k;
}
void zamien(struct element **lista)
{
	if ((*lista)->poprzedni != NULL)
		(*lista)->poprzedni->nastepny = (*lista)->nastepny;
	(*lista)->nastepny->poprzedni = (*lista)->poprzedni;
	(*lista)->poprzedni = (*lista)->nastepny;
	(*lista)->nastepny = (*lista)->poprzedni->nastepny;
	(*lista)->poprzedni->nastepny = *lista;
	if ((*lista)->nastepny != NULL)
		(*lista)->nastepny->poprzedni = *lista;
}
int dodaj_kontakt(struct element **lista, int sort)
{
	struct element *temp = NULL;
	int flaga = 1, k;
	temp = malloc(1 * sizeof(struct element));
	printf("Podaj dane nowego kontaktu: \n");
	printf("Imie: \n");
	scanf("%s", temp->dane.imie);
	printf("Nazwisko: \n");
	scanf("%s", temp->dane.nazwisko);
	printf("Podaj numer: \n");
	scanf("%s", temp->dane.numer);
	printf("Podaj grupe: \n");
	scanf("%s", temp->dane.grupa);
	if ((*lista)->dane.imie[0] == 'z' && (*lista)->dane.imie[1] == 'e' && (*lista)->dane.imie[2] == 'r' && (*lista)->dane.imie[3] == 'o' && (*lista)->dane.imie[4] == '\0')
	{
		temp->poprzedni = NULL;
		temp->nastepny = NULL;
		*lista = temp;
		return 0;
	}

	switch (sort)
	{
	case 1:
		while ((*lista)->nastepny != NULL)
		{
			k = strcoll((*lista)->dane.imie, temp->dane.imie);
			if (k == -1)
				*lista = (*lista)->nastepny;
			else
				break;
		}
		break;
	case 2:
		while ((*lista)->nastepny != NULL)
		{
			if ((strcoll((*lista)->dane.nazwisko, temp->dane.nazwisko)) == -1)
				*lista = (*lista)->nastepny;
			else
				break;
		}
		break;
	case 3:
		while ((*lista)->nastepny != NULL)
		{
			if ((strcoll((*lista)->dane.grupa, temp->dane.grupa)) == -1)
				*lista = (*lista)->nastepny;
			else
				break;
		}
		break;
	default:
		break;
	}
	if ((strcoll((*lista)->dane.imie, temp->dane.imie)) == -1 && (*lista)->nastepny == NULL) // Jeśli dodany na sam koniec, przed NULL
	{
		temp->nastepny = (*lista)->nastepny;
		temp->poprzedni = *lista;
		(*lista)->nastepny = temp;
	}
	else		//Jeśli dodany w środku
	{
		temp->nastepny = (*lista);
		temp->poprzedni = (*lista)->poprzedni;
		(*lista)->poprzedni = temp;
		if ((temp)->poprzedni != NULL)		//Jesli dodany na początek!
			temp->poprzedni->nastepny = temp;
	}
	*lista = temp;
	while ((*lista)->poprzedni != NULL)
		*lista = (*lista)->poprzedni;
	return 1;
}
void szukaj_i_n_g_A(struct element **lista)  // Funkcja szukająca imiona + nazwiska lub grupy według QUERTY lub klawiatury telefonu
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, b = 0, decyzja = 0; // decyzja = 0 -> imie/nazwisko, decyzja = 1 -> grupa
	char c = 3, *tekst = NULL, a;
	char klawiatura[8][7] = {
		{'a', 'ą', 'b', 'c', 'ć'},
		{'d', 'e', 'ę', 'f',},
		{'g', 'h', 'i'},
		{'j', 'k', 'l', 'ł'},
		{'m', 'n', 'o', 'ó'},
		{'p', 'q', 'r', 's', 'ś'},
		{'t', 'u', 'v'},
		{'w', 'x', 'y', 'z', 'ź', 'ż'}
	};
	struct element temp, *podstawa = NULL;
	while ((*lista)->poprzedni != NULL)
		*lista = (*lista)->poprzedni;
	podstawa = *lista;
	tekst = malloc(1 * sizeof(char));
	printf("Wpisz szukane imie i nazwisko, aby przelaczyc sie na grupy wcisnij '#' \n Aby wyczyscic wprowadzany tekst wcisnij '0', aby wyjsc wcisnij 1 \n");
	while (c != '1')
	{
		c = _getch();
		system("cls");
		if (c == '#')
		{
			if (decyzja == 0)
				decyzja = 1;
			else
				decyzja = 0;
		}
		if (decyzja == 0)
			printf("Wpisz szukane imie i nazwisko, aby przelaczyc sie na grupy wcisnij '#' \n Aby wyczyscic wprowadzany tekst wcisnij '0', aby wyjsc wcisnij 1 \n");
		else
			printf("Wpisz szukana grupe, aby przelaczyc sie na szukanie imienia i nazwiska wcisnij '#' \n Aby wyczyscic wprowadzany tekst wcisnij '0', aby wyjsc wcisnij 1 \n");
		if (c == '0')
		{
			free(tekst);
			tekst = malloc(1 * sizeof(char));
			k = 0;
			b = 0;
		}
		else if (c != '1' && c != '0' && c != '#' && c != '\0')
		{
			k++;
			tekst = realloc(tekst, (k + 1) * sizeof(char));
			tekst[k - 1] = tolower(c);
			tekst[k] = '\0';
			while ((*lista)->nastepny != NULL)
			{
				temp = **lista;
				if (decyzja == 0)
				{
					for (i = 0; temp.dane.imie[i] != '\0'; i++)
						temp.dane.imie[i] = tolower(temp.dane.imie[i]);
					for (i = 0; temp.dane.nazwisko[i] != '\0'; i++)
						temp.dane.nazwisko[i] = tolower(temp.dane.nazwisko[i]);
				}
				else
				{
					for (i = 0; temp.dane.grupa[i] != '\0'; i++)
						temp.dane.grupa[i] = tolower(temp.dane.grupa[i]);
				}
				if (isalpha(c))
				{

					if (decyzja == 0)
					{
						if (strstr(temp.dane.imie, tekst) != NULL || (strstr(temp.dane.nazwisko, tekst) != NULL))
						{
							printf(" \n Kontakt %d: \n \t Imie: %s \n\t Nazwisko: %s \n\t Numer: %s \n\t Grupa: %s \n", b, (*lista)->dane.imie, (*lista)->dane.nazwisko, (*lista)->dane.numer, (*lista)->dane.grupa);
							b++;
						}
					}
					else
					{
						if (strstr(temp.dane.grupa, tekst) != NULL)
						{
							printf(" \n Kontakt %d: \n \t Imie: %s \n\t Nazwisko: %s \n\t Numer: %s \n\t Grupa: %s \n", b, (*lista)->dane.imie, (*lista)->dane.nazwisko, (*lista)->dane.numer, (*lista)->dane.grupa);
							b++;
						}
					}
				}
				if (isdigit(c))
				{
					if (decyzja == 0)
					{
						for (i = 0, j = 0; !(temp.dane.imie[i] == '\0' && temp.dane.nazwisko[j] == '\0');)
						{
							//m = n = 0;
							for (m = 0, a = '0'; m < 8; m++, a++) //while(m<8)
							{
								n = 0;
								while ((klawiatura[m][n]) != 0) //for (n = 0; n < 4; n++) 
								{
									if (temp.dane.imie[i] == klawiatura[m][n])
									{
										temp.dane.imie[i] = a + 2;
									}
									if (temp.dane.nazwisko[j] == klawiatura[m][n])
										temp.dane.nazwisko[j] = a + 2;
									n++;
								}
								//m++;
							}
							if (temp.dane.imie[i] != '\0')
								i++;
							if (temp.dane.nazwisko[j] != '\0')
								j++;
						}
						if (strstr(temp.dane.imie, tekst) != NULL || (strstr(temp.dane.nazwisko, tekst) != NULL))
						{
							printf(" \n Kontakt %d: \n \t Imie: %s \n\t Nazwisko: %s \n\t Numer: %s \n\t Grupa: %s \n", b, (*lista)->dane.imie, (*lista)->dane.nazwisko, (*lista)->dane.numer, (*lista)->dane.grupa);
							b++;
						}
					}
					else
					{
						for (i = 0; temp.dane.grupa[i] != '\0'; i++)
						{
							for (m = 0, a = '0'; m < 8; m++, a++)
							{
								n = 0;
								while ((klawiatura[m][n]) != 0) //for (n = 0; n < 4; n++) 
								{
									if (temp.dane.grupa[i] == klawiatura[m][n])
									{
										temp.dane.grupa[i] = a + 2;
									}
									n++;
								}
							}
						}
						if (strstr(temp.dane.grupa, tekst) != NULL)
						{
							printf(" \n Kontakt %d: \n \t Imie: %s \n\t Nazwisko: %s \n\t Numer: %s \n\t Grupa: %s \n", b, (*lista)->dane.imie, (*lista)->dane.nazwisko, (*lista)->dane.numer, (*lista)->dane.grupa);
							b++;
						}
					}
				}
				*lista = (*lista)->nastepny;
			}
			*lista = podstawa;
			printf("szukana fraza: %s", tekst);
		}
		if (c != '1')
			c = _getch();
	}
	free(tekst);
}
int usun_kontakt(struct element **lista)
{
	struct element *temp = NULL;
	int i, ile = 0, decyzja;
	temp = *lista;
	while ((*lista)->nastepny != NULL)
	{
		ile++;
		*lista = (*lista)->nastepny;
	}
	*lista = temp;
	printf("Ktory kontakt chcesz usunac? Podaj numer: \n");
	wyswietl(lista);
	while (scanf("%d", &decyzja) == 0 || decyzja < 0 || decyzja > ile)
	{
		while (getchar() != '\n');
		printf("Podaj poprawna odpowiedz! \n");
	}
	if ((*lista)->nastepny == NULL && (*lista)->poprzedni == NULL)
	{
		free(*lista);
		*lista = malloc(1 * sizeof(struct element));
		(*lista)->poprzedni = NULL;
		strcpy((*lista)->dane.imie, "zero");
		return 0;
	}
	for (i = 0; i < decyzja; i++)
		*lista = (*lista)->nastepny;
	if ((*lista)->poprzedni != NULL)
		(*lista)->poprzedni->nastepny = (*lista)->nastepny;
	if ((*lista)->nastepny != NULL)
	{
		temp = (*lista)->nastepny;
		(*lista)->nastepny->poprzedni = (*lista)->poprzedni;
	}
	else
		temp = (*lista)->poprzedni;
	free(*lista);
	*lista = temp;
	while ((*lista)->poprzedni != NULL)
		*lista = (*lista)->poprzedni;
	return 1;
}
