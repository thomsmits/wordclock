/**
  Functions to be deleted soon.
*/

#define PORT_SRCK 2
#define PORT_SER_IN 3
#define PORT_RCK 4
#define PORT_CLEAR 5
#define PORT_OUTPUT_ENABLE 6

void jens_und_thomas_verstehen_es_nicht() {
  
  high(PORT_CLEAR);
  
  for (int i = 0; i < 112; i++) {
    high(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
  }
  
  low(PORT_SER_IN);
  
  high(PORT_RCK);
  low(PORT_RCK);
  
  low(PORT_OUTPUT_ENABLE);
  
  for (int i = 0; i < 112; i++) {
    low(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
  }
  
  high(PORT_RCK);
  low(PORT_RCK);
  
  for (int i = 0; i < 112 / 2; i++) {
    high(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
    
    low(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
  }
  
  high(PORT_RCK);
  low(PORT_RCK);
  
  for (int i = 0; i < 112 / 2; i++) {
    low(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
    
    high(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
  }
  
  high(PORT_RCK);
  low(PORT_RCK);
  
  for (int i = 0; i < 112 / 2; i++) {
    high(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
    
    low(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
    
     low(PORT_SER_IN);
    high(PORT_SRCK);
    low(PORT_SRCK);
  }
  
  high(PORT_RCK);
  low(PORT_RCK);
  
  //low(PORT_CLEAR);
}


void thomas_versteht_es() {
  
   
  int x[112];
  memfill(x, 112, 0);
  
  for (int i = 0; i < 112; i += 2) {
    x[i] = 1;
  }
    
  for (int i = 0; i < 112; i++) {
    Serial.print(i);
    Serial.print(":");
    Serial.print(x[i]);
    Serial.print(" --\n");
  }
  
  send_to_shift_registers(x);

  
  
}
