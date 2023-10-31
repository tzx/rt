#include <cstdlib>
#include <ctime>
int random_id() {
  srand((unsigned) time(NULL));
  return rand();
}
