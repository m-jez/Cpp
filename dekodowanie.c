#include <stdio.h>	//	ONLY
#ifdef NULL			//	FOR
	#undef NULL		//	TESTING
#endif //NULL		//	!!!
#include "operacjeproste.h"
#include "konwersje.h"

#define MAX_TOKEN_NR            3            
#define MAX_KEYWORD_NR          3
#define MAX_KEYWORD_STRING_LTH 10            
#define NULL                 '\0'
#define SPACE 			     ' '

enum TokenStatus {TOKEN, DELIMITER};
enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {LD, ST, RST};
//enum ComparationResult {OK, ERROR};  // CompResult form operacjeproste.h

struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

union TokenValue{
	enum KeywordCode eKeyword;			 
	unsigned int uiNumber;     
	char * pcString;           
};
	
struct Token{
	enum TokenType eType;    		
	union TokenValue uValue;			
};

struct Keyword asKeywordList[MAX_KEYWORD_NR]= 
{
	{RST,"reset"},	
	{LD, "load" },
	{ST, "store"}
};

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

unsigned char ucFindTokensInString(char *pcString){

	unsigned char ucCharIndex;
	char cCurrentChar;
	enum TokenStatus eState=DELIMITER;
	
    for (ucCharIndex=0; ;ucCharIndex++){
		cCurrentChar=pcString[ucCharIndex];
		switch (eState){
			case TOKEN:
				if((cCurrentChar==NULL)||(ucTokenNr==MAX_TOKEN_NR)){
					return ucTokenNr;
				}
				else if(cCurrentChar==SPACE){
					eState=DELIMITER;
				}
				break;
			case DELIMITER:
				if (cCurrentChar==NULL){
					return ucTokenNr;
				}
				else if (!(cCurrentChar==SPACE)){
					asToken[ucTokenNr].uValue.pcString=&pcString[ucCharIndex];
					eState=TOKEN;
					ucTokenNr++;
				}
				break;
		}
	}
}

enum CompResult eStringToKeyword(char cStr[], enum KeywordCode *peKeyword){

	unsigned char ucKeywordIndex, ucCharIndex;
	for(ucKeywordIndex=0;ucKeywordIndex<MAX_KEYWORD_NR;ucKeywordIndex++){
		if(eCompareString(cStr, asKeywordList[ucKeywordIndex].cString) == OK ){
			*peKeyword=asKeywordList[ucKeywordIndex].eCode;
			return OK;
		}
	}
	return ERROR;
}   

void DecodeTokens(void)
{
    unsigned char ucTokenNumberCounter;
    char *cCurrentToken;
    enum KeywordCode peKeywordCode;
    unsigned int uiValue;
    enum TokenType eType;
    union TokenValue uValue;

    for(ucTokenNumberCounter=0; ucTokenNumberCounter<ucTokenNr; ucTokenNumberCounter++)
    {
        cCurrentToken=asToken[ucTokenNumberCounter].uValue.pcString;
        if(eStringToKeyword(cCurrentToken, &peKeywordCode)==OK)
        {
            eType=KEYWORD;
            uValue.eKeyword=peKeywordCode;
        }
        else if(eHexStringToUInt(cCurrentToken,&uiValue)==OK)
        {
            eType=NUMBER;
            uValue.uiNumber=uiValue;
        }
        else
        {
            eType=STRING;
            uValue.pcString=cCurrentToken;
        }
        asToken[ucTokenNumberCounter].eType=eType;
        asToken[ucTokenNumberCounter].uValue=uValue;
    }
}
///////////////////////////////////////////////////////////////////////////////

void DecodeMsg(char *pcString)
{
    ucTokenNr = ucFindTokensInString (pcString);
    ReplaceCharactersInString(pcString,' ','\0');
    DecodeTokens();
}

/*//------------------------------------------------------------------------------------
//		ucFindTokensInString TEST
int main(void){
	
	int x;
	// #1 - Only spaces in string
	//char Str[]="           ";
	// #2 - Delimiter before first char
	//char Str[]=" Hi MJ :)";
	// #3 - More than 1 delimiter beetwen 2 tokens
	char Str[]="Hi   TJ :)";
	char *ptStr;
	ptStr = &Str[5];
	
	printf("Sending string: '%s' to function ucFindTokensInString\n", Str);
	ucFindTokensInString(Str);
	printf("Number of tokens: %d\n", ucTokenNr);
	return 0;
}*/

/*//------------------------------------------------------------------------------------
//		eStringToKeyword TEST
int main(void){
	
	char cToken[]="reset";
	enum KeywordCode eKeyWordResult;
	if(eStringToKeyword(cToken, &eKeyWordResult)==OK){
		switch(eKeyWordResult){
						case LD:
							printf("Result: load\n");
							break;
						case ST:
							printf("Result: store\n");
							break;
						case RST:
							printf("Result: reset\n");
							break;
						default:
							printf("Result: none\n");
							break;
					}
	}
	return 0;
}*/


//------------------------------------------------------------------------------------
//		DecodeMsg	TEST
int main(void){
	
	char Str[] = "reset load store 0x0064 siema";
	unsigned char ucTokenIndex;
	
	printf("\nDecoding string '%s'\n\n", Str);
	DecodeMsg(Str);
	for(ucTokenIndex=0; ucTokenIndex < MAX_TOKEN_NR; ucTokenIndex++){
		printf("Token number %i:\n", ucTokenIndex);
		switch(asToken[ucTokenIndex].eType){
			case KEYWORD:
				printf("\tType KEYWORD | Code ");
				switch(asToken[ucTokenIndex].uValue.eKeyword){
					case LD:
						printf("LD\n");
						break;
					case ST:
						printf("ST\n");
						break;
					case RST:
						printf("RST\n");
						break;
				}
				break;
			case NUMBER:
				printf("\tType NUMBER | Value: %i\n", asToken[ucTokenIndex].uValue);
				break;
			case STRING:
				printf("\tType STRING | TEXT: %s\n", asToken[ucTokenIndex].uValue);
				break;
		}
	}	
	printf("\n\t### END OF TEST ###\n\n");
	return 0;
}
