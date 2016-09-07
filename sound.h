// opcode
// note, channel, Duration
const byte PROGMEM titleScore [] = 
{ 
  0x90,
  91, 0, 100, 0x80,
  0x90,
  87, 0, 200, 0x80,
  0x90,
  92, 1, 44, 0x80,
  0xf0
};

const byte PROGMEM scoreScore [] = 
{ 
  0x90,
  89, 0, 33, 0x80,
  0x90,
  91, 0, 33, 0x80, 
  0x90,
  92, 0, 33, 0x80, 
  0xf0
};

const byte PROGMEM winScore [] = 
{ 
  0x90,
  92, 0, 100, 0x80,
  0x90,
  93, 0, 50, 0x80, 
  0x90,
  92, 0, 50, 0x80, 
  0x90,
  96, 0, 200, 0x80, 
  0xf0
};
