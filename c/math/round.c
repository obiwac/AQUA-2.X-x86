
#include "round.h"

float round(float x) { return (float) ((int) (x + 0.5f)); }
float floor(float x) { return (float) ((int) x); }
float ceil(float x) { return (float) ((int) x + 1.0f); }
