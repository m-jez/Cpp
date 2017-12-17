#define NULL '\0'

enum CompResult{ DIFFERENT, EQUAL};

void CopyString(char pcSource[], char pcDestination[]){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcSource[ucStringIndex]);ucStringIndex++){
        pcDestination[ucStringIndex]=pcSource[ucStringIndex];
    }
    pcDestination[ucStringIndex]=NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
    
    enum CompResult eCompResult = DIFFERENT;
    unsigned char ucStringIndex; 
    
    for(ucStringIndex=0;(pcStr1[ucStringIndex]==pcStr2[ucStringIndex]);ucStringIndex++){
        if(NULL==pcStr1[ucStringIndex]){
            eCompResult=EQUAL};
            break;
        }
    }
    return eCompResult;
}

void AppednString(char pcSourceStr[], char pcDestinationStr[]){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcDestinationStr[ucStringIndex]);ucStringIndex++){}
    CopyString(pcSourceStr,&pcDestinationStr[ucStringIndex]);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
    
    unsigned char ucStringIndex;
    
    for(ucStringIndex=0;!(NULL==pcString[ucStringIndex]);ucStringIndex++){
        if(cOldChar==pcString[ucStringIndex]){
            pcString[ucStringIndex]=cNewChar;
        }
    }
}
