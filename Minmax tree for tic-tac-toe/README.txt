Detalii implementare Tema 2 SD:
Ca si structuri de date efective am folosit un arbore si o coada.
In nodurile arborelui pot fi stocate mai multe informatii depinzand de
cerinta.

*Cerinta 1:
-Citim mutarea si tabloul asociat jocului de X si O din fisierul de intrare;
-Se verifica daca jocul este deja terminat (desi acest lucru nu era specificat)
si se afiseaza doar tabloul primit cu un mesaj de "atentionare" ca jocul este
deja terminat si se iese;
-Altfel , se incepe crearea arborelui de joc prin functia de inserare;
-Functia de inseare primeste arborele (gol initial) , tabloul asociat starii
jocului, numarul de spatii libere, mutarea urmatoare , linia si coloana
spatiului in care urmeaza sa se introduca o noua mutare si mutarea initiala;
-De asemenea , in functie de mutarea initiala avem o variabila in struct
in cazul in care primul jucator care a facut mutarea castiga. Se parcurge 
recursiv , se creeaza fiii , se adauga mutarea urmatoare , se verifica castigul
si se continua pana cand nu mai exista stari posibile de completat;
-Se reactualizeaza vectorii globali pentru fiecare fiu;
-Se sare peste prima intrare , deoarece trebuie sa initalizam nodul radacina
fara cu starea initiala , primita din fisier;
-Functia de verificare castig parcurge tabloul de doua ori , pentru X si pentru
O, si verifica daca se afla 3 caractere consecutive pe linie , coloana ,
diagonala principala si diagonala secundara. Intoarce 1 daca se indeplineste
si 0 altfel;
-Functia de copiere copiaza un tablou in altul;
-Functia de schimb , schimba mutarea actuala cu opusul ei;
-Functia de nr_aparitii , numara toate locurile libere si pune pozitile lor
in vectorii globali , de aceea trebuie sa fie rescrisi pentru fiecare nou fiu;
-Se ajunge in functia de print ,care , in functie de cerinta se foloseste de
mai multe functii auxiliare;
-Pentru indentare am folosit "\t" intr-un for avand n-ul diferenta dintre
numarul initial de spatii libere si numarul spatiilor libere al tabloului din
nodul care urmeaza sa fie printat , avand astfel distanta pana la el in fisier;

*Cerinta 2:
-Citim mutarea si tabloul asociat jocului de X si O din fisierul de intrare;
-Intram iar in aceeasi functie de inserare ca si la prima cerinta, de data 
asta fiind important parametrul true sau false asociat fiecarui nod si jucatorul
care a facut miscarea la starea curenta;
-Dupa iesirea din cerinta arborele nu va indeplini cerinta de AND/OR , deoarece
doar nodurile terminale care sunt castigate de jucatorul inital vor fi true;
-Vom folosi o alta functie de completare care va ajunge la cel mai jos nivel
al arborelui si va incepe sa completeze parametrii true si false si pentru
celelalte noduri in functie de and sau or, asociat pe nivele;
-Scrierea in fisier este aproximativ la fel ca cea de la cerinta 1 ,mai putin
faptul ca se vor afisa conditiile de true sau false ale nodurilor;

*Cerinta 3:
-Am luat un vector alocat static foarte mare pentru numarul foarte mare de
caractere la intrare din teste;
-Citesc linie cu linie in vector si cu ajutorul lui strtok separ stringurile
de spatii;
-Am folosit o coada pentru a retine intrarile propiu-zise pentru a putea sa 
introduc foarte usor in arbore;
-Pentru fiecare linie, coada se goleste si retine doar linia curenta;
-Intram cu coada curenta in functie si se creaza arborele extragand elementele
din coada si punand nivelul pentru fiecare nod;
-Dupa creerea arborelui , singurele noduri care contin valorile sunt frunzele,
deci vom aplica algoritmul de minimax pe arbore , asemanator cu cel de si/sau,
in sensul ca vom incepe de la cel mai jos nivel;
-In functie de paritatea nivelului curent se va alege minimul sau maximul 
valorilor din fii nodului curent;
-Nodurile cu nivel impar sunt maxime si cele cu nivel par minime;
-Functia de afisare este cam aceeasi si aici , mai putin faptul ca ne vom folosi
de diferenta dintre nivelul maxim si nivelul fiecarui nod pentru indentare si
distanta la afisare , si vor fi afisate valorile fiecarui nod;

La final se elibereaza memoria arborilor.