#include <stdio.h>	//	ONLY
#ifdef NULL			//	FOR
	#undef NULL		//	TESTING
#endif //NULL		//	!!!

#define MAX_TOKEN_NR            3            
#define MAX_KEYWORD_NR          3
#define MAX_KEYWORD_STRING_LTH 10            
#define NULL                 '\0'
#define SPACE 			     ' '

enum TokenStatus {TOKEN, DELIMITER};
enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {LD, ST, RST};
enum ComparationResult {OK, ERROR};

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
					ucTokenNr++;
					asToken[ucTokenNr].uValue.pcString=&pcString[ucCharIndex];
					eState=TOKEN;
				}
				break;
		}
    }
}
// ongoing
enum ComparationResult eStringToKeyword(char cStr[], enum KeywordCode *peKeyword){

	unsigned char ucKeywordIndex, ucCharIndex;

	for(ucKeywordIndex=0;ucKeywordIndex<MAX_KEYWORD_NR;ucKeywordIndex++){
		printf("ucKeywordIndex: %d\n", ucKeywordIndex);
		for(ucCharIndex=0; cStr[ucCharIndex]==asKeywordList[ucKeywordIndex].cString[ucCharIndex]; ucCharIndex++){
			printf("\tcStr: %c | cString: %c\n", cStr[ucCharIndex], asKeywordList[ucKeywordIndex].cString[ucCharIndex]);
			if(NULL==cStr[ucCharIndex]){
				peKeyword = &asKeywordList[ucKeywordIndex].eCode;	// nie przypisuje wartości do wskaznika
				printf("\tOK\n");
				switch(*peKeyword){
					case 0:
						printf("\t*peKeyword: load\n");
						break;
					case 1:
						printf("\t*peKeyword: store\n");
						break;
					case 2:
						printf("\t*peKeyword: reset\n");
						break;
				}
				printf("\t%d\n", *peKeyword);
				return OK;
			}
		}
	}
	printf("\tERROR\n");
	return ERROR;
}   

/*void DecodeTokens(void){

	unsigned char ucTokenCtr;

	for (ucTokenCtr=0; ucTokenCtr < ucTokenNr ; ucTokenCtr ++ ) {
		KeywordCode eKeywordCode;
		unsigned int uiNumberValue;
		Token * pasToken;
		pasToken = &asToken[ucTokenCtr];

		if (eStringToKeyword(pasToken ->uValue.pcString, &eKeywordCode) == OK) {
			pasToken->eType = KEYWORD;
			pasToken->uValue.eKeyword = eKeywordCode;
		}
		else if (eHexStringToUInt(pasToken ->uValue.pcString, &uiNumberValue) == OK) {
			pasToken->eType = NUMBER;
			pasToken->uValue.uiNumber = uiNumberValue;
		}
		else {
			pasToken ->eType = STRING;
		}
	}
}

void DecodeMsg(char *cStr) {
	ucFindTokensInString(cStr);
	ReplaceCharactersInString(cStr,SPACE,NULL);
	DecodeTokens();
}*/

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

//------------------------------------------------------------------------------------
//
int main(void){
	
	char c[]="reset";
	enum KeywordCode *pt;
	
	printf("\n***%d***\n", *pt);
	if(eStringToKeyword(c, pt)==OK){
		switch(*pt){
						case 0:
							printf("\t*pt: load\n");
							break;
						case 1:
							printf("\t*pt: store\n");
							break;
						case 2:
							printf("\t*pt: reset\n");
							break;
						default:
							printf("\t*pt: none\n");
							break;
					}
	}
	printf("\n***%d***\n", *pt);
	return 0;
}
