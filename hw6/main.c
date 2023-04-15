
#include <stdlib.h>
#include "clog.h"

int main(void) {
    clog_init(CLOG_LEVEL_DEBUG, NULL);
    LOG_DEBUG("test4");
    LOG_ERROR("test5");
    clog_close();

    return EXIT_SUCCESS;
}
