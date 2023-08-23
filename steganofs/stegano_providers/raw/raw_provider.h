#ifndef _RAW_PROVIDER_H_
#define _RAW_PROVIDER_H_

#include "../stegano_file.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct SteganoFile read_raw (const char *path);
size_t write_raw (struct SteganoFile);

#endif //_RAW_PROVIDER_H_
