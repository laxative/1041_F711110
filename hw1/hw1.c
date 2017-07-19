//學號:F74046242
//姓名：謝耀賢
//編譯方式：gcc -o hw1 hw1.c
//執行方式：./hw1 (infile) (outfile)
//功能：複製檔案
//更新日期：2015.10.13


 #include<stdio.h>                                                           
 #include<stdlib.h>
 
 int main(int argc, char *argv[]){
 
 FILE *infp;
 FILE *outfp;
 int ch;

 if(argc!=3)   //檢查輸入格式
 {
	printf("Error!!\n");
	exit(1);
 }

 infp = fopen(argv[1],"r");   //開啟讀取檔案
 outfp = fopen(argv[2],"w");  //開啟存入檔案
 

 while((ch = fgetc(infp)) != EOF)  //自infile中抓取字元存入outfile
 {
     fputc(ch, outfp);
 }
 
 fclose(infp);     //關閉檔案
 fclose(outfp);    //關閉檔案
 
 
 return 0;
 }
