#define inPin 10
#define inPinMask 1 << 6
#define record_size 750

typedef struct {
  bool in;
  unsigned int duration;
} record;
