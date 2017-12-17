#define NULL '\0'

enum Result{OK, ERROR};

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
    
    unsigned char ucCurrentTetrad;
    char cTetradValue;
    
    pcStr[0]='0';
    pcStr[1]='x';
    for(ucCurrentTetrad=0;4>ucCurrentTetrad;ucCurrentTetrad++){				// KONWENCJA
        cTetradValue = ((uiValue >> ((5-ucCurrentTetrad) * 0xF)) & 0xF); 
        if(cTetradValue < 10){
            pcStr[ucCurrentTetrad] = '0' + cTetradValue;
        }
        else{
            pcStr[ucCurrentTetrad] = 'A' + cTetradValue - 10;
        }
    }
    pcStr[ucCurrentTetrad]=NULL;
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
    
    unsigned char ucCurrentChar;
    unsigned int uiCharValue;
    
    if(('0'!=pcStr[0])||('x'!=pcStr[1])){
		return ERROR;
	}
	for(ucCurrentChar=0;!(NULL==pcStr[ucCurrentChar]);ucCurrentChar++){				//KONWENCJA
		if(pcStr[ucCurrentChar]<'A'){
			uiCharValue=uiCharValue+((pcStr[ucCurrentChar]-'0')&0xF);
			*puiValue=(*puiValue<<4)+uiCharValue;
		}
		else{
			uiCharValue=uiCharValue+10+((pcStr[ucCurrentChar]-'A')&0xF);
			*puiValue=(*puiValue<<4)+uiCharValue;
		}
	}
	if((8>ucCurrentChar)&&(3<ucCurrentChar)){
		return OK;
	}
	else {
		*puiValue = 0;
		return ERROR;
	}
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcDestinationStr[ucStringIndex]);ucStringIndex++){}
    UIntToHexStr(uiValue,(&pcDestinationStr[ucStringIndex]));
}

int main(){
	
	char znak[] = "0x44";
	unsigned int liczba;
	unsigned int * wskaznik = &liczba;
	
	eHexStringToUInt(znak,  wskaznik);
	printf("%02x", liczba);
}
