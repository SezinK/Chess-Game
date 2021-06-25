//
//  main.cpp
//  ChessGame
//
//  Created by SEZİN on 18.06.2021.
//

/* The Grading Criteria */
/*
 1- Bir taşın tehdit altında olup olmadığının kontrolü, o taşı tehdit eden karşı renkte bir veya birden fazla taş olması durumunda oluşur.
 2- Table 1 Satranç TaşlarıTable 1’de taşların puanları verilmiştir. Eğer bir taş tehdit edilmiyorsa tablodaki puanı alır.
 3- Eğer bir taş karşı tarafın taşlarından herhangi biri tarafından tehdit ediliyorsa, tehdit edilen taşın puanı Table 1’deki puanının yarısı alınır.
 
 */

/*
 Not: Sadece at ve fil tarafından tehdit olan durumları ele alın. Yani sadece Fil ve at tehdit olduğu veya tehdit ettiği durumlarda tehdit olunan taşların puanları yarı yarıya indirilip o anki puanlama yapılacak.
 */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct Point{
    char x;
    char y;
} Point;

void clear (void);
int possPawn(FILE*,long); // Finding the position of the pawns
int countKnights(); //Count knights that can attack
int countPieces(); // Counting the pieces on the chess board for a specific color


int main(int argc, const char * argv[]) {
    
    // Reading the board1.
    
    char *filename = "/Users/sezin/Desktop/ChessGame/board1.txt";
    FILE *fp = fopen(filename, "r");
    
    
    // Positions of the chess pieces
    //int possPawnBlack[8], possPawnWhite[8];
    //long pawn;
    
    if (fp == NULL) {
        printf("Could not open the file %s",filename);
        return 1;
    }
    
    // First we need to read the txt file.
    // After that, we need to read it to a 8x8 matrix and then close it.
    // We will go with the matrix we created to check the positions
    
    Point *points = (Point*)malloc(9* sizeof(Point));
    int index = 0;
    while(fscanf(fp, "%c %c ", &points[index].x, &points[index].y) == 2)
          index++;
    for (int u=0; u<8; u++) {
        for (int w=0; w<8; w++) {
            printf("%c ",points[u].x);
        }printf("\n");
    }
    // Reading one character at a time and display it to the output
    char ch;
    int ps=0, as=0, fs=0, ks=0, vs=0, ss=0; //These will be used to count the chess pieces in the board for the black ones.
    int pb=0, ab=0, fb=0, kb=0, vb=0, sb=0; //These will be used to count the chess pieces in the board for the white ones.
    while ((ch = fgetc(fp)) != EOF ) {
        
        // Counting the chess pieces for both white and black in the board.
        if (ch == (char)'p' && (ch=fgetc(fp))==(char)'s') {ps++;}
        else if (ch == (char)'a' && (ch=fgetc(fp))==(char)'s') {as++;}
        else if (ch == (char)'f' && (ch=fgetc(fp))==(char)'s') {fs++;}
        else if (ch == (char)'k' && (ch=fgetc(fp))==(char)'s') {ks++;}
        else if (ch == (char)'v' && (ch=fgetc(fp))==(char)'s') {vs++;}
        else if (ch == (char)'s' && (ch=fgetc(fp))==(char)'s') {ss++;}
        
        //clear();
        if (ch == (char)'p' && (ch=fgetc(fp))==(char)'b') {pb++;}
        else if (ch == (char)'a' && (ch=fgetc(fp))==(char)'b') {ab++;}
        else if (ch == (char)'f' && (ch=fgetc(fp))==(char)'b') {fb++;}
        else if (ch == (char)'k' && (ch=fgetc(fp))==(char)'b') {kb++;}
        else if (ch == (char)'v' && (ch=fgetc(fp))==(char)'b') {vb++;}
        else if (ch == (char)'s' && (ch=fgetc(fp))==(char)'b') {sb++;}
        
        
        //putchar(ch); // You can see the txt file by uncommenting this line and commenting the lines 40-52
    }
    
    fflush(stdin);
    
    while ((ch = fgetc(fp)) != EOF) {
        
        
    }
    
    // Finding the location of the pawns for both black (Siyah) and white (Beyaz).
    int *locPS = (int*)malloc(8*sizeof(int));
    int *locPB = (int*)malloc(8*sizeof(int));;
    int PSMatrix[8][8]={};
    int j=0,k=0,temp;
    int t, y;
    for (int p=1; p<=322; p++) {
        if (p%3==0) {
            for (t=0; t<8; t++) {
                for (y=0; y<8; y++) {
                    fseek(fp, p, SEEK_SET);
                    fflush(fp);
                    ch = fgetc(fp);
                    if (ch=fgetc(fp)=='p') {
                        printf("PS FOUND!!!\n");
                        fseek(fp, p+1, SEEK_SET);
                        fflush(fp);
                        ch = fgetc(fp);
                        PSMatrix[t][y] = 1;
                        if (ch == 's') {
                            locPS[j] = p; j++;
                            PSMatrix[t][y] = 1;
                        }
                        if (ch == 'b') {
                            locPB[k] = p; k++;
                        }
                    }
                }
            }
        }
    }
    
    printf("\n");
    for (t=0; t<8; t++) {
        for (y=0; y<8; y++) {
            printf("%d ", PSMatrix[t][y]);
        }printf("\n");
    }
    
    printf("\n");
    
    for (int i=1; i<=322; i++) {
        fseek(fp, i, SEEK_SET);
        fflush(fp);
        ch = fgetc(fp);
        if (ch == 'p') {
            temp=i;
            fseek(fp, temp+1, SEEK_SET);
            fflush(fp);
            ch = fgetc(fp);
            if (ch == 's') {
                locPS[j] = temp; j++;
            }
            if (ch == 'b') {
                locPB[k] = temp; k++;
            }
        }
        
    }
    
    // Finding the location of the knights for both black(Siyah) and white(Beyaz).
    int *locAS = (int*)malloc(8*sizeof(int));
    int *locAB = (int*)malloc(8*sizeof(int));;
    j=0;k=0;
    for (int i=1; i<=322; i++) {
        fseek(fp, i, SEEK_SET);
        fflush(fp);
        ch = fgetc(fp);
        if (ch == 'a') {
            fseek(fp, i+1, SEEK_SET);
            fflush(fp);
            ch = fgetc(fp);
            if (ch == 's') {
                locAS[j] = i; j++;
            }
            if (ch == 'b') {
                locAB[k] = i; k++;
            }
        }
    }
    printf("\n");
    printf("PS Locations: %d %d %d",locPS[0], locPS[1], locPS[2]);
    printf("\n");
    printf("PB Locations: %d %d %d",locPB[0], locPB[1], locPB[2]);
    printf("\n");
    printf("AS Locations: %d %d %d",locAS[0], locAS[1], locAS[2]);
    printf("\n");
    printf("AB Locations: %d %d %d",locAB[0], locAB[1], locAB[2]);
    printf("\n");
    
    printf("\n");
    printf("PS = %d\n",ps);
    printf("AS = %d\n",as);
    printf("FS = %d\n",fs);
    printf("KS = %d\n",ks);
    printf("VS = %d\n",vs);
    printf("SS = %d\n",ss);
    printf("\n");
    printf("PB = %d\n",pb);
    printf("AB = %d\n",ab);
    printf("FB = %d\n",fb);
    printf("KB = %d\n",kb);
    printf("VB = %d\n",vb);
    printf("SB = %d\n",sb);

    
    fclose(fp);
    return 0;
}
void clear (void)
{
  while ( getchar() != '\n' );
}

/*int possPawn(FILE* fp, long pawn){
    char ch;
    printf("TEXT FILE:\n");
    while ((ch=fgetc(fp))!=EOF) {
        printf("%c ",ch);
    }printf("\n");
    
    int matrix[8][8];
    
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (fgetc(fp) == pawn) {
                matrix[i][j] = 1;
            }
            
            else
                matrix[i][j] = 0;
        }
    }
    
    printf("MATRIX:\n");
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            printf("%d ",matrix[i][j]);
        }printf("\n");
    }
    printf("\n");
    
    for (int i=1; i<8; i++) {
        for (int j=1; j<8; j++) {
            if (matrix[i][j] == 1) {
                return (static_cast<void>(i),j);
            }
        }
    }
    return (static_cast<void>(0),0);
    
}*/
    

