

const char __attribute__ ((section ("userconst"))) blaat[]="its working!";


void __attribute__ ((section ("usercode"))) modi2c(void) 
{	bpWline(blaat);

}


