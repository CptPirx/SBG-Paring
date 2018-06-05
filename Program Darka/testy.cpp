 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 int main(int argc , const char **argv) {
   char haslo_poprawne = 0;
   char haslo[16];
   
   if (argc!=2) {
     fprintf(stderr, "uzycie: %s haslo", argv[1]);
     return EXIT_FAILURE;
   }
   
   strcpy(haslo, argv[1]); /* tutaj nastêpuje przepe³nienie bufora */
   if (!strcmp(haslo, "poprawne")) {
     haslo_poprawne = 1;
   }
   
   if (!haslo_poprawne) {
     fputs("Podales bledne haslo.\n", stderr);
     return EXIT_FAILURE;
   }
   
   puts("Witaj, wprowadziles poprawne haslo.");
   return EXIT_SUCCESS;
 }
