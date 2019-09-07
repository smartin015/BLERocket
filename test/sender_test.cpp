#ifdef UNIT_TEST

#include <unity.h>


void testUserPartGenerator() {
  // TODO
  // - test generated parts from user ID do not end up as game::ShipPartType_unknown
  // - test higher score makes higher quality part
  // - test part quality cannot go below 1
}

void testSuppressNav() {
  // Should ensure that nav suppression is WAI
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    UNITY_END();
}

#endif
