*
*	    Copined from:
*	    MEK6802D5 Microcomputer Evaluation Board User's Manual
*	    Page 3-8
*
*	    Assemble with the following command:
*		as0 used5.asm -l cre c s
*
        nam     used5
*       Options set in file override command line option settings
*        opt     c       * options must be in lower case
        org     $0
disbuf  equ     $e41d
diddle  equ     $f0a2
mnptr   equ     $e419
put     equ     $f0bb
*
beg     ldaa    #$3e
        staa    disbuf
        ldaa    #$6d
        staa    disbuf+1
        ldaa    #$79
        staa    disbuf+2
        ldaa    #$00
        staa    disbuf+3
        ldaa    #$5e
        staa    disbuf+4
        ldaa    #$6d
        staa    disbuf+5
        ldaa    #diddle
        stx     mnptr
        jmp     put
        end
