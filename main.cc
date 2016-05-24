#include "controller.h"

int main( int argc, char *argv[] ){
  if (argc == 1){ 
  	Controller c;
  	c.play();
  }
  else {
  	Controller c(argv[1]);
  	c.play();
  }
}
