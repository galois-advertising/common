#define _COMB(a, b) #a"."#b
#define COMB(a, b) _COMB(a, b)
#define _STR(a) #a
#define STR(a) _STR(a)
#define _JOIN(a, b) a##b
#define JOIN(a, b) _JOIN(a, b)
