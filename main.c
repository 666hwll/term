#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char command[256];
   if (!fgets(command, sizeof(command), stdin)) {
       perror("Failed to read command");
       return EXIT_FAILURE;
   }

   // Remove trailing newline character
   size_t len = strlen(command);
   if (command[len - 1] == '\n') {
       command[--len] = '\0';
   }

   FILE *fp = popen(command, "r");
   if (fp == NULL) {
       perror("Failed to execute command");
       return EXIT_FAILURE;
   }

   char buffer[256];
   while (fgets(buffer, sizeof(buffer), fp) != NULL) {
       printf("%s", buffer);
   }

   pclose(fp);
   return 0;
}
