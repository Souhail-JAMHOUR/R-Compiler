#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.c"

typedef enum {TPROG, TCONST, TVAR}TSYM;

typedef struct {
    char NOM[20];
    TSYM TIDF;
}T_TAB_IDF ;

T_TAB_IDF TAB_IDFS[100];
int test_double_declaration;
int indice_TAB_IDFS = 0;
void ajouter_idf(char *nom , TSYM type);
int chercher_idf(char *nom);


void INST();
void INSTS();
void INSTF();
void SEP();
void SI();

void SINON();
void CONSTS();
void VARS();
void AFFECT();
void TANTQUE();
void POUR();
void ECRIRE();
void ID();
void AFTERID();
void LIRE();
void AFFEC();
void AFFECF();
void EXPR();
void EXPRF();
void ARGUMENTS();
void ARGUMENT();
void ADDOP();
void CONDS();
void SINONF();
void BOUCLEFOR();
void STRING();
void COND();
void TOREAD();
void CONDSF();
void RELOP();
void ELOGIQUE();
void TERM();
void TERMF();
void FACT();
void MULOP();

void STRINGF();
void BOUCLEFORF();
void CHIFFRE();
void LETTRE();




int main(){
    
   
    Ouvrir_Fichier("R.r");
    Lire_Caractere(); 

  	Sym_Suiv();  
     
  	        
    INSTS();
    if(sym.CODE==EOF_TOKEN){
        printf("Correct");
    }else{
        printf("Not Correct");
    }

    
    return 1;
}

void INSTS(){
    
     switch (sym.CODE) {
        case PV_TOKEN:
            Sym_Suiv();
            INST();
            INSTF();
            break;
        case RL_TOKEN:
            Sym_Suiv();
            INST();
            INSTF();
            break;
        default:
        INST();
        break;
    }
}
void INSTF(){
    
    switch (sym.CODE) {
    case BO_TOKEN:
        INSTS();
        Test_Symbole(BF_TOKEN, ERR_BF);
        break;
    case RL_TOKEN:
        INSTS();
        Sym_Suiv();
        break;
    case PV_TOKEN:
        
        INSTS();
        break;
    default:
    
    break;
    }
}
void INST(){
    
     switch (sym.CODE) {
            case IF_TOKEN:
                SI();
                break;
            case ELSE_TOKEN:
                SINON();
                break;
            case WHILE_TOKEN:

                TANTQUE();
                break;
            case FOR_TOKEN:
  
                POUR();
                break;
            case PRINT_TOKEN:
    
                ECRIRE();
                break;
            case READ_TOKEN:
    
                LIRE();
                break;
            case CAT_TOKEN:
    
                ECRIRE();
                break;
            case ID_TOKEN:
                Sym_Suiv();
             
                AFTERID();
                break;
            default:
                break ;
    }  
    
}
void AFTERID(){
    switch (sym.CODE) {
        case READ_TOKEN:
            //Sym_Suiv();
            LIRE();
            break;
        case AFF_TOKEN:
            
            AFFEC();
            break;
        case EG_TOKEN:
            Sym_Suiv();
            AFTERID();
            break;    
        default:
            break;
    }    
}
void AFFEC(){
    Test_Symbole(AFF_TOKEN, ERR_AFFECT);
    AFFECF();
}
void AFFECF(){
    
    switch (sym.CODE) {
        case FUNCTION_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            ARGUMENTS();
            Test_Symbole(PF_TOKEN, ERR_PF);
            break;
        case DQUOTE_TOKEN:
            Test_Symbole(DQUOTE_TOKEN, ERR_DQUOTE);
            EXPR();
            Test_Symbole(DQUOTE_TOKEN, ERR_DQUOTE);
            break;
        default:
        
        Sym_Suiv();
        
            EXPR();
            break;
    }
}
void SI(){
    
    switch (sym.CODE) {
        case IF_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            CONDS();
            Test_Symbole(PF_TOKEN, ERR_PF);
            Test_Symbole(BO_TOKEN, ERR_BO);
            INSTS();
            
            Test_Symbole(BF_TOKEN, ERR_BF);
            if(sym.CODE==ELSE_TOKEN){
                INSTS();
            }
            
            break;
        default:
            break;
    }
    
}
void SINON(){
    switch (sym.CODE) {
        case ELSE_TOKEN:
            Sym_Suiv();
            SINONF();
            break;
        default:
            printf("SINON");
    }
}
void SINONF(){
    switch (sym.CODE) {
        case BO_TOKEN:
            Sym_Suiv();
            INSTS();
            Test_Symbole(BF_TOKEN, ERR_BF);
            break;
        case IF_TOKEN:
            Sym_Suiv();
            SI ();
        default:
            printf("SINONF\n");
    }
}
void POUR(){
    switch (sym.CODE) {
        case FOR_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            BOUCLEFOR();
            Test_Symbole(PF_TOKEN, ERR_PF);
            Test_Symbole(BO_TOKEN, ERR_BO);
            INSTS();
            Test_Symbole(BF_TOKEN, ERR_BF);
            break;
        default:
            printf("POUR");
    }

}
void TANTQUE(){
    switch (sym.CODE) {
        case WHILE_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            CONDS();
            Test_Symbole(PF_TOKEN, ERR_PF);
            Test_Symbole(BO_TOKEN, ERR_BO);
            INSTS();
            Test_Symbole(BF_TOKEN, ERR_BF);
            break;
        default:
            printf("TANTQUE");
    }
}
void ECRIRE(){
    switch (sym.CODE) {
        case CAT_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            STRING();
            Test_Symbole(PF_TOKEN, ERR_PF);
            break;
        case PRINT_TOKEN:
            Sym_Suiv();
            Test_Symbole(PO_TOKEN, ERR_PO);
            STRING();
            Test_Symbole(PF_TOKEN, ERR_PF);
            break;
        default:
            printf("ECRIRE");
    }
    
}
void LIRE(){
   
    switch (sym.CODE) {
        case EG_TOKEN:
            Sym_Suiv();
         
            if(sym.CODE==READ_TOKEN){
                Sym_Suiv();
                Test_Symbole(PO_TOKEN, ERR_PO);
                TOREAD();
                Test_Symbole(PF_TOKEN, ERR_PF);
            }
            break;
    }
}
void TOREAD(){
    switch (sym.CODE) {
        case PROMPT_TOKEN:
            Sym_Suiv();
            if(sym.CODE==EG_TOKEN){
                Sym_Suiv();
                if(sym.CODE==DQUOTE_TOKEN){
                    Sym_Suiv();
                    EXPR();
                    Test_Symbole(DQUOTE_TOKEN, ERR_DQUOTE);
                }
            }
            break;
        case DQUOTE_TOKEN:
            Sym_Suiv();
            EXPR();
            Test_Symbole(DQUOTE_TOKEN, ERR_DQUOTE);
            break;
        default:printf("TOREAD \n");break;
    }
}
void COND(){
    EXPR();
    RELOP();
    EXPR();
}
void CONDS(){
    COND();
    CONDSF();
}
void CONDSF(){
    switch (sym.CODE) {
        case ANDLOGIC_TOKEN:
            Sym_Suiv();
            CONDS();
            break;
        case ORLOGIC_TOKEN:
            Sym_Suiv();
            CONDS();
            break;
        default:
            printf("CONDSF");
    }
    

}
void RELOP(){
    switch (sym.CODE) {
        case DEG_TOKEN:
            Sym_Suiv();
            break;
        case NON_EG_TOKEN:
            Sym_Suiv();
            break;
        case INF_TOKEN:
            Sym_Suiv();
            break;
        case SUP_TOKEN:
            Sym_Suiv();
            break;
        case INF_OR_EG_TOKEN:
            Sym_Suiv();
            break;
        case SUP_OR_EG_TOKEN:
            Sym_Suiv();
            break;        
        default:
            break;
    }
}
void EXPR() {
    TERM();
    EXPRF();
}
void EXPRF(){
    switch (sym.CODE) {
        case PLUS_TOKEN:
            Sym_Suiv();
            EXPR();
            break;
        case MINUS_TOKEN:
            Sym_Suiv();
            EXPR();
            break;
        default:
            break;
    }
    
}
void ADDOP(){
    switch (sym.CODE) {
        case PLUS_TOKEN:
            Sym_Suiv();
            break;
        case MINUS_TOKEN:
            Sym_Suiv();
            break;
        default:
            printf("ADDOP");
    }
}
void TERM(){
    FACT();
    TERMF();

}
void TERMF(){
    switch (sym.CODE) {
        case MULT_TOKEN:
            Sym_Suiv();
            TERM();
            break;
        case DIV_TOKEN:
            Sym_Suiv();
            TERM();
            break;
        default:
            break;
    }
    
}
void MULOP(){
    switch (sym.CODE) {
        case MULT_TOKEN:
            Sym_Suiv();
            break;
        case DIV_TOKEN:
            Sym_Suiv();
            break;
        default:
            break;
    }
}
void FACT(){
    
    switch (sym.CODE) {
        case ID_TOKEN:
            Sym_Suiv();
            FACT();
            break;
        case NUM_TOKEN:
            Sym_Suiv();
            FACT();
            break;
        case PO_TOKEN:
            Sym_Suiv();
            EXPR();
            Test_Symbole(PF_TOKEN, ERR_PF);
            break;
        case BF_TOKEN:
            //Sym_Suiv();
            //Test_Symbole(BF_TOKEN, ERR_BF);
            //EXPR();
            break;      
        default:
            break;
    }
}
void ARGUMENTS(){
    ARGUMENT();
}
void ARGUMENT(){
    STRING();
}
void STRING(){
    switch (sym.CODE) {
        case DQUOTE_TOKEN:
            Sym_Suiv();
            EXPR();
            Test_Symbole(DQUOTE_TOKEN, ERR_DQUOTE);
            STRINGF();
            break;
        case ID_TOKEN:
            Sym_Suiv();
            STRINGF();
            break;
        case NUM_TOKEN:
            Sym_Suiv();
            STRINGF();
            break;
        default:printf("STRING\n");break;
    }
}
void STRINGF(){
    
    switch (sym.CODE) {
        case VIR_TOKEN:
            Sym_Suiv();
            STRING();
            break;
        default:
        break;
    }
}
void BOUCLEFOR(){
    switch (sym.CODE) {
    case ID_TOKEN:
        Sym_Suiv();
        if(sym.CODE==IN_TOKEN){
            Sym_Suiv();
            BOUCLEFORF();
        }
    default:printf("BOUCLEFOR\n");break;
    }
}
void BOUCLEFORF(){
    
    switch (sym.CODE) {
    case ID_TOKEN:
        Sym_Suiv();
        break;
    case NUM_TOKEN:
        Sym_Suiv();
        if(sym.CODE==DP_TOKEN){
            Sym_Suiv();
            if(sym.CODE==NUM_TOKEN){
                printf("BOUCLEFOR\n");
                Sym_Suiv();
                break;
            }
        }else{
            printf("BOUCLEFORF_ERR\n");
        }
    default:printf("BOUCLEFOR_ERR_ERR\n");break;
    }
}



