#define NULL '\0'

enum Result{OK, ERROR};

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
    
    unsigned int ucCurrentTetrad;
    int cTetradValue;
    
    pcStr[0]='0';
    pcStr[1]='x';
    for(ucCurrentTetrad=0; ucCurrentTetrad<4; ucCurrentTetrad++){
		cTetradValue=(uiValue >> (4 * (3-ucCurrentTetrad))) & 0xF;
		if(cTetradValue>10){
			pcStr[ucCurrentTetrad+2]=cTetradValue-10+'A';
		}
		else{
			pcStr[ucCurrentTetrad+2]=cTetradValue+'0';
		}
    }
    pcStr[ucCurrentTetrad+2]=NULL;
	
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
    
    unsigned int ucCurrentChar;
    unsigned int uiCharValue;
    
    if(('0'!=pcStr[0]) || ('x'!=pcStr[1])){
		return ERROR;
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
			return ERROR;
		}
	}
	if((7>ucCurrentChar) && (2<ucCurrentChar)){
		return OK;
	}
	else {
		return ERROR;
	}
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcDestinationStr[ucStringIndex]);ucStringIndex++){}
    UIntToHexStr(uiValue,(&pcDestinationStr[ucStringIndex]));
}
