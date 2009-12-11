//we made custom files so we can distribute them
//we don't all have same functions as the orig. This file was required
//so MPFS would compile without a custom SaveAppConfig function.
#define SaveAppConfig() NOP()
