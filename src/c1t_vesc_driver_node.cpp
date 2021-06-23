#include "c1t_vesc_driver/c1t_vesc_driver.h"

int main(int argc, char** argv)
{
  VescDriverWrapper wrapper(argc, argv);

  return wrapper.run();
}