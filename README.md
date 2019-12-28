# Książka telefoniczna

Program ma za zadanie funkcjonować jak książka telefoniczna w starszych telefonach komórkowych. 
Dane są ułożone w postaci listy dwukierunkowej, w której każde elementy ("cegły") składają się kolejno z:  
wskaźnika na następny element,  
danych (imię, nazwisko, numer, grupa),  
wskaźnika na poprzedni element.  

Kontakty ułożone w ten sposób można sortować (według imienia i nazwiska lub grupy), dodawać ręcznie, usuwać,
doawać wielokrotnie w formie pliku .csv i raz posortowane kontakty będą już takie cały czas (przy usunięciu, dodaniu itd. kontaktów 
lista pozostaje posortowana).

## Wyszukiwanie kontaktów

W przypadku szukania kontaktów NIE WOLNO używać klawisza backspace do kasowania wprowadzonych znaków. Należy w tym celu używać '0'.
Wyszukiwanie odbywa się w dwóch przypadkach:  
1. Po imieniu i nazwisku jednocześnie,  
2. Po samej grupie.  
Pomiędzy tymi trybami można przełączać się klawiszem '1'.

Wyszukiwać kontakty można wpisując litery z klawiatury lub jak gdybyśmy mieli do czynienia z klawiaturą numeryczną telefonów komórkowych
według formatu:  
```
7 8 9
4 5 6 
  2 3
```
Co przekłada się na znaki:
```
pqrsś tuv   wxyzźż
ghi   jklł  mnoó
      aąbcć deęf 
```

## Przygotowania do włączenia programu
 
Wystarczy załączyć plik ksiazka.c do projektu i gotowe. Przygotowany został również plik lista.csv jako baza danych do programu.
Należy go wczytać w menu programu podając jego ścieżkę lub, jeśli się znajduje w folderze z ksiazka.c, samą jego nazwę.

### Programy dodatkowe

Nie ma większych wymagań co do oprogramowania potrzebnego do uruchomienia programu. 
W trakcie tworzenia oprogramowania korzystano z Microsoft Visual Studio Community 2019 16.1.0

## Autor

* **Jakub Szwedowicz** - *Solver* - [JakubSzwedowicz](https://github.com/JakubSzwedowicz)
