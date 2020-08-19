#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

//using namespace std;

static void help(char *progname);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    help(argv[0]);
    return EXIT_FAILURE;
  }

  FILE *outputFile = stdout; // output to file or stdout
  int opt;
  while ((opt = getopt(argc, argv, "hw:")) != -1) {
    switch (opt) {
      case 'w':
        outputFile = fopen(optarg, "w");
        break;
      case 'h':
        help(argv[0]);
        break;
      case '?':
        if (optopt == 'w')
          fprintf(stderr, "ERROR: Output file is not specified with '-%c'.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "ERROR: Unknown option '-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
        fclose(outputFile);
        return EXIT_FAILURE;
      default:
        abort();
    }
  }
  for (int index = optind; index < argc; index++)
    printf("WARNING: Non-option argument, '%s'\n", argv[index]);
  fclose(outputFile);
  return EXIT_SUCCESS;
}

static void help(char *progname)
{
  const char *text = "\n\tPre-processing an OpenFOAM case\n\n"
  "\tUsage: ";
  printf("%s%s", text, progname);
  text = " [OPTIONS]\n\n\tOPTIONS:\n"
  "\t  -h\t\t\t\tShow this message\n"
  "\t  -g\t\t\t\tCollect general data\n"
  "\t  -i\t\t\t\tPre-process initial conditions\n"
  "\t  -a\t\t\t\tCollect all data\n"
  "\t  -f [FOLDER PATH]\t\tSpecify case folder as a string [FOLDER PATH]"
  ". If this option is not specified, the app will run on current path ($PWD)\n"
  "\t  -w [REPORT FILE]\t\tSpecify report data file name as a string [REPORT FILE]"
  ". If this option is not specified data will be displayed on standart output (stdout)\n\n"
  "\t NOTE: -w and -f should be specified before any other options!\n\n"
  "\tEXAMPLES:\n"
  "\t  Display initial/boundary conditions data from ${HOME}/OpenFOAM/myCase:\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase -i\n\n";
  printf("%s", text);
  text = "\t  Collect all data from case ${HOME}/OpenFOAM/myCase into 'report.txt':\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase -w report.txt -a\n\n";
  printf("%s", text);
}
