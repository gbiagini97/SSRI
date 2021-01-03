```
T = ABABDABACDABABCABAB
P =  ABABCABAB
n = 19
m = 9
```
---
```
calcolaBack(P, m, B)

h = 0
i = 1
B[0] = 0

// primo giro while
1 < 9 ? V

B == A ? F
0 != 0 ? F
B[1] = 0
i = 2

// secondo giro while
2 < 9 ? V
A == A ? V
h = 1
B[2] = 1
i = 3

// terzo giro while
3 < 9 ? V
B == B ? V
h = 2
B[3] = 2
i = 4

// quarto giro while
4 < 9 ? V
C == A ? F
h != 0 ? V
h = B[2-1] = B[1] = 0

// quinto giro while
4 < 9 ? V
C == A ? F
0 != 0 ? F
B[4] = 0
i = 5

// sesto giro while
5 < 9 ? V
A == A ? V
h = 1
B[5] = 1
i = 6

// settimo giro while
6 < 9 ? V
B == B ? V
h = 2
B[6] = 2
i = 7

// ottavo giro while
7 < 9 ? V
A == A ? V
h = 3
B[7] = 3
i = 8

// ottavo giro while
8 < 9 ? V
B == B ? V
h = 4
B[8] = 4
i = 9

// nono giro while
9 < 9 ? F

B = [0, 0, 1, 2, 0, 1, 2, 3, 4]
```
---
```
KMP(T, P, n, m)

j = 0
i = 0

// primo giro while
0 < 19 ? V
A == A ? V
j = 1
i = 1

1 == 9 ? F
1 < 19 && B != B ? F

// secondo giro while
1 < 19 ? V
B == B ? V
j = 2
i = 2

2 == 9 ? F
2 < 19 && A != A ? F

// terzo giro while
2 < 19 ? V
A == A ? V
j = 3
i = 2

3 == 9 ? F
3 < 19 && B != B ? F

// quarto giro while
3 < 19 ? V
B == B ? V
j = 4
i = 4

4 == 9 ? F
4 < 19 && C != D ? V
4 != 0 ? V
j = B[4-1] = B[3] = 2

// quinto giro while
4 < 19 = V
A == D ? F

2 == 9 ? F
4 < 19 && A != D ? V
2 != 0 ? V
j = B[2-1] = B[1] = 0

// sesto giro while
4 < 19 ? V
A == D ? F

0 == 9 ? F
4 < 19 && A != D ? V
0 != 0 ? F
i = 5

// settimo giro while
5 < 19 ? V
A == A ? V
j = 1
i = 6

1 == 9 ? F
6 < 19 && B != B ? F

// ottavo giro while
6 < 19 ? V
B == B ? V
j = 2
i = 7

2 == 9 ? F
7 < 19 && A != A ? F

// nono giro while
7 < 19 ? V
A == A ? V
j = 3
i = 8

3 == 9 ? F
8 < 19 && B != C ? V
3 != 0 ? V
j = B[3-1] = B[2] = 1

// decimo giro while
8 < 19 ? V
B == C ? F

1 == 9 ? F
8 < 19 && B != C ? V
1 != 0 ? V
j = B[1-1] = B[0] = 0

// undicesimo giro while
8 < 19 ? V
A == C ? F

0 == 9 ? F
8 < 19 && A != C ? V
0 != 0 ? F
i = 9

// dodicesimo giro while
9 < 19 ? V
A == D ? F

0 == 9 ? F
9 < 19 && A != D ? V
0 != 0 ? F
i = 10

// tredicesimo giro while
10 < 19 ? V
A == A ? V
j = 1
i = 11

1 == 9 ? F
11 < 19 && B != B ? F

// quattordicesimo giro while
11 < 19 ? V
B == B ? V
j = 2
i = 12

2 == 9 ? F
12 < 19 && A != A ? F

// quindicesimo giro while
12 < 19 ? V
A == A ? V
j = 3
i = 13

3 == 9 ? F
13 < 19 && B != B ? F

// sedicesimo giro while
13 < 19 ? V
B == B ? V
j = 4
i = 14

4 == 9 ? F
14 < 19 && C != C ? F

// diciassettesimo giro while
14 < 19 ? V
C == C ? V
j = 5
i = 15

5 == 9 ? F
15 < 19 && A != A ? F

// diciottesimo giro while
15 < 19 ? V
A == A ? V
j = 6
i = 16

6 == 9 ? F
16 < 19 && B != B ? F

// diciannovesimo giro while
16 < 19 ? V
B == B ? V
j = 7
i = 17

7 == 9 ? F
17 < 19 && A != A ? F

// ventesimo giro while
17 < 19 ? V
A == A ? V
j = 8
i = 18

8 == 9 ? F
18 < 19 && B != B ? F

// ULTIMO giro while
18 < 19 ? V
B == B ? V
j = 9
i = 19

9 == 9 ? V
PRINTA 19 - 9 = 10
j = B[9-1] = B[8] = 4
```