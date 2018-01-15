#include "konwersje.h"

#define NULL '\0'

//enum Result{OK, ERROR};

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
    
    unsigned int ucCurrentTetrad;
    int cTetradValue;
    
    pcStr[0]='0';
    pcStr[1]='x';
    for(ucCurrentTetrad=0; ucCurrentTetrad<4; ucCurrentTetrad++){
		cTetradValue=(uiValue>>(4*ucCurrentTetrad))&0xF;
		if(cTetradValue>=10){
			pcStr[5-ucCurrentTetrad]=cTetradValue-10+'A';
		}
		else{
			pcStr[5-ucCurrentTetrad]=cTetradValue+'0';
		}
    }
    pcStr[6]=NULL;	
	
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
    
    unsigned int ucCurrentChar;
    unsigned int uiCharValue;
    
	*puiValue = 0;
    if(('0'!=pcStr[0]) || ('x'!=pcStr[1])){
		return FAIL;
	}
	for(ucCurrentChar=2; !(NULL==pcStr[ucCurrentChar]); ucCurrentChar++){
		if((pcStr[ucCurrentChar] <= '9') && (pcStr[ucCurrentChar] >= '0')){
			uiCharValue=pcStr[ucCurrentChar]-'0';
			*puiValue=(*puiValue<<4)+uiCharValue;
		}
		else if((pcStr[ucCurrentChar] <= 'F') && ( pcStr[ucCurrentChar] >= 'A')){
			uiCharValue=pcStr[ucCurrentChar]-'A'+10;
			*puiValue=(*puiValue<<4)+uiCharValue;
		}
		else if((pcStr[ucCurrentChar] <= 'f') && ( pcStr[ucCurrentChar] >= 'a')){
			uiCharValue=pcStr[ucCurrentChar]-'a'+10;
			*puiValue=(*puiValue<<4)+uiCharValue;
		}
		else{
			return FAIL;
		}
	}
	if((7>ucCurrentChar) && (2<ucCurrentChar)){
		return CORRECT;
	}
	else {
		return FAIL;
	}
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcDestinationStr[ucStringIndex]);ucStringIndex++){}
    UIntToHexStr(uiValue,(&pcDestinationStr[ucStringIndex]));
}
