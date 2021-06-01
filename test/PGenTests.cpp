#include "PasswordGeneratorTests.h"

int main(int argc, char *argv[]) {
  if (int failures = lest::run(specification, argc, argv))
    return failures;

  return std::cout << "All tests passed\n", EXIT_SUCCESS;
}
