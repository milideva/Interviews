/* Option 1 */
typedef int bool;
#define true 1
#define false 0

/* Option 2 */
typedef int bool;
enum { false, true };

/* Option 3 */
typedef enum { false, true } bool;

/* Option 4 - C99 and later */
#include <stdbool.h>

