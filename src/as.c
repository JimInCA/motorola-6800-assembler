
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "as.h"
#include "output.h"
#include "util.h"
#include "ffwd.h"
#include "do0.h"
#include "ffwd.h"
#include "pseudo.h"
#include "symtab.h"

/* global variables */
int     Line_num =0;            /* current line number          */
//int     Err_count =0;           /* total number of errors       */
char    Line[MAXBUF] = {0};     /* input line buffer            */
char    Label[MAXLAB] = {0};    /* label on current line        */
char    Op[MAXOP] = {0};        /* opcode mnemonic on current line      */
char    Operand[MAXBUF] = {0};  /* remainder of line after op           */
char    *Optr =0;               /* pointer into current Operand field   */
int     Result =0;              /* result of expression evaluation      */
int     Force_word =0;          /* Result should be a word when set     */
int     Force_byte =0;          /* Result should be a byte when set     */
int     Pc =0;                  /* Program Counter              */
int     Old_pc =0;              /* Program Counter at beginning */

int     Last_sym =0;            /* result of last lookup        */

int     Pass =0;                /* Current pass #               */
int     N_files =0;             /* Number of files to assemble  */
FILE    *Fd =0;                 /* Current input file structure */
int     Cfn =0;                 /* Current file number 1...n    */
int     Ffn =0;                 /* forward ref file #           */
int     F_ref =0;               /* next line with forward ref   */
char    **Argv =0;              /* pointer to file names        */

int     E_total =0;             /* total # bytes for one line   */
int     E_bytes[E_LIMIT] = {0}; /* Emitted held bytes           */
int     E_pc =0;                /* Pc at beginning of collection*/

int     Lflag = 0;              /* listing flag 0=nolist, 1=list*/

int     P_force = 0;            /* force listing line to include Old_pc */
int     P_total =0;             /* current number of bytes collected    */
int     P_bytes[P_LIMIT] = {0}; /* Bytes collected for listing  */

int     Cflag = 0;              /* cycle count flag */
int     Cycles = 0;             /* # of cycles per instruction  */
long    Ctotal = 0;             /* # of cycles seen so far */
int     Sflag = 0;              /* symbol table flag, 0=no symbol */
int     N_page = 0;             /* new page flag */
int     Page_num = 2;           /* page number */
int     CREflag = 0;            /* cross reference table flag */

struct  nlist *root;            /* root node of the tree */
  
FILE    *Objfil =0;             /* object file's file descriptor*/
char    Obj_name[] = {"             "};

void initialize(void);
void make_pass(void);
void re_init(void);
void process(void);
int parse_line(void);

/*
	as ---	cross assembler main program
 */
int main(int argc, char *argv[])
{
	char	**np;
	char	*i;
	FILE	*fopen();
	int	j = 0;

	if(argc < 2){
		printf("Usage: %s [files]\n",argv[j]);
		exit(1);
		}
	  Argv = argv;
	  initialize();
	  while ((*argv[j] != '-') && (j<argc))
	   j++;
	  N_files = j-1;
	 if (j < argc )
	  {
	  argv[j]++;
	  while (j<argc)
	   {
	   for (i = argv[j]; *i != 0; i++)
	     if ((*i <= 'Z') && (*i >= 'A'))
	       *i = *i + 32;
	   if (strcmp(argv[j],"l")==0)
	     Lflag = 1;
	   else if (strcmp(argv[j],"nol")==0)
	     Lflag = 0;
	   else if (strcmp(argv[j],"c")==0)
	      Cflag = 1;
	   else if (strcmp(argv[j],"noc")==0)
	     Cflag = 0;
	   else if (strcmp(argv[j],"s")==0)
	     Sflag = 1;
	   else if (strcmp(argv[j],"cre")==0)
	     CREflag = 1;
	    j++;
	   }
	  }
	root = NULL;

	Cfn = 0;
	np = argv;
	Line_num = 0; /* reset line number */
	while( ++Cfn <= N_files )
		if((Fd = fopen(*++np,"r")) == NULL)
			printf("as: can't open %s\n",*np);
		else{
			make_pass();
			fclose(Fd);
		}
	if( Err_count == 0 ){
		Pass++;
		re_init();
		Cfn = 0;
		np = argv;
		Line_num = 0;
		while( ++Cfn <= N_files)
			if((Fd = fopen(*++np,"r")) != NULL)
			    {
				make_pass();
				fclose(Fd);
			     }
			if (Sflag == 1)
			  {
			    printf ("\f");
			    stable (root);
			  }
			if (CREflag == 1)
			  {
			    printf ("\f");
			    cross (root);
			  }
		fprintf(Objfil,"S9030000FC\n"); /* at least give a decent ending */
		}
	exit(Err_count);
}

void initialize(void)
{
	FILE	*fopen();
	int	i = 0;

#ifdef DEBUG
	printf("Initializing\n");
#endif
	Err_count = 0;
	Pc	  = 0;
	Pass	  = 1;
	Lflag	  = 0;
	Cflag	  = 0;
	Ctotal	  = 0;
	Sflag	  = 0;
	CREflag   = 0;
	N_page	  = 0;
	Line[MAXBUF-1] = NEWLINE;

	strcpy(Obj_name,Argv[1]); /* copy first file name into array */
	do {
	    if (Obj_name[i]=='.')
	       Obj_name[i]=0;
	}
	while (Obj_name[i++] != 0);
	strcat(Obj_name,".s19");  /* append .out to file name. */
	if( (Objfil = fopen(Obj_name,"w")) == NULL)
		fatal("Can't create object file");
	fwdinit();	/* forward ref init */
	localinit();	/* target machine specific init. */
}

void re_init(void)
{
#ifdef DEBUG
	printf("Reinitializing\n");
#endif
	Pc	= 0;
	E_total = 0;
	P_total = 0;
	Ctotal	= 0;
	N_page	= 0;
	fwdreinit();
}

void make_pass(void)
{
	char	*fgets();

#ifdef DEBUG
	printf("Pass %d\n",Pass);
#endif
	while( fgets(Line,MAXBUF-1,Fd) != (char *)NULL ){
		Line_num++;
		P_force = 0;	/* No force unless bytes emitted */
		N_page = 0;
		   if(parse_line())
			process();
		if(Pass == 2 && Lflag && !N_page)
			print_line();
		P_total = 0;	/* reset byte count */
		Cycles = 0;	/* and per instruction cycle count */
		}
	f_record();
}


/*
 *	parse_line --- split input line into label, op and operand
 */
int parse_line(void)
{
	register char *ptrfrm = Line;
	register char *ptrto = Label;
	char	*skip_white();

	if( *ptrfrm == '*' || *ptrfrm == '\n' )
		return(0);	/* a comment line */

	while( delim(*ptrfrm)== NO )
		*ptrto++ = *ptrfrm++;
	if(*--ptrto != ':')ptrto++;     /* allow trailing : */
	*ptrto = EOS;

	ptrfrm = skip_white(ptrfrm);

	ptrto = Op;
	while( delim(*ptrfrm) == NO)
		*ptrto++ = mapdn(*ptrfrm++);
	*ptrto = EOS;

	ptrfrm = skip_white(ptrfrm);

	ptrto = Operand;
	while( *ptrfrm != NEWLINE )
		*ptrto++ = *ptrfrm++;
	*ptrto = EOS;

#ifdef DEBUG
	printf("Label-%s-\n",Label);
	printf("Op----%s-\n",Op);
	printf("Operand-%s-\n",Operand);
#endif
	return(1);
}

/*
 *	process --- determine mnemonic class and act on it
 */
void process(void)
{
	register struct oper *i;
	struct oper *mne_look();

	Old_pc = Pc;		/* setup `old' program counter */
	Optr = Operand; 	/* point to beginning of operand field */

	if(*Op==EOS){		/* no mnemonic */
		if(*Label != EOS)
			install(Label,Pc);
		}
	else if( (i = mne_look(Op))== NULL)
		error("Unrecognized Mnemonic");
	else if( i->class == PSEUDO )
		do_pseudo(i->opcode);
	else{
		if( *Label )install(Label,Pc);
		if(Cflag)Cycles = i->cycles;
		do_op(i->opcode,i->class);
		if(Cflag)Ctotal += Cycles;
		}
}

