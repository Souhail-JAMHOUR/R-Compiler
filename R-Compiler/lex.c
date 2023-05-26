#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {ID_TOKEN, NUM_TOKEN, SINONSI_TOKEN, SINON_TOKEN, ANDLOGIC_TOKEN, ORLOGIC_TOKEN,DEG_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN,
WRITE_TOKEN, PV_TOKEN, PT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, MULT_TOKEN, AFF_TOKEN, INF_TOKEN, INF_OR_EG_TOKEN, SUP_TOKEN, SUP_OR_EG_TOKEN, PO_TOKEN, PF_TOKEN,
NON_EG_TOKEN, FIN_TOKEN, EOF_TOKEN, EG_TOKEN, ERREUR_TOKEN, ELSE_TOKEN, FOR_TOKEN, TO_TOKEN, DOWNTO_TOKEN, FUNCTION_TOKEN, IN_TOKEN, PRINT_TOKEN,AO_TOKEN,AF_TOKEN,APPEND_TOKEN,
LENGTH_TOKEN,BO_TOKEN,BF_TOKEN,DQUOTE_TOKEN, COMMENT_TOKEN,SQUOTE_TOKEN,RL_TOKEN,CAT_TOKEN,DIV_TOKEN,DP_TOKEN,VIR_TOKEN,PROMPT_TOKEN,CHIFFRE_TOKEN} 
CODES_LEX;

char caracteres_speciaux[] = {';', ' ', ',', '=', ':', '*', '/', '-', '+', '.','{','}', '<', '>','"','\'', '(', ')','[',']','#', '\t'};

typedef enum {ERR_IN,ERR_CAR_INC,ERR_DBLDEC, ERR_FICH_VID, ERR_ID_LONG, ERR_PROGRAM, ERR_PV, ERR_PT, ERR_EG, ERR_NUM, ERR_CONST_VAR_BEGIN, ERR_BF, ERR_VAR_ID, ERR_BO, ERR_AFFECT, ERR_PF, ERR_FACT, ERR_PO, ERR_ID_READ, ERR_THEN, ERR_DO, ERR_FOR, ERR_TO_DOWNTO, ERR_TO_DOWNTO_LIMIT, ERR_FOR_START,
ERR_PROGRAM_ID, ERR_READ, ERR_DQUOTE, ERR_DP}	
ERREURS;

typedef struct {
    CODES_LEX CODE;
    char *NOM;
}Symbole;
typedef struct {
    ERREURS CODE_ERR;
    char mes[40];
}Erreurs;

Erreurs MES_ERR[100] = {{ERR_DP, "DP ERROR"},{ERR_IN, "IN ERROR"},{ERR_READ, "READLINE ERROR"},{ERR_CAR_INC, "Caractere inconnu"},{ERR_DBLDEC,"double déclaration"}, {ERR_FICH_VID, "Fichier vide"}, {ERR_ID_LONG, "Identifiant tres long"},
{ERR_PROGRAM, "Erreur program"}, {ERR_PV, "Erreur PV"}, {ERR_PT, "Erreur PT"}, {ERR_EG, "Erreur EG"}, {ERR_NUM, "Erreur NUM"}, {ERR_CONST_VAR_BEGIN, "Erreur_const_var_begin"},
{ERR_BF, "Erreur_bracket_fermente"}, {ERR_VAR_ID, "Erreur_var_id"}, {ERR_BO, "Erreur_Bracket_ouvrante"},
{ERR_AFFECT, "Erreur_affectation"}, {ERR_PF, "Erreur_parenthese_fermente"}, {ERR_FACT, "Erreur_facteur"}, {ERR_PO, "Erreur_parenthese_ouvrante"},
{ERR_ID_READ, "Erreure_Lire_ID"}, {ERR_THEN, "Erreur_then"}, {ERR_DO, "Erreur_Do"}, {ERR_FOR, "Erreur_For_ID"}, {ERR_TO_DOWNTO, "Erreur_To_DownTo"},
{ERR_TO_DOWNTO_LIMIT, "Erreur_To_DownTo_Limit"}, {ERR_DQUOTE, "ERREUR QUOTES"}, {ERR_FOR_START, "Erreur_For_Start"}, {ERR_PROGRAM_ID, "Erreur_Program_ID"}};


Symbole sym;
char Car_Cour;
FILE *f;
void Sym_Suiv();
void Lire_mot();
void Lire_nombre();
char Lire_Caractere();
int verifier_Caractere(char car);
void Ouvrir_Fichier(char *fichier);
void AfficherToken(Symbole symbole);
Symbole Test_Symbole(CODES_LEX cl, ERREURS code_err);

void Ouvrir_Fichier(char *fichier){
    f = fopen(fichier, "r");
    if(f == NULL) {
        printf("%s\n",MES_ERR[ERR_FICH_VID].mes);
        fclose(f);
    }
}

Symbole Test_Symbole(CODES_LEX cl, ERREURS code_err){
  //AfficherToken(sym);
    
    if(sym.CODE == cl){
        Sym_Suiv();
        return sym ;
    }
    else{
        printf("%s\n",MES_ERR[code_err].mes);
        exit(0);
    }
}

int verifier_Caractere(char car){
    for (int i = 0 ; i < sizeof(caracteres_speciaux) ; i++){
        if(car == caracteres_speciaux[i]) return 1;
    }
    return 0;
}


char Lire_Caractere(){
    if(f != NULL){
        Car_Cour = fgetc(f);
       

    }
    else 
        Car_Cour = EOF;   
}

void Lire_nombre(){
    char nombre_cour[21];
    int i = 0;
    while(i < 20 && !verifier_Caractere(Car_Cour)){
    	
        nombre_cour[i] = Car_Cour;
        Lire_Caractere();
        
        i++;
    }
    if(i == 21) {
      
        printf("%s\n",MES_ERR[ERR_ID_LONG].mes);
    
    }
    nombre_cour[i] = '\0';
    sym.CODE = NUM_TOKEN;
    sym.NOM = "NUM_TOKEN";
}




void Lire_mot(){
    char mot_cour[21];
    int i = 0;
    while(i < 20 && !verifier_Caractere(Car_Cour)) {

        mot_cour[i] = Car_Cour;
        Lire_Caractere();
        i++;
    }
    if(i == 21) {
        
        printf("%s\n",MES_ERR[ERR_ID_LONG].mes);
        
    }
    mot_cour[i] = '\0';
    
    
    if(strstr(mot_cour, "function") != NULL){
        sym.CODE = FUNCTION_TOKEN;
        sym.NOM = "FUNCTION_TOKEN";
    }
    else if(strcmp(mot_cour, "while") == 0){
        sym.CODE = WHILE_TOKEN;
        sym.NOM = "WHILE_TOKEN";
    }
    
    else if(strcmp(mot_cour, "if") == 0){
        sym.CODE = IF_TOKEN;
        sym.NOM = "IF_TOKEN";
    }
    else if(strcmp(mot_cour, "for") == 0){
        sym.CODE = FOR_TOKEN;
        sym.NOM = "FOR_TOKEN";
    }
    else if(strcmp(mot_cour, "in") == 0){
        sym.CODE = IN_TOKEN;
        sym.NOM = "IN_TOKEN";
    }
    else if(strcmp(mot_cour, "else") == 0){
        sym.CODE = ELSE_TOKEN;
        sym.NOM = "ELSE_TOKEN";
    }
    else if(strcmp(mot_cour, "print") == 0){
        sym.CODE = PRINT_TOKEN;
        sym.NOM = "PRINT_TOKEN";
    }
    else if(strcmp(mot_cour, "cat") == 0){
        sym.CODE = CAT_TOKEN;
        sym.NOM = "CAT_TOKEN";
    }

    else if(strcmp(mot_cour, "readline") == 0){						// scan
        sym.CODE = READ_TOKEN;
        sym.NOM = "READ_TOKEN";
    }
    else if(strcmp(mot_cour, "append") == 0){
        sym.CODE = APPEND_TOKEN;
        sym.NOM = "APPEND_TOKEN";
    }
    else if(strcmp(mot_cour, "length") == 0){
        sym.CODE = LENGTH_TOKEN;
        sym.NOM = "LENGTH_TOKEN";
    }else if(strcmp(mot_cour, "prompt") == 0){
        sym.CODE = PROMPT_TOKEN;
        sym.NOM = "PROMPT_TOKEN";
    }
    
    else {
        sym.CODE = ID_TOKEN;
        sym.NOM = "ID_TOKEN";
    }
}


void Sym_Suiv(){
    AfficherToken(sym);
    while(Car_Cour == ' ' || Car_Cour == '\t' ){
        Lire_Caractere();
    }
    if((Car_Cour >= 'a' && Car_Cour <= 'z') || (Car_Cour >= 'A' && Car_Cour <= 'Z')){
        Lire_mot();
    }
    else if(Car_Cour >= '0' && Car_Cour <= '9'){
        Lire_nombre();
    }
    else{
    	
        switch(Car_Cour){
            case '\'' :
            	sym.CODE = SQUOTE_TOKEN;
                sym.NOM = "SQUOTE_TOKEN";
                Lire_Caractere();
                break;
            case '#' :
            	sym.CODE = COMMENT_TOKEN;
                sym.NOM = "COMMENT_TOKEN";
                Lire_Caractere();
                break;
            case ';' : 
                sym.CODE = PV_TOKEN;
                sym.NOM = "PV_TOKEN";
                Lire_Caractere();
                break;
            case '.' : 
                sym.CODE = PT_TOKEN;
                sym.NOM = "PT_TOKEN";
                Lire_Caractere();
                break; 
            case '+' : 
                sym.CODE = PLUS_TOKEN;
                sym.NOM = "PLUS_TOKEN";
                Lire_Caractere();
                break;
            case '-' : 
                sym.CODE = MINUS_TOKEN;
                sym.NOM = "MINUS_TOKEN";
                Lire_Caractere();
                break;
            case '*' : 
                sym.CODE = MULT_TOKEN;
                sym.NOM = "MULT_TOKEN";
                Lire_Caractere();
                break;
            case '/' : 
                sym.CODE = DIV_TOKEN;
                sym.NOM = "DIV_TOKEN";
                Lire_Caractere();
                break;
            case ',' : 
                sym.CODE = VIR_TOKEN;
                sym.NOM = "VIR_TOKEN";
                Lire_Caractere();
                break;
            case '"' : 
                sym.CODE = DQUOTE_TOKEN;
                sym.NOM = "DQUOTE_TOKEN";
                Lire_Caractere();
                break;       
            case '(' : 
                sym.CODE = PO_TOKEN;
                sym.NOM = "PO_TOKEN";
                Lire_Caractere();
                break; 
            case ')' : 
                sym.CODE = PF_TOKEN;
                sym.NOM = "PF_TOKEN";
                Lire_Caractere();
                break; 
            case '[' : 
                sym.CODE = AO_TOKEN;
                sym.NOM = "AO_TOKEN";
                Lire_Caractere();
                break;
            case ']' : 
                sym.CODE = AF_TOKEN;
                sym.NOM = "AF_TOKEN";
                Lire_Caractere();
                break;
            case '{' : 
                sym.CODE = BO_TOKEN;
                sym.NOM = "BO_TOKEN";
                Lire_Caractere();
                break;
            case '}' : 
                sym.CODE = BF_TOKEN;
                sym.NOM = "BF_TOKEN";
                Lire_Caractere();
                break;        
            case '=' : 
            	Lire_Caractere();
            	if (Car_Cour == '=')							// ==
            	{
            		sym.CODE = EG_TOKEN;
                	sym.NOM = "EG_TOKEN"; 
                	Lire_Caractere();
            	}
                
                break;  
            
            case '<' :
                Lire_Caractere();
                if(Car_Cour == '-'){							// <-
                    sym.CODE = AFF_TOKEN;
                    sym.NOM = "AFF_TOKEN";
                    Lire_Caractere();
                }
                else if(Car_Cour == '='){						// <=
                    sym.CODE = INF_OR_EG_TOKEN;
                    sym.NOM = "INF_OR_EG_TOKEN";
                    Lire_Caractere();
                }
                else {											// <
                    sym.CODE = INF_TOKEN;
                    sym.NOM = "INF_TOKEN";
                }
                break;
            case '>' :
                Lire_Caractere();
                if(Car_Cour == '='){							// >=
                    sym.CODE = SUP_OR_EG_TOKEN;
                    sym.NOM = "SUP_OR_EG_TOKEN";
                    Lire_Caractere();
                }
                else {											// >
                    sym.CODE = SUP_TOKEN;
                    sym.NOM = "SUP_TOKEN";
                }  
                break;
            case '\n' :
            	sym.CODE = RL_TOKEN;
                sym.NOM = "RL_TOKEN";
                Lire_Caractere();
                break;
            case ':' :
            	sym.CODE = DP_TOKEN;
                sym.NOM = "DP_TOKEN";
                Lire_Caractere();
                break;  
            case EOF:
                sym.CODE = EOF_TOKEN;
                sym.NOM = "EOF_TOKEN";
                break;
            default :
                printf("%s\n",MES_ERR[ERR_CAR_INC].mes);
                break;      
        }
    }
}
void AfficherToken(Symbole symbole){
    printf("%s\n", symbole.NOM);

}

/*int main(){
  Ouvrir_Fichier("test.txt");  
  Lire_Caractere();  
  while (Car_Cour!=EOF) {  

  	Sym_Suiv();  
  	AfficherToken(sym);   
  } 
  getchar();  
  return 1; 
} */