1. Ho inserito con successo in dictionary.h e dictionary.c
   la funzione char * toLowerString ( char * word, char * word1 ); 
   Speller compila e valgrind non da' ne' errori ne' leaks.

2. Ho utilizzato la funzione sopra descritta inserendola in speller.c
   Ho immagazzinato la versione lower case di word in lowerCaseWord.
   Il check viene quindi fatto su lowerCaseWord e non piu' su word.
   A questo punto sara' possibile utilizzare semplicemente strcmp(), ed evitare altre funzioni
   come strcasecmp().  
   speller.c compila e valgrind non da' errori. 
   
3. Inserita senza problemi la hash function in dictionary.h e dictionary.c

4. Inserita senza problemi la definizione di struct node in dictionary.h 

5. Ho dichiarato hashtable[26] come variabile globale in speller.c
   Nessuno si lamenta per il fatto che i pointers non siano inizializzati.
   Li settero' come NULL in load?
   Nessun errore in valgrind (nessuna leak ovviamente).
   
6. Prima di inserire implementare load() nel programma ho testato con valgrind le versioni
   che sembrano funzionare. (versione 'alfabetica' e non). Valgrind riscontra quattro errori
   in entrambe:
   
   Conditional jump or move depends on uninitialised value(s)
==30340==    at 0x406CB3C: toupper (ctype.c:52)
==30340==    by 0x804865E: hash (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340==    by 0x80485E7: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340== 
==30340== Use of uninitialised value of size 4
==30340==    at 0x406CB53: toupper (ctype.c:52)
==30340==    by 0x804865E: hash (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340==    by 0x80485E7: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340== 
==30340== Invalid read of size 4
==30340==    at 0x80485F0: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340==  Address 0xbee09f94 is just below the stack ptr.  To suppress, use: --workaround-gcc296-bugs=yes
==30340== 
==30340== Invalid write of size 4
==30340==    at 0x8048600: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/hashtable5)
==30340==  Address 0xbee09f94 is just below the stack ptr.  To suppress, use: --workaround-gcc296-bugs=yes 
  
   Conditional jump or move depends on uninitialised value(s)
==30184==    at 0x406CB3C: toupper (ctype.c:52)
==30184==    by 0x80486FB: hash (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184==    by 0x8048671: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184== 
==30184== Use of uninitialised value of size 4
==30184==    at 0x406CB53: toupper (ctype.c:52)
==30184==    by 0x80486FB: hash (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184==    by 0x8048671: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184== 
==30184== Invalid read of size 4
==30184==    at 0x804867A: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184==  Address 0xbea43f94 is just below the stack ptr.  To suppress, use: --workaround-gcc296-bugs=yes
==30184== 
==30184== Invalid write of size 4
==30184==    at 0x8048692: main (in /home/jharvard/Desktop/PSET5_PREPARATION/1/load/insert3)
==30184==  Address 0xbea43f94 is just below the stack ptr.  To suppress, use: --workaround-gcc296-bugs=yes

    Devo risolvere questo prima di implementare load nel programma. 
   
7.  Problema risolto. Ho evitato l'uso di feof e ho utilizzato direttamente fscanf nella
    condizione del loop. I quattro errori sono scomparsi (e abbiamo anche capito il perche'...)
    Prima di implementare load nel programma pero'
    provo a inserire l'algoritmo per inserire alfabeticamente, dato che Zamyla dice di usarlo.
    (Anche se non ho ancora capito come sfruttarlo quando si arriva a check() ).

8.  Ho sostituito strcmp() a strcasecmp() in insert() in insert3.c e il file funziona.
    (peraltro non c'era assolutamente bisogno di utilizzare strcasecmp in quel punto
    dato che la comparazione avviene solo tra parole del dizionario che sono tutto lower case).
    Ho implementato la funzione in hashtable5.c. Tutto funziona correttamente, nessun errore, ecc..
    Procedo ad implementare nel programma. 
    
9.  Ho inserito insert() in dictionary.c e dictionary.h e, dopo avere incluso <string.h>, la compilazione
    avviene senza errori. Valgrind non riscontra errori. 
    
10. POSSO PROCEDERE AD IMPLEMENTARE LOAD.
    La funzione sembra essere stata implementata correttamente. Ho fatto un test con il vocabolario small.txt
    che ho messo nel desktop come primo argomento e questo stesso README.txt file come secondo argomento.
    Questo e' il risultato di valgrind:
    ==828== 
==828== HEAP SUMMARY:
==828==     in use at exit: 1,768 bytes in 34 blocks
==828==   total heap usage: 36 allocs, 2 frees, 2,472 bytes allocated
==828== 
==828== LEAK SUMMARY:
==828==    definitely lost: 0 bytes in 0 blocks
==828==    indirectly lost: 0 bytes in 0 blocks
==828==      possibly lost: 0 bytes in 0 blocks
==828==    still reachable: 1,768 bytes in 34 blocks
==828==         suppressed: 0 bytes in 0 blocks
==828== Rerun with --leak-check=full to see details of leaked memory
==828== 
==828== For counts of detected and suppressed errors, rerun with: -v
==828== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

    PRIMA DI PROCEDERE AD IMPLEMENTE LE ALTRE FUNZIONI (SI DEVE FARE PRIMA CHECK DI UNLOAD ...)
    FERMARSI UN ATTIMO A PENSARE !!!
   
11. Ho implementato check() nel programma. Valgrind non da' errori. (Ci sono ovviamente leaks dato
    che non abbiamo ancora implementato unload() ). 
    Ecco i risulati: 
jharvard@appliance (~/Dropbox/pset5): valgrind ./speller /home/jharvard/Desktop/small.txt text.txt
==2512== Memcheck, a memory error detector
==2512== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==2512== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==2512== Command: ./speller /home/jharvard/Desktop/small.txt text.txt
==2512== 

MISSPELLED WORDS

questo
e'
un
testo
prova
Could not unload /home/jharvard/Desktop/small.txt.
==2512== 
==2512== HEAP SUMMARY:
==2512==     in use at exit: 1,768 bytes in 34 blocks
==2512==   total heap usage: 36 allocs, 2 frees, 2,472 bytes allocated
==2512== 
==2512== LEAK SUMMARY:
==2512==    definitely lost: 0 bytes in 0 blocks
==2512==    indirectly lost: 0 bytes in 0 blocks
==2512==      possibly lost: 0 bytes in 0 blocks
==2512==    still reachable: 1,768 bytes in 34 blocks
==2512==         suppressed: 0 bytes in 0 blocks
==2512== Rerun with --leak-check=full to see details of leaked memory
==2512== 
==2512== For counts of detected and suppressed errors, rerun with: -v
==2512== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

12. Sto testando speller per vedere se le parola vengono checkate correttamente. Senza apostrofi
    le parole sembrano essere checkate correttamente. 
    Pure le parole che presentano apostrofo/i sembrano essere checkate con correttezza.
    Adesso testo le maiuscole nel testo;
    tutto funziona correttamente. 
    
13. Ho implementato size. 
    Valgrind non si lamenta. 
    
14. Ho implementato la versione ignorante di unload().
    Tutto sembra funzionare correttamente: 
jharvard@appliance (~/Dropbox/pset5): valgrind ./speller /home/jharvard/Desktop/small.txt text.txt
==3128== Memcheck, a memory error detector
==3128== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3128== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==3128== Command: ./speller /home/jharvard/Desktop/small.txt text.txt
==3128== 

MISSPELLED WORDS

parolachenonc'e'

WORDS MISSPELLED:     1
WORDS IN DICTIONARY:  34
WORDS IN TEXT:        5
TIME IN load:         0.03
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04

==3128== 
==3128== HEAP SUMMARY:
==3128==     in use at exit: 0 bytes in 0 blocks
==3128==   total heap usage: 36 allocs, 36 frees, 2,472 bytes allocated
==3128== 
==3128== All heap blocks were freed -- no leaks are possible
==3128== 
==3128== For counts of detected and suppressed errors, rerun with: -v
==3128== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)



lanciando : valgrind ./speller ~cs50/pset5/texts/austinpowers.txt
ottengo:

==3442== 
==3442== HEAP SUMMARY:
==3442==     in use at exit: 0 bytes in 0 blocks
==3442==   total heap usage: 143,093 allocs, 143,093 frees, 7,441,436 bytes allocated
==3442== 
==3442== All heap blocks were freed -- no leaks are possible
==3442== 
==3442== For counts of detected and suppressed errors, rerun with: -v
==3442== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)



15. Anche il programma sembra funzionare correttamente make50 si lamenta:
    Expecting the following on standard out —  [object Object]
    
    ... but received the following on standard error instead —  dictionary.o: In function `check':
/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:23: undefined reference to `hashtable'
dictionary.o: In function `load':
/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:54: undefined reference to `hashtable'
/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:71: undefined reference to `hashtable'
/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:71: undefined reference to `hashtable'
dictionary.o: In function `unload':
/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:94: undefined reference to `hashtable'
dictionary.o:/var/sandbox50/sandboxes/5ce7cf489f2d43ffb6d7de918c30207d/homedir/dictionary.c:102: more undefined references to `hashtable' follow
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [speller] Error 1


16. Ho reso dichiarato hashtable[] come variabile globale all'interno di dictionary.c.
    make 50 si lamenta per altri not standard error: (che evidentemente sono legati alle variabile extern...)
    
    Expecting the following on standard out —  basic.out,[object Object]
    
    ... but received the following on standard error instead — /opt/sandbox50/bin/run.sh: line 31:  5745 Segmentation fault      stdbuf --error=0 --output=0 "$@"
    
    
    Cerco di risolvere eliminado extern variables se ci sono...
    
17.

    
    


