/*
------------------------------------------------------------------------------
rand.h: definitions for a random number generator
By Bob Jenkins, 1996, Public Domain
MODIFIED:
  960327: Creation (addition of randinit, really)
  970719: use context, not global variables, for internal state
  980324: renamed seed to flag
  980605: recommend RANDSIZL=4 for noncryptography.
  010626: note this is public domain

  20.2.2008: by Juha Nieminen: Made a C++ version, moving everything that
             garbaged the global namespace inside the .cc file. The algorithm
             itself is untouched.
------------------------------------------------------------------------------
*/
#ifndef ISAAC_RAND_HH
#define ISAAC_RAND_HH

class IsaacRand
{
 public:
	IsaacRand(void) {};
    IsaacRand(unsigned seed);
    IsaacRand(unsigned seed1, unsigned seed2);
    IsaacRand(const unsigned* seeds, unsigned seedsAmount); // At most 32

    void setSeed(unsigned seed);
    void setSeed(unsigned seed1, unsigned seed2);
    void setSeed(const unsigned* seeds, unsigned seedsAmount); // At most 32

    inline unsigned getNext();



//------------------------------------------------------------------------
 private:
    typedef unsigned int ub4;      /* unsigned 4-byte quantities */
    static const ub4 RANDSIZL = 5; /* I recommend 8 for crypto, 4 for simulations */
    static const ub4 RANDSIZ = (1<<RANDSIZL);

    /* context of random number generator */
    struct randctx
    {
        ub4 randcnt;
        ub4 randrsl[RANDSIZ];
        ub4 randmem[RANDSIZ];
        ub4 randa;
        ub4 randb;
        ub4 randc;
    };

    randctx data;

    static void randinit(randctx* ctx, bool flag);
    static void isaac(randctx* ctx);
};

inline unsigned IsaacRand::getNext()
{
    return !data.randcnt-- ?
        (isaac(&data), data.randcnt=RANDSIZ-1, data.randrsl[data.randcnt]) :
        data.randrsl[data.randcnt];
}

#endif
