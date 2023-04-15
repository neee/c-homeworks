
#include <stdlib.h>
#include "clog.h"

int main(void) {
    clog_init(CLOG_LEVEL_DEBUG, NULL);
    LOG_DEBUG("test debug message");
    LOG_INFO("test info message");
    LOG_WARN("test warning message");
    LOG_ERROR("test error message");
    clog_close();

    return EXIT_SUCCESS;
}
