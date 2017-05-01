/*
 *      machine independent definitions and global variables
 */

#define YES     1
#define NO      0
#define ERR     (-1)

#define MAXBUF  128
#define MAXOP   10      /* longest mnemonic */
#define MAXLAB  16
#define E_LIMIT 32
#define P_LIMIT 64

/*      Character Constants     */
#define NEWLINE '\n'
#define TAB     '\t'
#define BLANK   ' '
#define EOS     '\0'

/*      Opcode Classes          */
#define INH     0       /* Inherent                     */
#define GEN     1       /* General Addressing           */
#define IMM     2       /* Immediate only               */
#define REL     3       /* Short Relative               */
#define P2REL   4       /* Long Relative                */
#define P1REL   5       /* Long Relative (LBRA and LBSR)*/
#define NOIMM   6       /* General except for Immediate */
#define P2GEN   7       /* Page 2 General               */
#define P3GEN   8       /* Page 3 General               */
#define RTOR    9       /* Register To Register         */
#define INDEXED 10      /* Indexed only                 */
#define RLIST   11      /* Register List                */
#define P2NOIMM 12      /* Page 2 No Immediate          */
#define P2INH   13      /* Page 2 Inherent              */
#define P3INH   14      /* Page 3 Inherent              */
#define GRP2    15      /* Group 2 (Read/Modify/Write)  */
#define LONGIMM 16      /* Immediate mode takes 2 bytes */
#define BTB     17      /* Bit test and branch          */
#define SETCLR  18      /* Bit set or clear             */
#define CPD     19      /* compare d               6811 */
#define XLIMM   20      /* LONGIMM for X           6811 */
#define XNOIMM  21      /* NOIMM for X             6811 */
#define YLIMM   22      /* LONGIMM for Y           6811 */
#define YNOIMM  23      /* NOIMM for Y             6811 */
#define FAKE    24      /* convenience mnemonics   6804 */
#define APOST   25      /* A accum after opcode    6804 */
#define BPM     26      /* branch reg plus/minus   6804 */
#define CLRX    27      /* mvi x,0                 6804 */
#define CLRY    28      /* mvi y,0                 6804 */
#define LDX     29      /* mvi x,expr              6804 */
#define LDY     30      /* mvi y,expr              6804 */
#define MVI     31      /* mvi                     6804 */
#define EXT     32      /* extended                6804 */
#define BIT     33      /* bit manipulation        6301 */
#define SYS     34      /* syscalls (really swi)        */
#define PSEUDO  35      /* Pseudo ops                   */

/* global variables */
int     Line_num =0;            /* current line number          */
int     Err_count =0;           /* total number of errors       */
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

struct link { /* linked list to hold line numbers */
       int L_num; /* line number */
       struct link *next; /* pointer to next node */
};

struct nlist { /* basic symbol table entry */
        char    *name;
        int     def;
        struct nlist *Lnext ; /* left node of the tree leaf */
        struct nlist *Rnext; /* right node of the tree leaf */ 
        struct link *L_list; /* pointer to linked list of line numbers */
};

struct oper {   /* an entry in the mnemonic table */
        char    *mnemonic;      /* its name */
        char    class;          /* its class */
        int     opcode;         /* its base opcode */
        char    cycles;         /* its base # of cycles */
};

struct  nlist *root;            /* root node of the tree */
  
FILE    *Objfil =0;             /* object file's file descriptor*/
char    Obj_name[] = {"             "};
