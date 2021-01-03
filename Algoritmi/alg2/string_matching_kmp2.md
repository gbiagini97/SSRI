```C
// C program for implementation of KMP pattern searching 
// algorithm
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
void computeLPSArray(char *pat, int M, int *lps);
 
void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // index for pat[]
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    int i = 0;  // index for txt[]
    while (i < N)
    {
      if (pat[j] == txt[i])
      {
        j++;
        i++;
      }
 
      if (j == M)
      {
        printf("Found pattern at index %d \n", i-j);
        j = lps[j-1];
      }
 
      // mismatch after j matches
      else if (i < N && pat[j] != txt[i])
      {
        // Do not match lps[0..lps[j-1]] characters,
        // they will match anyway
        if (j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    free(lps); // to avoid memory leak
}
 
void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;  // length of the previous longest prefix suffix
    int i;
 
    lps[0] = 0; // lps[0] is always 0
    i = 1;
 
    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else // (pat[i] != pat[len])
       {
         if (len != 0)
         {
           // This is tricky. Consider the example 
           // AAACAAAA and i = 7.
           len = lps[len-1];
 
           // Also, note that we do not increment i here
         }
         else // if (len == 0)
         {
           lps[i] = 0;
           i++;
         }
       }
    }
}
 
// Driver program to test above function
int main()
{
   char *txt = "ABABDABACDABABCABAB";
   char *pat = "ABABCABAB";
   KMPSearch(pat, txt);
   return 0;
}

```


T = 0001101100111
P = 001

KMP(P[], T[], 13, 3)

    -------------
h = 0
back[0] = 0
i = 1

i < 3 ? true
    P[1] == P[h] ? true
        h = 1
        back[1] = 1
        i = 2

// h = 1
// i = 2
// back = [0, 1]
i < 3 ? true
    P[2] == P[1] ? false
        h != 0 ? true
            h = back[h-1] = back[0]
            // h = 0


// h = 0
// i = 2
i < 3 ? true
    P[2] == P[0] ? false
        h != 0 ? false
            back[2] = 0
            i = 3

//fine del while
// back[0,1,0]

----


i = j = 0

// prima iterazione while
// T = 0001101100111
// P = 001
// back = [0,1,0]
// i = 0, j = 0
i < 13 ? true
    P[j] == T[i] = P[0] == T[0] ? true
        j = 1
        i = 1
    j == m = 1 == 3 ? false
    i < n && P[j] != T[i] = 1 < 13 && P[1] != T[1] ? false

// seconda iterazione while
// T = 0001101100111
// P = 001
// back = [0,1,0]
// i = 1, j = 1
i < 13 ? true
    P[j] == T[i] = P[1] == T[1] ? true
        j = 2
        i = 2
    j == m = 2 == 3 ? false
    i < n && P[j] != T[i] = 2 < 13 && P[2] != T[2] ? true
        j != 0 ? true
            j = back[j-1] = back[1] = 1

// terza iterazione while
// T = 0001101100111
// P =  001
// back = [0,1,0]
// i = 2, j = 1
i < 13 ? true
    P[j] == T[i] = P[1] == T[2] ? true
        j = 2
        i = 3
    j == m = 2 == 3 ? false
    i < n && P[j] != T[i] = 3 < 13 && P[2] != T[3] ? false


// quarta iterazione while
// T = 0001101100111
// P =  001
// back = [0,1,0]
// i = 3, j = 2
i < 13 ? true
    P[j] == T[i] = P[2] == T[3] ? true
        j = 3
        i = 4
    j == m = 3 == 3 ? true // PATTERN FOUND
        j = back[j-1] = back[2] = 0


// quinta iterazione while
// T = 0001101100111
// P =  001
// back = [0,1,0]
// i = 4, j = 0
i < 13 ? true
    P[j] == T[i] = P[0] == T[4] ? false
    j == m = 0 == 3 ? false
    i < n && P[j] != T[i] = 4 < 13 && P[0] != T[4] ?  true
        j != 0 ? false
            i = 5


    



