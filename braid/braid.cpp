/* ---------------------------------
File Encrypter "tabris.c"
ver 0.1
20150822 Y.Terasawa
Published under GPL Lisense
ver 1.0
20160129
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "chash.cpp"
#include "base64.cpp"



//s,r is system parametor
unsigned char r[N]={50,57,14,8,53,6,19,47,12,60,7,49,51,44,4,16,10,15,28,2,41,33,35,42,23,21,38,29,27,36,63,48,59,17,3,24,58,39,18,9,5,11,22,46,45,40,1,34,32,56,43,61,37,31,30,13,20,55,0,62,26,25,52,54};

unsigned char s[N]={58,1,59,3,36,25,63,51,50,21,17,11,53,2,18,7,6,12,31,28,20,32,14,8,22,13,38,30,26,34,47,54,46,43,60,35,55,49,27,39,40,61,56,5,37,4,9,16,52,29,48,19,0,62,10,33,41,42,15,44,57,24,45,23};

//ps,pr is public-kry
unsigned char ps[N]; 
unsigned char pr[N]; 

unsigned char x[5][N]={-1};
unsigned char message[4]={0};

unsigned char salt[64]={ 148, 246, 52, 251, 16, 194, 72, 150, 249, 23, 90, 107, 151, 42, 154, 124, 48, 58, 30, 24, 42, 33, 38, 10, 115, 41, 164, 16, 33, 32, 252, 143, 86, 175, 8, 132, 103, 231, 95, 190, 61, 29, 215, 75, 251, 248, 72, 48, 224, 200, 147, 93, 112, 25, 227, 223, 206, 137, 51, 88, 109, 214, 17, 172};

//PR:(x,y),f(x)=y,|(x,y)|=t,f=h(mx),x=m;f=(x-ai)p_r(x),(ai)sec,f(pub),c=f+m;
//SR(sindrome reconstruction):ml+gv=w->e=w/l'->x=H,eH=S=c,l(random),(g,x)sec
//GS:C=ABA^-1,D=AB'A^-1,E=Tr(r)(A,B),F=Tr(r)(C,D),c=(h(F)^m,E)
//mmc mat:G'=G+e, c=rG'+e,n=512,k=224,|G'|=114688bit



int deka(unsigned long long int u[N]){
  unsigned long long H[8]; //ハッシュ
  int t,i;
  typedef union a {
    unsigned long long l;
    unsigned char e[8];
  } hash;
  hash bb[8];
  int count=0;


  mon(H,u);
  //        printf("%s\n\n",argv[1]);  //argv[1]はファイル名の先頭の番地
  for (t=0; t<8; t++) { bb[t].l=H[t];}
  printf("\n\n");
  for (t=0; t<8; t++) {
    for(i=0;i<8;i++) { aa[count++]=bb[t].e[i]; }
  }
  
  printf("\n\n");
//    system("PAUSE");


  return 0;
}


void ufu(){
  int i,k,j,l,ii;
  time_t t;

  
 srand(time(&t));
 seed();
	

 for(ii=0;ii<3;ii++){
   for(i=0;i<N;i++)
     x[ii][i]= -1;
   
   i=rand()%N;
   x[ii][N-1]= i;
   
   i=0;
   while(i<N-1){
     k=0;
     
     j=rand()%N;
     for(l=0;l<i+1;l++){
       if(x[ii][l]==j && j!=x[ii][N-1])
	 k=1;
    }
     
     if(k==0 && j!=x[ii][N-1] && i!=j){
       x[ii][i]=j;
       printf("%d,",x[ii][i]);
       i++;
     }
   }
   printf("%d},\n",x[ii][N-1]);
 }
 printf("%d\n",i);


}


unsigned char v[N];

void ransue(){
int i,j=0;
	

unsigned char z[N];
unsigned char w[N];


ufu();

 for(i=0;i<N;i++){
   z[x[0][i]]=i;
   v[i]=salt[i];
 }
	
for(i=0;i<N;i++)
v[i]^=v[x[1][i]];

	
for(i=0;i<N;i++)
w[i]=x[0][x[1][z[i]]];
for(i=0;i<N;i++)
x[1][i]=w[i];
for(i=0;i<N;i++)
v[i]^=v[w[i]];
	
return;
}



set session(unsigned char u[N]){
unsigned char a[N],b[N],inv_b[N],c[N];
 unsigned char tmp[N],tmb[N];
 int i,j,k;
 set t;

 for(i=0;i<N;i++){
   a[i]=i;
   b[i]=i;
 }

/*
 for(i=0;i<N;i++)
   printf("%d,",s[i]);
  printf("\n");
 // exit(1);
 */
 for(i=0;i<32;i++){
   while(u[i]>0){
     if(u[i]%2==0){
       for(k=0;k<N;k++){
	 //  printf("0");
	 tmp[k]=a[r[k]];
	 tmb[k]=b[pr[k]];
	 //   printf("%d,",tmp[k]);
       }

       for(k=0;k<N;k++){
	 a[k]=tmp[k];
	 b[k]=tmb[k];
       }
     } else if(u[i]%2==1){
       //  printf("1");
       for(k=0;k<N;k++){
	 tmp[k]=a[s[k]];
	 tmb[k]=b[ps[k]];
	 // printf("%d,",s[k]);
       }
       // printf("\n");
       for(k=0;k<N;k++){
	 a[k]=tmp[k];
	 b[k]=tmb[k];
       }
     }
     u[i]=(u[i]>>1);
   }
 }
 
 for(i=0;i<N;i++){
   t.a[i]=a[i];
   t.b[i]=b[i];
   //   printf("%d,",t.b[i]);
 }

 
 return t;
 
}


void keygen(){
  int i,j,k;
  unsigned char fi[N],inv_f[N];
  unsigned char pi[4][N],e[N],c[N],b[N],f[N];
  FILE *fp,*fo;


  fo=fopen("braidpub.key","wb");
  fp=fopen("braidsec.key","wb");

  ufu();
  for(i=0;i<N;i++)
    fi[i]=x[0][i];

  for(i=0;i<N;i++)
    inv_f[fi[i]]=i;

  for(i=0;i<N;i++){
    b[i]=fi[r[inv_f[i]]];
    f[i]=fi[s[inv_f[i]]];
}
  fwrite(fi,1,N,fp);
  fwrite(b,1,N,fo);
  fwrite(f,1,N,fo);
  fclose(fp);
  fclose(fo);
  exit(1);
}


int main(int argc,char *argv[]){
  int i,j,k,count=0;
  unsigned char inv_x[N],o;
  unsigned char a[N],b[N],inv_b[N],c[N];
  time_t t;
  FILE *fp,*fo;
  set fai;
  arrayn p;
  array8 q;

  
  unsigned char cipher[4];
  unsigned char temp[N];
  unsigned char inv_c[16][N];
  
  unsigned char test[32]={1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0};
  unsigned char ee[4];
  unsigned int t2=0,l=0;
  char m[1];

  unsigned char u[N/2],tmp[N],tmb[N];
  unsigned char inv_t[16][N];
  unsigned char nx[N];
  

  srand(time(&t));

  for(i=0;i<N/2;i++){
    u[i]=rand()%256;
    printf("%u\n",u[i]);
  }


  printf("input mode\n");
  scanf("%s",&m);

  if(strcmp(m,"k")==0)
    keygen();
  if(strcmp(m,"d")==0){
    fp=fopen("braidsec.key","rb");
    fread(nx,1,N,fp);
    fclose(fp);
  }
  if(strcmp(m,"e")==0){
    fp=fopen("braidpub.key","rb");
    fread(pr,1,N,fp);
    fread(ps,1,N,fp);
    /*
   for(i=0;i<N;i++)
     printf("%d,",s[i]);
   printf("\n");
   */
    fclose(fp);
  }


  char file[100],out[100];
  int f;
  unsigned char buf[64];
  unsigned char h[N],rr[N];
  
  for(i=0;i<N;i++)
    h[i]= r[i];
  
  printf("\ninput file name\n");
  scanf("%s",&file);
  fp=fopen(file,"rb");
  printf("input outfile name\n");
  scanf("%s",&out);
  fo=fopen(out,"wb");
 

  j=0;

  if(strcmp("d",m)==0){
    for(i=0;i<N;i++)
      inv_b[nx[i]]=i;
    for(i=0;i<N;i++)
      pr[i]=nx[r[inv_b[i]]];
    for(i=0;i<N;i++)
      ps[i]=nx[s[inv_b[i]]];
  }

  for(i=0;i<N;i++)
    rr[i]=rand()%256;


  if(strcmp(m,"e")==0){
    fai=session(rr);
    
    for(i=0;i<N;i++)
      printf("%d,",fai.b[i]);
    printf("\n");
    
    fwrite(fai.a,1,64,fo);
  }


  if(strcmp(m,"d")==0){
    fread(fai.a,1,64,fp);
    for(k=0;k<N;k++){
      c[k]=nx[fai.a[inv_b[k]]];
      printf("%d,",c[k]);
    }
    printf("aaa\n");
  }

while((f=fread(buf,1,64,fp))>0){

  if(strcmp("e",m)==0){
    p=chash(fai.b);
    /*
    for(i=0;i<N;i++)
      printf("%d,",p.ar[i]);
    printf("\n");
    */
    for(k=0;k<N;k++)
      rr[k]=p.ar[k];
    fai=session(rr);
    for(k=0;k<N;k++)
      buf[k]^=p.ar[k];
  }
  if(strcmp("d",m)==0){
  /*
    for(i=0;i<N;i++)
      printf("%d,",c[i]);
    printf("vv\n");
    //        exit(1);
    */
    p=chash(c);
    
    for(k=0;k<N;k++){
      buf[k]^=p.ar[k];
      rr[k]=p.ar[k];
    }
    fai=session(rr);
    /*
    for(i=0;i<N;i++)
      printf("%d,",p.ar[i]);
    printf("bb\n");
    */
    //    exit(1);
    for(k=0;k<N;k++)
      c[k]=fai.b[k];
    
  }
  fwrite(buf,1,f,fo);

 }

 fclose(fp);
 fclose(fo);


return 0;
}
