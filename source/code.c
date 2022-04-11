#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
char* trim(char *line);
char fonksiyonTipi[100];
char fonksiyonAdi[100];
void calismaSuresiniBul(){
            FILE *rfile=fopen("code.txt","r");
            FILE *wfile=fopen("code.c","w");
            char line[1000];
            while(fgets(line,sizeof(line),rfile)){
                fprintf(wfile,"%s",line);
            }
            fclose(rfile);
            fclose(wfile);
            printf("Yazilan kod calistiriliyor....");
            clock_t start,end;
            start=clock();
            system("gcc code.c && start a.exe && pause");
            end=clock();
            printf("Calisma suresi : %f",(double)(end-start)/CLOCKS_PER_SEC);
}
int byteCek(char *line){
    int x=0;
    if(strcmp(line,"char")==0){
        x=1;
    }else if(strcmp(line,"short")==0){
        x=2;
    }else if(strcmp(line,"int")==0||strcmp(line,"long")==0||strcmp(line,"float")==0){
        x=4;
    }else if(strcmp(line,"double")==0){
        x=8;
    }
    return x;
}
int yanYanaDegerTanimlama(char *line,char *birSonraki){
    int sayac=0;
    int x=byteCek(line);
    char arrayBoyut[100];
    int arrayStringKontrol=0;
    if(strstr(birSonraki,";")!=NULL){
            char *tmp;
            tmp=strtok(birSonraki,",");
            int arraySayi=1;
            while(tmp!=NULL){
                strcpy(tmp,trim(tmp));
                if(strstr(tmp,"[")!=NULL){
                    for(int i=0;i<strlen(tmp);i++){
                        //Array Kontrol
                        if(tmp[i]=='['){
                            i++;
                            int a=0;
                            if(isdigit(tmp[i])){
                                while(isdigit(tmp[i+a])){
                                    arrayBoyut[a]=tmp[i+a];
                                    a++;
                                }
                                arraySayi*=atoi(arrayBoyut);
                            }else{
                                char yeni[100];
                                strcpy(yeni,"");
                                if(arrayStringKontrol==1){
                                    arrayBoyut[strlen(arrayBoyut)]='*';
                                    arrayBoyut[strlen(arrayBoyut)+1]='\0';
                                     while(tmp[i+a]!=']'){
                                        yeni[a]=tmp[i+a];
                                        a++;
                                    }
                                }else{
                                    while(tmp[i+a]!=']'){
                                        arrayBoyut[a]=tmp[i+a];
                                        a++;
                                    }
                                    arrayBoyut[a]='\0';
                                }
                                strcat(arrayBoyut,yeni);
                                arrayStringKontrol=1;
                            }
                        }
                    }
                }
                else if(strstr(tmp,"*")!=NULL){
                    if(strstr(tmp,"=")==NULL){
                        sayac+=2;
                    }else{
                        if(strstr(tmp,"*") < strstr(tmp,"=")){
                            sayac+=2;
                        }else sayac++;
                    }
                }else{
                    sayac++;
                }
                tmp=strtok(NULL,",");
            }

            if(arrayStringKontrol==1){
                printf("%d*(%d + %s)+",x,sayac,arrayBoyut);
                x=0;
            }else{
                if(arraySayi!=1){
                    sayac+=arraySayi;
                }
                x*=sayac;
            }

    }else{
       if(strstr(birSonraki,"main")==NULL){
           for(int i=0;i<strlen(birSonraki);i++){
                if(birSonraki[i]!='('){
                        fonksiyonAdi[i]=birSonraki[i];
                }else break;
           }
           strcpy(fonksiyonAdi,trim(fonksiyonAdi));
       }else{
           if(strcmp(fonksiyonAdi,"$")==0){
                strcpy(fonksiyonAdi,"$");
           }
       }
       x=ayikla(line,birSonraki);
       strcpy(fonksiyonTipi,line);//Global FonksyionTip tutan degere tipi kopyala
    }
    return x;
}
int returnByte(){
    return byteCek(fonksiyonTipi);
}
char *trim(char *line){
    int ilk=0,son=0;
    while(line[ilk]==' ')
        ilk++;
    strcpy(line,line+ilk);
    while(line[strlen(line)-son-1]==' ')
        son++;
    line[strlen(line)-son]='\0';
    return line;
}
int  ayikla(char line[],char birSonraki[]){
    int ilkp=0;
    for(int i=0;i<strlen(birSonraki);i++){
        if(birSonraki[i]=='('){
                ilkp=i+1;
        }else if(birSonraki[i]==')'){
                birSonraki[i]='\0';
                break;
        }
    }
    strcpy(birSonraki,birSonraki+ilkp);
    strcpy(birSonraki,trim(birSonraki));
    char *tmp,arrayBoyut[100];
    int x=0;
    int sayac=0;
    int sonuc=0;
    tmp=strtok(birSonraki,",");
    while(tmp!=NULL){
        sayac=0;
        strcpy(tmp,trim(tmp));
        for(int i=0;i<strlen(tmp);i++){
             if(tmp[i]==' '){
                    char yeni[i+1];
                    int a=0;
                    while(a!=i){
                        yeni[a]=tmp[a];
                        a++;
                    }
                    yeni[a]='\0';
                    x=byteCek(yeni);
                    break;
            }
        }
        int arrayStringKontrol=0;
        if(strstr(tmp,"[")!=NULL){
            for(int i=0;i<strlen(tmp);i++){
                //Array Kontrol
                 if(tmp[i]=='['){
                    i++;
                    int a=0;
                    if(isdigit(tmp[i])){
                        while(isdigit(tmp[i+a])){
                            arrayBoyut[a]=tmp[i+a];
                            a++;
                        }
                        sayac+=(atoi(arrayBoyut));
                    }else{
                        while(tmp[i+a]!=']'){
                            arrayBoyut[a]=tmp[i+a];
                            a++;
                        }
                        arrayBoyut[a]='\0';
                        arrayStringKontrol=1;
                    }
                }//Array kontrol bitis;
            }
        }
        else if(strstr(tmp,"*")!=NULL){
                sayac+=2;
        }else sayac++;
        if(arrayStringKontrol==1){
            printf("(%d * %s)+",x,arrayBoyut);
            x=0;
        }else{
             sonuc+=x*sayac;
        }
        tmp=strtok(NULL,",");
    }
    return sonuc;
}
int forByteHesapla(char *line,char *birSonraki){
    int sonuc=0;
    strcat(line,birSonraki);
    if(strstr(line,"char")!=NULL||strstr(line,"short")!=NULL||strstr(line,"int")!=NULL||strstr(line,"long")!=NULL||strstr(line,"float")!=NULL||strstr(line,"double")!=NULL){
        int pt=0,nt=0,bt=0;
        for(int i=0;i<strlen(line);i++){
            if(line[i]=='(' ){
                pt=i+1;
            }else if(line[i]==';'){
                nt=i;
                break;
            }
        }
        line[nt]='\0';
        strcpy(line,line+pt);
        strcpy(line,trim(line));
        char *tmp;
        int x=0;
        tmp=strtok(line,",");
        while(tmp!=NULL){
            strcpy(tmp,trim(tmp));
            for(int i=0;i<strlen(tmp);i++){
                if(tmp[i]==' '){
                    char yeni[i+1];
                    int a=0;
                    while(a!=i){
                        yeni[a]=tmp[a];
                        a++;
                    }
                    yeni[a]='\0';
                    x=byteCek(yeni);
                }
            }
            sonuc+=x;
            tmp=strtok(NULL,",");
        }
    }
    return sonuc;
}
int yerKarmasikliginiBul(){
    FILE *rfile=fopen("code.txt","r");
    char line[1024];
    char birSonraki[1024];
    int sonuc=0;
    printf("Sonuc= ");
    while(fscanf(rfile,"%s",line)!=EOF){
        //printf("%s\n",line);
        if(strcmp(line,"char")==0||strcmp(line,"short")==0||strcmp(line,"int")==0||strcmp(line,"long")==0||strcmp(line,"float")==0||strcmp(line,"double")==0){
            fgets(birSonraki,sizeof(birSonraki),rfile);
            sonuc+=yanYanaDegerTanimlama(line,birSonraki);
        }else if(strcmp(line,"return")==0){
            fscanf(rfile,"%s",line);
            if(isdigit(line[0])==0){
                sonuc+=returnByte();
            }
        }else if(strstr(line,"for")!=NULL){
            if(strstr(line,")")!=NULL ){
                strcpy(birSonraki,"");
                sonuc+=forByteHesapla(line,birSonraki);
            }else{
                fgets(birSonraki,sizeof(birSonraki),rfile);
                sonuc+=forByteHesapla(line,birSonraki);
            }
        }
    }
    printf("%d\n",sonuc);
    fclose(rfile);
    return sonuc;
}
char* forZamanHesapla(char *line){
    char tmpKosul[100];
    char tmpAtama[100];
    char tmpArtis[100];
    strcpy(tmpAtama,line);
    for(int i=0;i<strlen(line);i++){
        if(line[i]==';'){
            strcpy(tmpKosul,line+i+1);
            tmpAtama[i]='\0';
            break;
        }
    }
    for(int i=0;strlen(tmpAtama);i++){
        if(tmpAtama[i]=='('){
            strcpy(tmpAtama,tmpAtama+i+1);
            break;
        }
    }
    for(int i=0;strlen(tmpKosul);i++){
        if(tmpKosul[i]==';'){
            tmpKosul[i]='\0';
            break;
        }
    }
    strcpy(tmpKosul,trim(tmpKosul));
    int v;
    for(int i=0;i<strlen(line);i++){
        if(line[i]==';'){
                v=i;
        }
    }
    strcpy(tmpArtis,line+v+1);
    for(int i=0;i<strlen(tmpArtis);i++){
        if(tmpArtis[i]==')'){
            tmpArtis[i]='\0';
            break;
        }
    }
    strcpy(tmpArtis,trim(tmpArtis));
    char sonuc[100];
    if(strstr(tmpArtis,"+")!=NULL || strstr(tmpArtis,"-")!=NULL){
        if(strstr(tmpArtis,"+")!=NULL){
            for(int i=0;i<strlen(tmpKosul);i++){
                if(tmpKosul[i]=='<' || tmpKosul[i]=='>'){
                    i++;
                    if(tmpKosul[i]=='='){
                        i++;
                    }
                    strcpy(sonuc,tmpKosul+i);
                    break;
                }
            }
        }else{
            for(int i=0;i<strlen(tmpAtama);i++){
                    if(tmpAtama[i]=='='){
                        strcpy(sonuc,tmpAtama+i+1);
                        break;
                    }
            }
        }
    }else if(strstr(tmpArtis,"*")!=NULL || strstr(tmpArtis,"/")!=NULL){
         char tmp[100];

         if(strstr(tmpArtis,"*")!=NULL ){
             for(int i=0;i<strlen(tmpKosul);i++){
                    if(tmpKosul[i]=='<' || tmpKosul[i]=='>'){
                        i++;
                        if(tmpKosul[i]=='='){
                            i++;
                        }
                        strcpy(tmp,tmpKosul+i);
                        break;
                    }
             }
         }else{
            for(int i=0;i<strlen(tmpAtama);i++){
                if(tmpAtama[i]=='='){
                    strcpy(tmp,tmpAtama+i+1);
                    break;
                }
            }
         }if(atoi(tmp)!=0){
            strcpy(sonuc,"1");
         }else{
            strcpy(sonuc,"log");
            strcat(sonuc,tmp);
         }
    }
    if(atoi(sonuc)!=0){
            strcpy(sonuc,"1");
    }
    char *x=sonuc;
    return x;
}
char *whileZamanHesapla(char *line,long int konum){
     char tmpKosul[100];
     char bIsareti;
     for(int i=0;i<strlen(line);i++){
            if(line[i]=='('){
                strcpy(tmpKosul,line+i+1);
                break;
            }
     }
     for(int i=0;i<strlen(tmpKosul);i++){
           if(tmpKosul[i]==')')
                tmpKosul[i]='\0';
     }
     strcpy(tmpKosul,trim(tmpKosul));
     char x1[100],x2[100];
     strcpy(x1,tmpKosul);
     for(int i=0;i<strlen(tmpKosul);i++){
        if(tmpKosul[i]=='<' || tmpKosul[i]=='>'){
            bIsareti=tmpKosul[i];
            if(tmpKosul[i-1]=='=')
                 x1[i-1]='\0';
            else
                 x1[i]='\0';
            if(tmpKosul[i+1]=='=')
                strcpy(x2,tmpKosul+i+2);
            else
                strcpy(x2,tmpKosul+i+1);
            break;
        }
     }
     strcpy(x1,trim(x1));
     strcpy(x2,trim(x2));
     FILE *rfile=fopen("yeni.txt","r");
     char  rLine[1000];
     char sonuc[100];
     strcpy(sonuc,"");
     while(fgets(rLine,sizeof(rLine),rfile)){
         long int gosterge=ftell(rfile);
         if(konum < gosterge){
                if(strstr(rLine,x1)!=NULL || strstr(rLine,x2)!=NULL && strstr(rLine,tmpKosul)==NULL){
                    int kontrol=0;
                    if(strstr(rLine,x1)!=NULL){
                            for(int i=0,j;i<strlen(rLine);i++){
                                for(j=0;j<strlen(x1);j++){
                                    if(rLine[i+j]!=x1[j])
                                        break;
                                }
                                if(j==strlen(x1)){
                                    if(rLine[i+1]!=']' && rLine[i-1]!='[' && rLine[i-1]!='=' && rLine[i-1]!=',' && isalpha(rLine[i-1])==0 &&isalpha(rLine[i-1])==0){
                                            kontrol=1;
                                    }
                                    break;
                                }
                            }
                        if(kontrol==1){
                            if(strstr(rLine,"+")!=NULL || strstr(rLine,"-")!=NULL){
                                if(bIsareti=='>'){
                                    strcpy(sonuc,x1);
                                }else {
                                    strcpy(sonuc,x2);
                                }
                            }else if(strstr(rLine,"*")!=NULL || strstr(rLine,"/")!=NULL){
                                strcpy(sonuc,"log");
                                if(bIsareti=='/'){
                                    strcat(sonuc,x1);
                                }else{
                                    strcat(sonuc,x2);
                                }
                            }
                        }
                    }else{
                            for(int i=0,j;i<strlen(rLine);i++){
                                for(j=0;j<strlen(x2);j++){
                                    if(rLine[i+j]!=rLine[j])break;
                                }
                                if(j==strlen(x2)){
                                    if(rLine[i+1]!=']' && rLine[i-1]!='[' && rLine[i-1]!='=' && rLine[i-1]!=',' && isalpha(rLine[i-1])==0 &&isalpha(rLine[i-1])==0){
                                               kontrol=1;
                                    }
                                }
                            }
                            if(kontrol==1){
                                if(strstr(rLine,"+")!=NULL || strstr(rLine,"-")!=NULL){
                                    if(bIsareti=='<'){
                                        strcpy(sonuc,x2);
                                    }else{
                                        strcpy(sonuc,x1);
                                    }
                                }else if(strstr(rLine,"*")!=NULL || strstr(rLine,"/")!=NULL){
                                    strcpy(sonuc,"log");
                                    if(bIsareti=='/'){
                                        strcat(sonuc,x1);
                                    }else{
                                        strcat(sonuc,x2);
                                    }
                                }
                            }
                    }

                }
                if(strcmp(sonuc,"")!=0){
                    break;
                }
         }

     }
     fclose(rfile);
     char *x=sonuc;
     return x;
}
char *recursiveBul(char *line){
    char sonuc[100];
    strcpy(sonuc,"");
    int a=0,sayac=0;
    for(int i=0;i<strlen(line);i++){
        if(line[i]=='('){
            i++;
            while(line[i]!=')'){
                sonuc[a]=line[i];
                i++;
                a++;
            }
            sayac++;
        }
    }
    sonuc[a]='\0';
    char *x;
    if(strstr(sonuc,"+")!=NULL || strstr(sonuc,"-")!=NULL){
            int i=0;
            while(1){
               if(sonuc[i]=='+' ||sonuc[i]=='-')
                    break;
                i++;
            }
            sonuc[i]='\0';
            char tmp[100];
            if(sayac==2){
                strcpy(tmp,"2^");
                strcat(tmp,sonuc);
                strcpy(sonuc,tmp);
            }else if(sayac==3)
            {
                strcpy(tmp,"3^");
                strcat(tmp,sonuc);
                strcpy(sonuc,tmp);
            }
            x=sonuc;
    }else if(strstr(sonuc,"*")!=NULL || strstr(sonuc,"/")!=NULL){
            int i=0;
            char tmp[100];
            strcpy(tmp,"log");
            while(1){
               if(sonuc[i]=='*' ||sonuc[i]=='/')
                    break;
                i++;
            }
            sonuc[i]='\0';
            strcat(tmp,sonuc);
            strcpy(sonuc,tmp);
            x=sonuc;
    }else{
        strcpy(sonuc,"");
        x=sonuc;
    }
    return x;
}
void zamanKarmasikliginiBul(){
    printf("Yer Karmasikligi\t");
    yerKarmasikliginiBul();
    printf("Zaman Karmasikligi\t");
    FILE *rfile=fopen("code.txt","r");
    char line[1000];
    char sonuc[100];
    long int konum;
    int forK=0,whileK=0;
    int doKontrol=0;
    strcpy(sonuc,"");
    while(fgets(line,sizeof(line),rfile)){
        if(strstr(line,"for")!=NULL){
            char tmpFor[100];
            strcpy(tmpFor,forZamanHesapla(line));
            if(atoi(tmpFor)==0){
                if(forK==1 || whileK==1){
                    strcat(sonuc," * ");
                }
                strcat(sonuc,tmpFor);
            }
            forK=1;
        }else if(strstr(line,"do")!=NULL){
            char *r=strstr(line,"do");
            if(isalpha(*(r-1))==0){
                konum=ftell(rfile);
            }
            doKontrol=1;
        }else if(strstr(line,"while")!=NULL){
            if(doKontrol==0){
                konum=ftell(rfile);
            }
            if(forK==1 || whileK==1){
                    strcat(sonuc," * ");
            }
            char tmpWhile[100];
            strcpy(tmpWhile,whileZamanHesapla(line,konum));
            if(atoi(tmpWhile)==0)
                strcat(sonuc,tmpWhile);
            whileK=1;
        }else if(strstr(line,fonksiyonAdi)!=NULL){
             strcat(sonuc,recursiveBul(line));
        }
        if(strstr(line,"}")!=NULL){
            forK=0;
            whileK=0;
        }
    }
    if(strcmp(sonuc,"")==0)printf("sonuc: BigO(1)");
    else
        printf("sonuc: %s",sonuc);
}
void dosyaKopyala(){
    FILE *wfile=fopen("yeni.txt","w");
    FILE *rfile=fopen("code.txt","r");
    char line[1000];
    while(fgets(line,sizeof(line),rfile)){
        fprintf(wfile,"%s",line);
    }
    fclose(rfile);
    fclose(wfile);
}
void dosyaOku(){
    FILE *rfile=fopen("code.txt","r");
    char line[1000];
    while(fgets(line,sizeof(line),rfile)){
        printf("%s",line);
    }
    fclose(rfile);
}
int main()
{
        strcpy(fonksiyonAdi,"$");
        dosyaKopyala();
        while(1){
        int secim=0;
        printf("\n1-BigO() zaman ve yer karmasikligini hesapla\n");
        printf("2-kodun calisma suresini Hesapla + Kod MU?(Kodsa Hatalimi?)\n");
        printf("3-Kodu Oku\n");
        printf("4-Cikis\n");
        printf("Bir secim yapiniz:");
        scanf("%d",&secim);
        if(secim==4){
            break;
        }else if(secim==1){
            zamanKarmasikliginiBul();
        }else if(secim==2){
            calismaSuresiniBul();
        }else if(secim==3){
            dosyaOku();
        }else{
            printf("Hatali Giris !!\n");
        }
    }
    return 0;
}
/*

 		if(strstr(line,"(")!=NULL && strstr(line,")")!=NULL){
                    printf("N +");
                    sonuc=0;
                }
                else
                    sonuc+=returnByte();

*/
