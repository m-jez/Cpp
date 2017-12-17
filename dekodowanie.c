#define NULL '\0'
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10

//-------------------USER DEFINE VARIABLE TYPES
typedef enum TokenType {KEYWORD, NUMBER, STRING};
typedef enum KeywordCode {LD, ST, RST};
typedef enum StringToKeywordState {TOKEN, DELIMITER}; // change name 
typedef enum ComparationResult {OK, ERROR};

typedef union TokenValue
{
	enum KeywordCode	eKeyword;
	unsigned int 		uiNumber;
	char *				pcString;
};

typedef struct TokenType
{
	enum TokenType		eType;
	union TokenValue	uValue;
}

typedef struct KeywordCode
{
	enum KeywordCode	eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
}
//-------------------USER DEFINE VARIABLES
struct Token asToken[MAX_TOKEN_NR];
struct Keyword asKeywordList[MAX_TOKEN_NR]=
{
	{RST,"reset"},
	{LD, "load"},
	{ST, "store"}
};
//-------------------GLOBAL VARIABLES
unsigned char ucTokenNr;
//-------------------FUNCTIONS DECLARATIONS
unsigned char ucFindTokenInString(char *pcString){
	
}

enum TokenType eStringToKeyword(char pcStr[], enum KeywordCode *peKewordCode){

}

void DecodeToken(void){
	
}

void DecodeMsg(char *pcString){
	
}
