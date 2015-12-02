
/* Sets an error bit in the global error long. */
extern void setError(int pos) {
  #ifdef DEBUG
  if (pos > sizeof(long)) {
    Serial.println("ERROR -- setError() failed.");
    Serial.print("Warning -- bit out of range in error: ");
    Serial.print(pos);
    Serial.print(" -- width of long is: ");
    Serial.println(sizeof(long));
    while(1);
  }
  if (pos < 0) {
    Serial.println("Warning -- tried to set error bit at negative index.");
  }
  #endif
  
  /* Set the bit in the error number. */
  DRONE_ERROR = DRONE_ERROR & (1 << pos);
}

/* Returns true (non-zero) if there is an error, o.w false. */
extern inline int getError() {
  return DRONE_ERROR;
}

/* Clears the value of the error variable. */
extern inline void clearError() {
  DRONE_ERROR = 0;
}



